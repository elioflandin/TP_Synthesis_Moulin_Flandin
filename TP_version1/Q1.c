#include "main2.h"

void q1() {
    char welcomeMsg[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \nenseah %";
    if (write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg)) == -1) {
        perror("Erreur d'écriture");
        exit(EXIT_FAILURE);
    }
}

