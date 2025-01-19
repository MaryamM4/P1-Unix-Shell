#ifndef SHELL_H
#define SHELL_H

#include <assert.h>  // assert
#include <fcntl.h>   // O_RDWR, O_CREAT
#include <stdbool.h> // bool
#include <stdio.h>   // printf, getline
#include <stdlib.h>  // calloc
#include <string.h>  // strcmp
#include <unistd.h>  // pipe, fork, dup2, execvp, close, read

#define MAXLINE 80
#define PROMPT "osh> "

/*
fd=0 is the standard input (stdin) : READ
fd=1 is the standard output (cout) : WRITE
fd=2 (cerr)
*/
#define RD 0
#define WR 1

bool equal(char *a, char *b);
int fetchline(char **line);
int interactiveShell();
int runTests();
void processLine(char *line);
int main();

#endif