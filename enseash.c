#include "main.h"

#define BUFSIZE 1096

int main() {
	char buf[BUFSIZE] = "Bienvenue dans le Shell ENSEA. \nPour quitter, tapez 'exit'. \nenseah %";
	write(STDOUT_FILENO, buf, strlen(buf));

}
