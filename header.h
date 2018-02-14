#ifndef HEAD_H
#define HEAD_H value

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char runMenu();
void displayBoard(int r, int c, char **board);

char **makeBoard(int r, int c);
void randomBoard(int r, int c, char **board);

void save(int r, int c, char **board);
int* load(char ***board);

char **contOne(int r, int c, char **board);
char **cont(int r, int c, char **board, int steps);

#endif