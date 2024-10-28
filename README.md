## UID: 123456789

## Pipe Up

This code implements the shell redirect operation ("|") via a program pipe. 

## Building

To build the program, run make to compile. Then, ./pipe can be run followed by shell commands as arguments, each argument feeding into the next.

## Running
Example command:
./pipe ls cat wc
This command will print the number of files and directories twice, followed by the total number of characters across all file and directory name and newlines.When running in this project directory after running make, this will output "8 8 73". It takes the output of ls, redirects into cat, which then redirects its output to wc.

./pipe ps sort
sorts the current running processes in alphanumeric order (where numbers are less than letters).
Example output:
2892 pts/0 00:00:00 pipe
2893 pts/0 00:00:00 ps
716 pts/0  00:00:00 zsh
PID TTY        TIME CMD

Note that adding flags to commands is not supported.

## Cleaning up

To clean up binary files, run "make clean".
