#include "main.h"

void handle_user_commands() {
    #define BUFSIZE 1096
    char buf[BUFSIZE];
    ssize_t bytesRead;

    while (1) {
        // Reading the command using the "read" function
        bytesRead = read(STDIN_FILENO, buf, BUFSIZE - 1);
        if (bytesRead <= 0) {
            perror("Read error");  // If the command could not be read, display "Read error"
            exit(EXIT_FAILURE);
        }

        // Adding a null character to process the string
        buf[bytesRead - 1] = '\0'; // Replaces '\n' with '\0'

	check_exit_command(buf);  //Q3

	//Q5 : Measure the start time
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);  

        // Tokenize the input command to separate command and arguments
        char *argv[BUFSIZE / 2 + 1];  // Maximum number of arguments
        tokenize_command(buf, argv);

        // Handle redirection and adjust input/output file descriptors
        int input_fd = STDIN_FILENO;  // Default stdin
        int output_fd = STDOUT_FILENO;  // Default stdout
        handle_redirection(argv, &input_fd, &output_fd);

        // Creating a child process to execute the command (with fork)
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error during fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            pid_t child_pid = getpid();
	    printf("PID du processus fils : %d\n", child_pid);

            

            //execlp(buf, buf, NULL); // Replaces the child process with the execution of the entered command ("buf") (Q2)
            execvp(argv[0], argv);
            perror("Command not found");  // If the command is not found or cannot be executed
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0); // Waits for the child process to finish and retrieves its status
	    // Measure the end time
	    clock_gettime(CLOCK_MONOTONIC, &end);
	    handle_process_status(status);  //Q4
        }

        char prompt[] = "enseash % "; // Waiting for a new command
        write(STDOUT_FILENO, prompt, strlen(prompt));
    }
}

