#include "shell.h"

/**
 * Shell Program main entry point.
 *
 * If the --interactive flag is passed in the command line,
 * the program starts an interactive shell.
 * Otherwise, it runs a set of predefine tests.
 *
 * @param argc Number of command-line args. Expected to be 1 or 2.
 * @param arv Array of command-line arguments.
 * @return Result of the interactive shell or the tests.
 */
int main(int argc, char **argv) {
  // First argument is the program name.
  if (argc == 2 && equal(argv[1], "--interactive")) {
    return interactiveShell();

  } else {
    return runTests();
  }
}

/**
 * Starts interactive shell to listen
 * for user prompts and then process the command.
 *
 * The loops continues until the user enters "exit", or once
 * the end-of-file (EOF) is reached (^D, which sets line length to -1).
 *
 * @return 0 to indicate successful execution of shell.
 *         Does not indicate command processings are correct.
 */
int interactiveShell() {
  bool should_run = true;
  char *line = calloc(1, MAXLINE);

  while (should_run) {
    printf(PROMPT);
    fflush(stdout);
    int n = fetchline(&line);
    printf("read: %s (length = %d)\n", line, n);

    // ^D results in n == -1
    if (n == -1 || equal(line, "exit")) {
      should_run = false;
      continue;
    }

    if (equal(line, "")) {
      continue;
    }

    processLine(line);
  }

  free(line);
  return 0;
}

/**
 * Reads user entry, and if the command is valid,
 * a child process is created to execute the command.
 *
 * If the command ends '&', the child will run in the background.
 * Otherwise, if it ends with an ";", the parent process will wait
 * for the child process to finish.
 *
 * For each pipe ("|"), a child process will be spawned for
 * each commands in the pipeline, and the output of the preceding
 * is redirected as input into the following command.
 *
 * @param line Pointer to a string containing full command.
 */
void processLine(char *line) {
  printf("processing line: %s\n", line);
  // @todo

  /*
  1. fork a child process using fork()
  2. child process will invoke execvp() to replace current process image
  3. parent will invoke wait() unless command ended with &
  */
}

/**
 * Runs a number of predefined commands and prints output for verification.
 *
 * Tests covers a range of common shell commands,
 * including piping, redirection, background execution,
 * and a bonus "ascii" command.
 *
 * @return 0 to indicate successful test execution.
 *         Does not indicate test outputs are correct.
 */
int runTests() {
  printf("*** Running basic tests ***\n");
  char lines[7][MAXLINE] = {
      "ls",      "ls -al", "ls & whoami ;", "ls > junk.txt", "cat < junk.txt",
      "ls | wc", "ascii"};

  for (int i = 0; i < 7; i++) {
    printf("* %d. Testing %s *\n", i + 1, lines[i]);
    processLine(lines[i]);
  }

  return 0;
}

/**
 * Reads a line from the console and stores it in provided string.
 * Removes the newline character ('\n') at the end of the line.
 *
 * @param line Pointer to their string where the line will be stored.
 *             The string should be allocated before calling fetchLine.
 * @return Length of the line read, or -1 if the read failed.
 */
int fetchline(char **line) {
  size_t len = 0;
  size_t n = getline(line, &len, stdin);

  if (n > 0) {
    (*line)[n - 1] = '\0';
  }

  return n;
}

/**
 * @return True if the C-strings are equal.
 */
bool equal(char *a, char *b) { return (strcmp(a, b) == 0); }
