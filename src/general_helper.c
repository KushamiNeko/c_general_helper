#include "general_helper.h"

#ifdef UNIT_TESTING
#include <cmockery/cmockery_override.h>
#endif

inline void *defenseCalloc(size_t numElements, size_t sizeOfObject) {
  void *re = calloc(numElements, sizeOfObject);
  if (re == NULL) {
    printf("The system is running out of memory!\n");
    printf("Abort software operation\n");
    exit(EXIT_FAILURE);
  }

  return re;
}

inline void *defenseMalloc(size_t memorySize) {
  void *re = malloc(memorySize);
  if (re == NULL) {
    printf("The system is running out of memory!\n");
    printf("Abort software operation\n");
    exit(EXIT_FAILURE);
  }

  return re;
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
  size_t sizeA = strlen(a);
  size_t sizeB = strlen(b);
  size_t sizeS = strlen(s);

  size_t sizeR = sizeA + sizeB + sizeS + 1;
  if (sizeR == 1) {
    return NULL;
  }

  char *r = (char *)defenseCalloc(1, sizeR * sizeof(char));
  strcat(r, a);

  if (sizeS != 0) {
    strcat(r, s);
  }

  strcat(r, b);
  strcat(r, "\0");

  return r;
}

char *pathJoin(const char *a, const char *b) {
  size_t sizeA = strlen(a);
  size_t sizeB = strlen(b);

  size_t sizeR = sizeA + sizeB + 2;

  char *r = (char *)defenseCalloc(1, sizeR * sizeof(char));
  strcat(r, a);
  strcat(r, SYSTEM_PATH_SEPARATOR);
  strcat(r, b);
  strcat(r, "\0");

  return r;
}

char *pathGetBase(const char *path) {
  char *a = (char *)path;
  char *base = (char *)path;
  char *sys = SYSTEM_PATH_SEPARATOR;

  while (strcmp(a, "\0") != 0) {
    if (*a == *sys) {
      base = a;
    }
    a++;
  }

  size_t sizeR = strlen(base);
  char *r = (char *)defenseCalloc(1, sizeR * sizeof(char));
  strcat(r, ++base);
  r[sizeR - 1] = '\0';

  return r;
}

char *pathRemoveExt(const char *path) {
  size_t textLen = strlen(path);
  char *p = (char *)&(path[textLen - 1]);

  size_t newLen = 0;
  while (*p != '.') {
    p--;
    newLen++;

    if (newLen >= textLen) {
      return NULL;
    }
  }

  size_t reLen = textLen - newLen;
  char *r = (char *)defenseCalloc(1, reLen * sizeof(char));
  memcpy(r, path, reLen - 1);

  r[reLen - 1] = '\0';

  return r;
}

int fileExist(const char *fileName) {
  struct stat st;
  int result = stat(fileName, &st);
  return result == 0;
}

char *readFile(const char *file) {
  char *content = NULL;
  long length;
  FILE *f = fopen(file, "rb");
  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    rewind(f);
    content = (char *)defenseCalloc(1, (length * sizeof(char)) + 1);
    if (content) {
      fread(content, sizeof(char), length, f);
    }
    fclose(f);

    // add string end point "\0" to the end of the array
    content[length] = '\0';
  }

  return content;
}
