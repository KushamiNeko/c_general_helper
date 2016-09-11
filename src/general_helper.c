#include "general_helper.h"

#ifdef UNIT_TESTING
#include <cmockery/cmockery_override.h>
#endif

void mallocFailAbort(void *data) {
  printf("memory allocation failed!\n");
  printf("abort oeration!\n");
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
  size_t sizeA = strlen(a);
  size_t sizeB = strlen(b);
  size_t sizeS = strlen(s);

  size_t sizeR = sizeA + sizeB + sizeS + 1;
  if (sizeR == 1) {
    return NULL;
  }

  char *r = defenseCalloc(1, sizeR * sizeof(char), mallocFailAbort, NULL);
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

  char *r = defenseCalloc(1, sizeR * sizeof(char), mallocFailAbort, NULL);

  strcat(r, a);
  strcat(r, SYSTEM_PATH_SEPARATOR);
  strcat(r, b);
  strcat(r, "\0");

  return r;
}

char *pathGetBase(const char *path) {
  size_t textLen = strlen(path);
  char *p = (char *)&(path[textLen - 1]);

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

  size_t sizeR = strlen(base);
  char *r = defenseCalloc(1, sizeR * sizeof(char), mallocFailAbort, NULL);
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
  char *r = defenseCalloc(1, reLen * sizeof(char), mallocFailAbort, NULL);
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
    content =
        defenseCalloc(1, (length * sizeof(char)) + 1, mallocFailAbort, NULL);
    if (content) {
      fread(content, sizeof(char), length, f);
    }
    fclose(f);

    // add string end point "\0" to the end of the array
    content[length] = '\0';
  }

  return content;
}

void copy_file(const char *src, const char *tar) {
  FILE *source, *target;
  source = fopen(src, "rb");
  if (source == NULL) {
    printf("copy source failed\n");
    exit(1);
  }

  fseek(source, 0, SEEK_END);
  long int sizeSrc = ftell(source);
  fseek(source, 0, SEEK_SET);

  target = fopen(tar, "wb");
  if (target == NULL) {
    printf("copy target failed\n");
    fclose(source);
    exit(1);
  }

  char ch;
  for (int i = 0; i < sizeSrc; i++) {
    ch = fgetc(source);
    fputc(ch, target);
  }

  fclose(source);
  fclose(target);
}
