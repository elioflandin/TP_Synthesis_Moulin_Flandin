#include "main.h"

void display_welcome_message() {
    char welcomeMsg[] = "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \nenseash %";
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));
}
