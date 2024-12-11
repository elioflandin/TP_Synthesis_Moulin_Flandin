#include "main.h"

void tokenize_command(char *buf, char *argv[]) {
    char *token = strtok(buf, " ");
    int i = 0;

    // Split the input buffer into command and arguments
    while (token != NULL) {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;  // NULL-terminate the array of arguments
}

