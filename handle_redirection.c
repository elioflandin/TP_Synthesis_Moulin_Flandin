#include "main.h"

#define BUFSIZE 1096

void handle_redirection(char *argv[], int *input_fd, int *output_fd) {
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "<") == 0) {  // Input redirection
            if (argv[i + 1] != NULL) {
                *input_fd = open(argv[i + 1], O_RDONLY);
                if (*input_fd == -1) {
                    perror("Input file open error");
                    exit(EXIT_FAILURE);
                }
                argv[i] = NULL;  // Nullify the argument after "<"
            }
        } else if (strcmp(argv[i], ">") == 0) {  // Output redirection
            if (argv[i + 1] != NULL) {
                *output_fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (*output_fd == -1) {
                    perror("Output file open error");
                    exit(EXIT_FAILURE);
                }
                argv[i] = NULL;  // Nullify the argument after ">"
            }
        }
    }
}

