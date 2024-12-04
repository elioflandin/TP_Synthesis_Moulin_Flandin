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

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Tokenize the input command to separate command and arguments
        char *argv[BUFSIZE / 2 + 1];  // Maximum number of arguments
        char *token = strtok(buf, " ");
        int i = 0;

        // Split the input buffer into command and arguments
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL;  // NULL-terminate the array of arguments

        pid_t pid = fork();
        if (pid < 0) {
            perror("Erreur lors du fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
	    pid_t child_pid = getpid();
	    printf("PID du processus fils : %d\n", child_pid);
            // Execute the command with arguments
            execlp(argv[0], argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], NULL);
            perror("Commande non trouvée");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);

            clock_gettime(CLOCK_MONOTONIC, &end);

            long seconds = end.tv_sec - start.tv_sec;
            long nanoseconds = end.tv_nsec - start.tv_nsec;
            if (nanoseconds < 0) {
                seconds--;
                nanoseconds += 1000000000;
            }
            long elapsedTimeMs = seconds * 1000 + nanoseconds / 1000000;

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

