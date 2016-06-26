#ifndef GENERAL_HELPER_H
#define GENERAL_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef UNIT_TESTING
#include <cmockery/cmockery_override.h>
#endif

#define SYSTEM_PATH_SEPARATOR "/"

void *defenseCalloc(size_t numElements, size_t sizeOfObject);
unsigned int euclidGCD(const unsigned int x, const unsigned int y);
double fit01(double src, double newMin, double newMax);

char *pathJoin(const char *a, const char *b);
char *pathGetBase(char *path);
char *pathRemoveExt(char *path);

int checkFileExist(const char *fileName);

#endif
