#include "main.h"

#define BUFSIZE 1096

void handle_process_status(int status) {
    long elapsedTimeMs = calcul_time(); //Q5
    char prompt[BUFSIZE];
    
    if (WIFEXITED(status)) {  // Le processus s'est terminé normalement
        int exitCode = WEXITSTATUS(status);
        int promptLen = snprintf(prompt, BUFSIZE, "enseash [exit:%d|%ldms] %% ", exitCode, elapsedTimeMs);
        write(STDOUT_FILENO, prompt, promptLen);
    } else if (WIFSIGNALED(status)) {  // Le processus s'est terminé à cause d'un signal
        int signalCode = WTERMSIG(status);
        int promptLen = snprintf(prompt, BUFSIZE, "enseash [sign:%d|%ldms] %% ", signalCode, elapsedTimeMs);
        write(STDOUT_FILENO, prompt, promptLen);
    } else {  // Autres cas (par exemple, processus arrêté)
        char defaultPrompt[] = "enseash % ";
        write(STDOUT_FILENO, defaultPrompt, strlen(defaultPrompt));
    }
}
