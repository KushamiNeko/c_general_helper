#ifndef DEBUG_MACRO_H
#define DEBUG_MACRO_H

#include <assert.h>
#include <stdio.h>

#ifdef DEBUG

#define REQUIRE(expr) assert(expr)
#define ENSURE(expr) assert(expr)

#define DEBUG_MESSAGE(m, ...) printf(m, ##__VA_ARGS__)

#else

#define REQUIRE(expr) \
  do {                \
  } while (0)

#define ENSURE(expr) \
  do {               \
  } while (0)

#define DEBUG_MESSAGE(m, ...) \
  do {                        \
  } while (0)

#endif

#endif
