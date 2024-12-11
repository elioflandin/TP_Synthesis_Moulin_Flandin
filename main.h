// main.h
#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

// Q1
void display_welcome_message();

// Q2
void handle_user_commands();

// Q3
void check_exit_command();

// Q4
void handle_process_status();

// Q5
long calcul_time();

// Q6
void tokenize_command();

// Q7
void handle_redirection();

#endif

