#include "main.h"

#define BUFSIZE 1096

int main() {
    char buf[BUFSIZE];
    ssize_t bytesRead;
    int status = 0;

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

        // Measure the start time
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

            // Measure the end time
            clock_gettime(CLOCK_MONOTONIC, &end);

            // Calculate the execution time
            long seconds = end.tv_sec - start.tv_sec;
            long nanoseconds = end.tv_nsec - start.tv_nsec;
            if (nanoseconds < 0) {
                seconds--;
                nanoseconds += 1000000000;  // Correction if the nanoseconds are negative
            }
            long elapsedTimeMs = seconds * 1000 + nanoseconds / 1000000; // Convert to milliseconds

            char prompt[BUFSIZE];
            if (WIFEXITED(status)) {
                int exitCode = WEXITSTATUS(status);
                int promptLen = snprintf(prompt, BUFSIZE, "enseash [exit:%d|%ldms] %% ", exitCode, elapsedTimeMs);
                write(STDOUT_FILENO, prompt, promptLen);
            } else if (WIFSIGNALED(status)) {
                int signalCode = WTERMSIG(status);
                int promptLen = snprintf(prompt, BUFSIZE, "enseash [sign:%d|%ldms] %% ", signalCode, elapsedTimeMs);
                write(STDOUT_FILENO, prompt, promptLen);
            } else {
                char defaultPrompt[] = "enseash % ";
                write(STDOUT_FILENO, defaultPrompt, strlen(defaultPrompt));
            }
        }
    }

    return 0;
}

