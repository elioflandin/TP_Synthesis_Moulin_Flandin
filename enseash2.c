#include "main.h"

#define BUFSIZE 1096

int main() {
    char buf[BUFSIZE];
    ssize_t bytesRead;

    char welcomeMsg[] = "Bienvenue dans le Shell ENSEA.\nenseash % ";
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

    while (1) {
        // Lecture de la commande utilisateur
        bytesRead = read(STDIN_FILENO, buf, BUFSIZE - 1);
        if (bytesRead <= 0) {
            perror("Erreur de lecture");  //Si la commande n'a pas pu être lu (erreur)
            exit(EXIT_FAILURE);
        }

        // Ajout d'un caractère nul pour traiter la chaîne
        buf[bytesRead - 1] = '\0'; // Remplace '\n' par '\0'

        // Création d'un processus enfant pour exécuter la commande
        pid_t pid = fork();
        if (pid < 0) {
            perror("Erreur lors du fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Processus enfant
            execlp(buf, buf, NULL);
            perror("Commande non trouvée");  //Si la commande n'est pas trouvée et ne peut pas être éxécutée
            exit(EXIT_FAILURE);
        } else {
            // Processus parent
            int status;
            waitpid(pid, &status, 0);
        }

        char prompt[] = "enseash % "; // On attend de nouveau une nouvelle commande
        write(STDOUT_FILENO, prompt, strlen(prompt));
    }

    return 0;
}


