#ifndef GENERAL_HELPER_H
#define GENERAL_HELPER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SYSTEM_PATH_SEPARATOR "/"

extern void *defenseCalloc(size_t numElements, size_t sizeOfObject);
extern void *defenseMalloc(size_t memorySize);

extern unsigned int euclidGCD(const unsigned int x, const unsigned int y);
extern double fit01(double src, double newMin, double newMax);

extern char *charJoin(const char *a, const char *b, const char *s);

extern char *pathJoin(const char *a, const char *b);
extern char *pathGetBase(const char *path);
extern char *pathRemoveExt(const char *path);

extern int fileExist(const char *fileName);
extern char *readFile(const char *file);

#endif
