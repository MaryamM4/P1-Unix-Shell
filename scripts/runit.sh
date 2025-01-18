#!/bin/bash

# remove executable
echo "Removing previous executable: rm -f ./p1_shell.out"
rm -f ./p1_shell.out

# compile
echo "Compiling: gcc -Wall -Wextra *.c"
gcc -Wall -Wextra ../src/*.c -o p1_shell.out

# execute
echo "Executing: ./p1_shell.out"
./p1_shell.out
