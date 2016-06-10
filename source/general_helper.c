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
