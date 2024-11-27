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

        // Mesure du temps de début
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

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

            // Mesure du temps de fin
            clock_gettime(CLOCK_MONOTONIC, &end);

            // Calcul du temps d'exécution
            long seconds = end.tv_sec - start.tv_sec;
            long nanoseconds = end.tv_nsec - start.tv_nsec;
            if (nanoseconds < 0) {
                seconds--;
                nanoseconds += 1000000000;  // Correction si les nanosecondes sont négatives
            }
            long elapsedTimeMs = seconds * 1000 + nanoseconds / 1000000; // Temps en millisecondes

            // Analyser le statut du processus
            char prompt[BUFSIZE];
            if (WIFEXITED(status)) { // Le processus s'est terminé normalement
                int exitCode = WEXITSTATUS(status);
                int promptLen = snprintf(prompt, BUFSIZE, "enseash [exit:%d|%ldms] %% ", exitCode, elapsedTimeMs);
                write(STDOUT_FILENO, prompt, promptLen);
            } else if (WIFSIGNALED(status)) { // Le processus s'est terminé à cause d'un signal
                int signalCode = WTERMSIG(status);
                int promptLen = snprintf(prompt, BUFSIZE, "enseash [sign:%d|%ldms] %% ", signalCode, elapsedTimeMs);
                write(STDOUT_FILENO, prompt, promptLen);
            } else { // Autre cas (par précaution)
                char defaultPrompt[] = "enseash % ";
                write(STDOUT_FILENO, defaultPrompt, strlen(defaultPrompt));
            }
        }
    }

    return 0;
}

