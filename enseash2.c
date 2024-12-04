#include "main.h"

#define BUFSIZE 1096

int main() {
    char buf[BUFSIZE];
    ssize_t bytesRead;

    char welcomeMsg[] = "Bienvenue dans le Shell ENSEA.\nenseash % ";
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

    while (1) {
        // Reading the command using the "read" function
        bytesRead = read(STDIN_FILENO, buf, BUFSIZE - 1);
        if (bytesRead <= 0) {
            perror("Read error");  // If the command could not be read, display "Read error"
            exit(EXIT_FAILURE);
        }

        // Adding a null character to process the string
        buf[bytesRead - 1] = '\0'; // Replaces '\n' with '\0'

        // Creating a child process to execute the command (with fork)
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error during fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp(buf, buf, NULL); // Replaces the child process with the execution of the entered command ("buf")
            perror("Command not found");  // If the command is not found or cannot be executed
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0); // Waits for the child process to finish and retrieves its status
        }

        char prompt[] = "enseash % "; // Waiting for a new command
        write(STDOUT_FILENO, prompt, strlen(prompt));
    }

    return 0;
}

