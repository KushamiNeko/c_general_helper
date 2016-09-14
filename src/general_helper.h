#ifndef GENERAL_HELPER_H
#define GENERAL_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#ifdef _WIN32
#define SYSTEM_PATH_SEPARATOR "\\"
#else
#define SYSTEM_PATH_SEPARATOR "/"

#define DEFENSE_CALLOC(num, size, cbFail, cbData) \
  ({                                              \
    void* ptr;                                    \
    ptr = calloc(num, size);                      \
    if (ptr == NULL) {                            \
      cbFail(cbData);                             \
    }                                             \
    ptr;                                          \
  })

#define DEFENSE_MALLOC(size, cbFail, cbData) \
  ({                                         \
    void* ptr;                               \
    ptr = malloc(size);                      \
    if (ptr == NULL) {                       \
      cbFail(cbData);                        \
    }                                        \
    ptr;                                     \
  })

#define DEFENSE_FREE(ptr) \
  ({                      \
    free(ptr);            \
    ptr = NULL;           \
  })

void mallocFailAbort(void *data);

unsigned int euclidGCD(const unsigned int x, const unsigned int y);

double fit01(double src, double newMin, double newMax);

char *charJoin(const char *a, const char *b, const char *s);

char *pathJoin(const char *a, const char *b);

char *pathGetBase(const char *path);

char *pathRemoveExt(const char *path);

int fileExist(const char *fileName);

char *readFile(const char *file);

int copy_file(const char *src, const char *tar);

#endif
