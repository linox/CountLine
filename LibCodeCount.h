#include <stdio.h>
#include <stdlib.h>

void ShowHelp();
void CodeCount(char *file[], int code);
void CodeCountError(char *program, char *arg);
void ValidRunCmd(int argc, char *program[]);
void ValidRepeatedArgs(int numArgs, char *args[]);
void ValidArgs(int argc, char *argv[]);
void FixEqualsArgs(int argc, char *argv[]);
void StartReport(char *file[], int *lines, int *emptyLines, int *commentLines, int *commentMultiLines, int *mode);

int optionsHandler(int argc, char *argv[]);
int execution(int *comment, int *silent, char *argv[]);
