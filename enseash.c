#include "main.h"

#define BUFSIZE 1096

int main() {
	char welcomeMsg[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \nenseah %";
	write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

}

