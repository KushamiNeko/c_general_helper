#include "linear_math.c"
#include <assert.h>

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include <cmockery/cmockery.h>

// static void pathJoinTest(void **state) {
//  char *path = pathJoin("ab", "cd");
//  char *sys = SYSTEM_PATH_SEPARATOR;
//  assert(path[0] == 'a');
//  assert(path[1] == 'b');
//  assert(path[2] == *sys);
//  assert(path[3] == 'c');
//  assert(path[4] == 'd');
//  assert(path[5] == '\0');
//  assert(strlen(path) == 5);
//
//  free(path);
//}
//
// static void pathGetBaseTest(void **state) {
//  char *path = pathGetBase("ab/cd");
//  assert(path[0] == 'c');
//  assert(path[1] == 'd');
//  assert(strlen(path) == 2);
//
//  free(path);
//
//  path = pathGetBase("abcd");
//  assert(path == NULL);
//}
//
// static void pathRemoveExtTest(void **state) {
//  char *path = pathRemoveExt("cd.jpg");
//  assert(path[0] == 'c');
//  assert(path[1] == 'd');
//  assert(strlen(path) == 2);
//
//  free(path);
//
//  path = pathRemoveExt("acd.scala");
//  assert(path[0] == 'a');
//  assert(path[1] == 'c');
//  assert(path[2] == 'd');
//  assert(strlen(path) == 3);
//
//  free(path);
//
//  path = pathRemoveExt("acdscala");
//  assert(path == NULL);
//
//  if (path != NULL) {
//    free(path);
//  }
//}
//
// static void checkFileExistTest(void **state) {
//  int exists = fileExist("makefile");
//  int nonexists = fileExist("hello");
//  assert(exists == 1);
//  assert(nonexists == 0);
//}
//
// static void memoryLeakTest(void **state) {
//  int *p = defenseCalloc(10, sizeof(int), mallocFailAbort, NULL);
//  *p = 0;
//  free(p);
//}
//
// static void charJoinTest(void **state) {
//  char *new = charJoin("ab", "cd", "_");
//  assert(new[0] == 'a');
//  assert(new[1] == 'b');
//  assert(new[2] == '_');
//  assert(new[3] == 'c');
//  assert(new[4] == 'd');
//  assert(strlen(new) == 5);
//
//  free(new);
//
//  new = charJoin("ab", "cd", "");
//  assert(new[0] == 'a');
//  assert(new[1] == 'b');
//  assert(new[2] == 'c');
//  assert(new[3] == 'd');
//  assert(strlen(new) == 4);
//
//  free(new);
//
//  new = charJoin("", "", "_");
//  assert(new[0] == '_');
//  assert(strlen(new) == 1);
//
//  free(new);
//
//  new = charJoin("a", "", "_");
//  assert(new[0] == 'a');
//  assert(new[1] == '_');
//  assert(strlen(new) == 2);
//
//  free(new);
//
//  new = charJoin("", "b", "_");
//  assert(new[0] == '_');
//  assert(new[1] == 'b');
//  assert(strlen(new) == 2);
//
//  free(new);
//
//  new = charJoin("", "", "");
//  assert(new == NULL);
//
//  if (new != NULL) {
//    free(new);
//  }
//}

int main(int argc, char **argv) {
  const UnitTest tests[] = {
      //      unit_test(pathJoinTest),      unit_test(pathGetBaseTest),
      //      unit_test(pathRemoveExtTest), unit_test(checkFileExistTest),
      //      unit_test(memoryLeakTest),    unit_test(charJoinTest),
  };

  return run_tests(tests, "general_helper");
}
