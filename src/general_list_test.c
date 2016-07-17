#include "general_list.c"
#include <assert.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

#include <cmockery/cmockery.h>

static void generalListMemoryLeakStackTest(void **state) {
  int *data1 = (int *)malloc(10 * sizeof(int));

  for (int i = 0; i < 10; i++) {
    data1[i] = 100;
  }

  struct GeneralList *p = generalListNew(data1);
  assert(p->next == NULL);
  assert(p->previous == NULL);
  assert(((int *)p->data)[0] == 100);
  assert(((int *)p->data)[1] == 100);

  struct GeneralList *originalP = p;

  int *data2 = (int *)malloc(10 * sizeof(int));

  for (int i = 0; i < 10; i++) {
    data2[i] = 200;
  }

  struct GeneralList *q = generalListNew(data2);
  assert(q->next == NULL);
  assert(q->previous == NULL);
  assert(((int *)q->data)[0] == 200);
  assert(((int *)q->data)[1] == 200);

  generalListAddItemStack(&p, q);
  assert(p == q);
  assert(p->next == originalP);
  assert(p->previous == NULL);
  assert(*((int *)p->data) == 200);

  assert(p->next->previous == q);
  assert(p->next->next == NULL);
  assert(*((int *)p->next->data) == 100);

  generalListDelete(&p);
}

static void generalListMemoryLeakQueueTest(void **state) {
  int *data1 = (int *)malloc(10 * sizeof(int));

  for (int i = 0; i < 10; i++) {
    data1[i] = 100;
  }

  struct GeneralList *p = generalListNew(data1);
  assert(p->next == NULL);
  assert(p->previous == NULL);
  assert(((int *)p->data)[0] == 100);
  assert(((int *)p->data)[1] == 100);

  int *data2 = (int *)malloc(10 * sizeof(int));

  for (int i = 0; i < 10; i++) {
    data2[i] = 200;
  }

  struct GeneralList *q = generalListNew(data2);
  assert(q->next == NULL);
  assert(q->previous == NULL);
  assert(((int *)q->data)[0] == 200);
  assert(((int *)q->data)[1] == 200);

  generalListAddItemQueue(&p, q);
  assert(p == p);
  assert(p->next == q);
  assert(p->previous == NULL);
  assert(*((int *)p->data) == 100);

  assert(p->next->previous == p);
  assert(p->next->next == NULL);
  assert(*((int *)p->next->data) == 200);

  generalListDelete(&p);
}

static void generalListLargeTest(void **state) {
  int *data1 = (int *)malloc(10 * sizeof(int));

  for (int i = 0; i < 10; i++) {
    data1[i] = 100;
  }

  struct GeneralList *p = generalListNew(data1);

  for (int i = 0; i < 1000000; i++) {
    int *data2 = (int *)malloc(1000 * sizeof(int));

    for (int i = 0; i < 10; i++) {
      data2[i] = 200;
    }

    struct GeneralList *q = generalListNew(data2);
    generalListAddItemStack(&p, q);
  }

  generalListDelete(&p);
}

int main(int argc, char **argv) {
  const UnitTest tests[] = {
      unit_test(generalListMemoryLeakStackTest),
      unit_test(generalListLargeTest),
      unit_test(generalListMemoryLeakQueueTest),
  };

  return run_tests(tests, "general_list");
}
