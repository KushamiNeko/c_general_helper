#include "general_helper.h"

//#include <cmockery/pbc.h>
#include "debug_macro.h"

#ifdef UNIT_TESTING
#include <cmockery/cmockery_override.h>
#endif

void mallocFailAbort(void *data) {
  printf("HEAP MEMORY ALLOCATION FAILED!\n");
  printf("ABORT OPERATION!\n");
  exit(EXIT_FAILURE);
}

unsigned int euclidGCD(const unsigned int x, const unsigned int y) {
  unsigned int a, b, r;

  a = x;
  b = y;
  r = a % b;

  while (r != 0) {
    a = b;
    b = r;
    r = a % b;
  }

  return b;
}

double fit01(double src, double newMin, double newMax) {
  double re;

  if (src > 1.0f) {
    re = newMax;
  } else if (src < 0.0f) {
    re = newMin;
  } else {
    double newRange = newMax - newMin;
    re = (src * newRange) + newMin;
  }

  return re;
}

char *charJoin(const char *a, const char *b, const char *s) {
  REQUIRE(a != NULL);
  REQUIRE(b != NULL);
  REQUIRE(s != NULL);

  size_t sizeA = strlen(a);
  size_t sizeB = strlen(b);
  size_t sizeS = strlen(s);

  // REQUIRE(sizeA != 0);
  // REQUIRE(sizeB != 0);
  // REQUIRE(sizeS != 0);

  size_t sizeR = sizeA + sizeB + sizeS + 1;
  if (sizeR == 1) {
    return NULL;
  }

  ENSURE(sizeR != 0);

  // char *r = DEFENSE_CALLOC(1, sizeR * sizeof(char), mallocFailAbort, NULL);
  char *r = calloc(1, sizeR * sizeof(char));
  RETURN_NULL_ON_FAIL(r);

  ENSURE(r != NULL);

  strcat(r, a);

  if (sizeS != 0) {
    strcat(r, s);
  }

  strcat(r, b);
  strcat(r, "\0");

  ENSURE(r[sizeR - 1] == '\0');

  return r;
}

char *pathJoin(const char *a, const char *b) {
  REQUIRE(a != NULL);
  REQUIRE(b != NULL);

  size_t sizeA = strlen(a);
  size_t sizeB = strlen(b);

  REQUIRE(sizeA != 0);
  REQUIRE(sizeB != 0);

  size_t sizeR = sizeA + sizeB + 2;

  ENSURE(sizeR != 0);

  // char *r = DEFENSE_CALLOC(1, sizeR * sizeof(char), mallocFailAbort, NULL);
  char *r = calloc(1, sizeR * sizeof(char));
  RETURN_NULL_ON_FAIL(r);

  ENSURE(r != NULL);

  strcat(r, a);
  strcat(r, SYSTEM_PATH_SEPARATOR);
  strcat(r, b);
  strcat(r, "\0");

  ENSURE(r[sizeR - 1] == '\0');

  return r;
}

char *pathGetBase(const char *path) {
  REQUIRE(path != NULL);

  size_t textLen = strlen(path);
  REQUIRE(textLen != 0);

  char *p = (char *)&(path[textLen - 1]);
  ENSURE(p != NULL);

  char *base = (char *)path;
  char *sys = SYSTEM_PATH_SEPARATOR;

  while (1) {
    if (*p == *sys) {
      base = p;
      break;
    }
    p--;

    if (strcmp(p, path) == 0) {
      return NULL;
    }
  }

  ENSURE(base != NULL);

  size_t sizeR = strlen(base);
  ENSURE(sizeR != 0);

  // char *r = DEFENSE_CALLOC(1, sizeR * sizeof(char), mallocFailAbort, NULL);
  char *r = calloc(1, sizeR * sizeof(char));
  RETURN_NULL_ON_FAIL(r);

  ENSURE(r != NULL);

  strcat(r, ++base);
  r[sizeR - 1] = '\0';

  ENSURE(r[strlen(base)] == '\0');

  return r;
}

char *pathRemoveExt(const char *path) {
  REQUIRE(path != NULL);

  size_t textLen = strlen(path);
  REQUIRE(textLen != 0);

  char *p = (char *)&(path[textLen - 1]);
  ENSURE(p != NULL);

  size_t newLen = 0;
  while (*p != '.') {
    p--;
    newLen++;

    if (newLen >= textLen) {
      return NULL;
    }
  }

  ENSURE(p != NULL);

  size_t reLen = textLen - newLen;
  ENSURE(reLen != 0);

  // char *r = DEFENSE_CALLOC(1, reLen * sizeof(char), mallocFailAbort, NULL);
  char *r = calloc(1, reLen * sizeof(char));
  RETURN_NULL_ON_FAIL(r);

  ENSURE(r != NULL);

  memcpy(r, path, reLen - 1);

  r[reLen - 1] = '\0';

  return r;
}

int fileExist(const char *fileName) {
  REQUIRE(fileName != NULL);
  REQUIRE(strlen(fileName) != 0);

  struct stat st;
  int result = stat(fileName, &st);
  return result == 0;
}

char *readFile(const char *file) {
  REQUIRE(file != NULL);
  REQUIRE(strlen(file) != 0);
  REQUIRE(fileExist(file) == 1);

  char *content = NULL;
  long length;
  FILE *f = fopen(file, "rb");

  if (f) {
    ENSURE(f);

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    rewind(f);

    if (length == 0) {
      goto clean;
    }

    ENSURE(length != 0);

    //    content =
    //        DEFENSE_CALLOC(1, (length * sizeof(char)) + 1, mallocFailAbort,
    //        NULL);

    content = calloc(1, (length * sizeof(char)) + 1);
    RETURN_NULL_ON_FAIL(content);

    ENSURE(content);
    fread(content, sizeof(char), length, f);

    // add string end point "\0" to the end of the array
    content[length] = '\0';

  clean:
    fclose(f);
  }

  return content;
}

int copy_file(const char *src, const char *tar) {
  REQUIRE(src != NULL);
  REQUIRE(strlen(src) != 0);
  REQUIRE(fileExist(src) == 1);

  REQUIRE(tar != NULL);
  REQUIRE(strlen(tar) != 0);

  FILE *source, *target;

  source = fopen(src, "rb");
  if (source == NULL) {
    return 0;
  }

  ENSURE(source != NULL);

  fseek(source, 0, SEEK_END);
  long int sizeSrc = ftell(source);
  fseek(source, 0, SEEK_SET);

  target = fopen(tar, "wb");
  if (target == NULL) {
    fclose(source);
    return 0;
  }

  ENSURE(target != NULL);

  char ch;
  for (int i = 0; i < sizeSrc; i++) {
    ch = fgetc(source);
    fputc(ch, target);
  }

  fclose(source);
  fclose(target);

  return 1;
}
