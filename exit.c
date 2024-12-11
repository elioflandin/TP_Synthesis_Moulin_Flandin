#include "main.h"

void check_exit_command(char *buf) {
    // Checking for the 'exit' command
    if (strcmp(buf, "exit") == 0) {  // Compares the entered string (buf) with the string "exit", returns 0 if identical
        char exitMsg[] = "bye bye... !\n";
        write(STDOUT_FILENO, exitMsg, strlen(exitMsg));
        exit(EXIT_SUCCESS);  // Exit the program
    }
}



