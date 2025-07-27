/*
 * File: shell.c
 * Authors: Group 7: Francisco Ortega, Peter Nguyen, Kathy Nguyen
 * Course: Operating Systems
 * Assignment: Simple Shell
 * Due Date: July 28, 2025
 *
 * Description:
 *   This is a simple shell that runs in a loop, takes input from the user, 
 *   looks for the command inputted, and runs using the execv(). This loop will continue 
 *   until the user exits.
 */


//libaries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

//function to prompt the user
void printPrompt()
{
  printf("osshell$ ");
  fflush(stdout);
}
// Reads a line of input from the user and returns it
void readCommand(char* inputBuffer) {
  if (fgets(inputBuffer, MAX_CMDLINE, stdin) == NULL) {
    perror("fgets failed");
    exit(1);
  }

  // Remove trailing newline character
  size_t len = strlen(inputBuffer);
  if (len > 0 && inputBuffer[len - 1] == '\n') {
    inputBuffer[len - 1] = '\0';
  }
}
// Parses the input string into arguments
void parseCommand(char* inputBuffer, command_t* cmd) {
  char* token = strtok(inputBuffer, " ");
  int index = 0;

  // store the tokens as arguments until the max is reached
  while (token != NULL && index < MAX_CMDLINE - 1) {
    cmd->argv[index++] = token;
    token = strtok(NULL, " ");
  }

  cmd->argv[index] = NULL;  // null-terminate for execv
  cmd->argc = index;
}

// Parses the system PATH into an array of directories
int parsePath(char* dir[]) {
  
  char* pathEnv = getenv("PATH");
  char* token = strtok(pathEnv, ":");
  int count = 0;

  // loop will store the directories into an array until a certain set of conditions is met
  while (token != NULL && count < MAX_PATHS) {
    dir[count++] = token;
    token = strtok(NULL, ":");
  }

  dir[count] = NULL;  // null-terminate
  
  return count;
}
// Searches for the command in the directories from PATH
char* lookupPath(char* cmdName, char* dir[]) {
  static char fullPath[MAX_CMDLINE];

  // If command already has '/' (e.g., ./a.out), don't search PATH
  if (strchr(cmdName, '/') != NULL) {
    if (access(cmdName, X_OK) == 0) {
      return cmdName;
    }
    return NULL;
  }

  // if not, we can search the dir to find the file
  for (int i = 0; dir[i] != NULL; i++) {
    snprintf(fullPath, sizeof(fullPath), "%s/%s", dir[i], cmdName);
    if (access(fullPath, X_OK) == 0) {
      return fullPath;
    }
  }

  return NULL;  // not found
}


// main loop of the shell
int main() {
  char inputBuffer[MAX_CMDLINE];
  char* pathDirs[MAX_PATHS];
  command_t command;

  // prompts user to enter a command and executes until user exits
  while (1) {
    printPrompt();
    readCommand(inputBuffer);

    if (strcmp(inputBuffer, "exit") == 0) {
      break;
    }

    parseCommand(inputBuffer, &command);
    if (command.argc == 0) {
      continue;  // empty input
    }

    parsePath(pathDirs);
    char* cmdPath = lookupPath(command.argv[0], pathDirs);

    if (cmdPath == NULL) {
      printf("Command not found: %s\n", command.argv[0]);
      continue;
    }

    pid_t pid = fork();
    
    if (pid == 0) {
      // In child process
      execv(cmdPath, command.argv);
      perror("execv failed");
      exit(1);
    } else if (pid > 0) {
      // In parent process
      wait(NULL);
    } else {
      perror("fork failed");
    }
  }

  printf("MiniShell terminated.\n");
  return 0;
}
