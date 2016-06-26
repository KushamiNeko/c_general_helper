#include "../header/general_helper.h"
#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

#include <cmockery/cmockery.h>

static void pathJoinTest(void **state) {
  char *path = pathJoin("ab", "cd");
  char *sys = SYSTEM_PATH_SEPARATOR;
  assert(path[0] == 'a');
  assert(path[1] == 'b');
  assert(path[2] == *sys);
  assert(path[3] == 'c');
  assert(path[4] == 'd');
  assert(path[5] == '\0');
  assert(strlen(path) == 5);
}

static void pathGetBaseTest(void **state) {
  char *path = pathGetBase("ab/cd");
  assert(path[0] == 'c');
  assert(path[1] == 'd');
  assert(strlen(path) == 2);
}

static void pathRemoveExtTest(void **state) {
  char *path = pathRemoveExt("cd.jpg");
  assert(path[0] == 'c');
  assert(path[1] == 'd');
  assert(strlen(path) == 2);
}

static void checkFileExistTest(void **state) {
  int exists = checkFileExist("makefile");
  int nonexists = checkFileExist("hello");
  assert(exists == 1);
  assert(nonexists == 0);
}

int main(int argc, char **argv) {
  const UnitTest tests[] = {unit_test(pathJoinTest), unit_test(pathGetBaseTest),
                            unit_test(pathRemoveExtTest),
                            unit_test(checkFileExistTest)};

  return run_tests(tests, "general_helper");
}
