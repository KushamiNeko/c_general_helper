#include "../header/general_helper.h"

inline void *defenseCalloc(size_t numElements, size_t sizeOfObject) {
  void *re = calloc(numElements, sizeOfObject);
  if (re == NULL) {
    printf("The system is running out of memory!\n");
    printf("Abort software operation\n");
    exit(1);
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

char *pathJoin(const char *a, const char *b) {
  size_t sizeA = strlen(a);
  size_t sizeB = strlen(b);

  size_t sizeR = sizeA + sizeB + 2;

  char *r = (char *)defenseCalloc(1, sizeR);
  strcat(r, a);
  strcat(r, SYSTEM_PATH_SEPARATOR);
  strcat(r, b);
  strcat(r, "\0");

  return r;
}

char *pathGetBase(char *path) {
  char *a = path;
  char *base = path;
  char *sys = SYSTEM_PATH_SEPARATOR;

  while (strcmp(a, "\0") != 0) {
    if (*a == *sys) {
      base = a;
    }
    a++;
  }

  size_t sizeR = strlen(base);
  char *r = (char *)defenseCalloc(1, sizeR);
  strcat(r, ++base);
  r[sizeR - 1] = '\0';

  return r;
}

char *pathRemoveExt(char *path) {
  size_t i = strlen(path) - 3;
  char *r = (char *)defenseCalloc(1, i);
  strncpy(r, path, i - 1);
  r[i - 1] = '\0';

  return r;
}

int checkFileExist(const char *fileName) {
  struct stat st;
  int result = stat(fileName, &st);
  return result == 0;
}
