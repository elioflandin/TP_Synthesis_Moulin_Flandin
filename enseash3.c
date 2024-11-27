#include "main.h"

#define BUFSIZE 1096

int main() {
    char buf[BUFSIZE];
    ssize_t bytesRead;

    char welcomeMsg[] = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

    while (1) {
        bytesRead = read(STDIN_FILENO, buf, BUFSIZE - 1);
        if (bytesRead <= 0) {
            perror("Erreur de lecture");
            exit(EXIT_FAILURE);
        }

        buf[bytesRead - 1] = '\0';

        // Vérification de la commande 'exit'
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
            int status;
            waitpid(pid, &status, 0);
        }

        char prompt[] = "enseash % ";
        write(STDOUT_FILENO, prompt, strlen(prompt));
    }

    return 0;
}
