#ifndef COMMON_H

#define COMMON_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5000

int validateString(char *, int, int);
void tryPipe(int[]);
int tryOpen(char *, int, int);
void tryClose(int);
int tryFork();
int readMax(int, char *, int);
void readAll(int, char *, int);
void writeAll(int, char *, int);

#endif
