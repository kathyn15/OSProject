# OSProject
Authors: Francisco Ortega, Peter Nguyen, Kathy Nguyen
Course: Operating Systems
Assignment: Simple Shell program
Due Date: July 28, 2025


# three files
* ReadMe
  - explains what everything is and how to use the files/shell
  - For the other two files, we have used the C programming language to build the shell
 
* Header file
  - Header file to define constants and struct for commands
  - declare function protoypes
 

* Main code file
  - libaries
  - functions for the shell like prompting, parsing, and searching for an executable path
  - we do this by creating a child process to execute the command using the function execv()
  - there is a main loop that will repeat until the user exits
