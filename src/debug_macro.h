#ifndef DEBUG_MACRO_H
#define DEBUG_MACRO_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG

#define ENSURE(expr) assert(expr)

#define ENSURE_MSG(expr, errMsg, ...)                                          \
  ({                                                                           \
    if ((expr) != true) {                                                      \
      printf(errMsg, ##__VA_ARGS__);                                           \
                                                                               \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  })

#define DEBUG_MESSAGE(m, ...) printf(m, ##__VA_ARGS__)

#else

#define ENSURE(expr)                                                           \
  do {                                                                         \
  } while (0)

#define ENSURE_MSG(expr, errMsg, ...)                                          \
  do {                                                                         \
  } while (0)

#define DEBUG_MESSAGE(m, ...)                                                  \
  do {                                                                         \
  } while (0)

#endif

#endif
