/*
 * File: shell.h
 * Authors: Group 7: Francisco Ortega, Peter Nguyen, Kathy Nguyen
 * Course: Operating Systems
 * Assignment: Simple Shell
 * Due Date: July 28, 2025
 *
 * Description:
 * We used C programming languagae for the header file for the shell program. 
   It defines some variables constants, a struct for command, and functions used by the shell.
 */


#ifndef SHELL_H
#define SHELL_H

// constants to define the max values
#define LINE 80 //max line length
#define MAX_ARGS 64 //max num of args
#define MAX_ARG_LEN 16 //max arg length
#define MAX_PATHS 64 //max num of paths
#define MAX_PATH_LEN 96 //max path length
#define MAX_CMDLINE 1024 //input buffer size
#define WHITESPACE " \t\n" //whitespace separators
#define TRUE 1 //make a true value 1

#ifndef NULL
#define NULL ((void *)0)
#endif

//typedef struct to group cmd variables together
typedef struct {
  char *name;
  int argc;
  char *argv[MAX_ARGS];
} command_t;


//prototypes for commands
void readCommand(char* inputBuffer);

// parses user input into arguments
void parseCommand(char* inputBuffer, command_t* cmd);

// parses the path into an array
int parsePath(char* dir[]);

// finds the full path of a command
char* lookupPath(char* cmdName, char* dir[]);

#endif
