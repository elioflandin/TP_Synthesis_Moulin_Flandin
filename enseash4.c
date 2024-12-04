#include "main.h"

#define BUFSIZE 1096

int main() {
    char buf[BUFSIZE];
    ssize_t bytesRead;
    int status = 0; // Statut du dernier processus exécuté

    char welcomeMsg[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

    while (1) {
        bytesRead = read(STDIN_FILENO, buf, BUFSIZE - 1);
        if (bytesRead <= 0) {
            perror("Erreur de lecture");
            exit(EXIT_FAILURE);
        }

        buf[bytesRead - 1] = '\0';

	if (strcmp(buf, "exit") == 0) {
            char exitMsg[] = "bye bye... !\n";
            write(STDOUT_FILENO, exitMsg, strlen(exitMsg));
            break;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Erreur lors du fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execlp(buf, buf, NULL);
            perror("Commande non trouvée");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);

            // Analyser le statut du processus
            char prompt[BUFSIZE];
            if (WIFEXITED(status)) { // Le processus s'est terminé normalement
                int exitCode = WEXITSTATUS(status);
                int promptLen = snprintf(prompt, BUFSIZE, "enseash [exit:%d] %% ", exitCode);
                write(STDOUT_FILENO, prompt, promptLen);
            } else if (WIFSIGNALED(status)) { // Le processus s'est terminé à cause d'un signal
                int signalCode = WTERMSIG(status);
                int promptLen = snprintf(prompt, BUFSIZE, "enseash [sign:%d] %% ", signalCode);
                write(STDOUT_FILENO, prompt, promptLen);
            } else { // Autre cas (par précaution)
                char defaultPrompt[] = "enseash % ";
                write(STDOUT_FILENO, defaultPrompt, strlen(defaultPrompt));
            }
        }
    }

    return 0;
}

