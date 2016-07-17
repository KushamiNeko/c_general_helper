#include "general_list.h"

#ifdef UNIT_TESTING
#define __malloc malloc
#include <cmockery/cmockery_override.h>
#else
#define __malloc defenseMalloc
#endif

struct GeneralList *generalListNew(void *data) {
  struct GeneralList *re;

  re = (struct GeneralList *)__malloc(sizeof(struct GeneralList));

  re->data = data;
  re->previous = NULL;
  re->next = NULL;
  //  re->head = NULL;
  //  re->end = NULL;

  return re;
}

void generalListAddItemStack(struct GeneralList **main,
                             struct GeneralList *item) {
  item->next = *main;
  (*main)->previous = item;
  *main = item;
}

void generalListAddItemQueue(struct GeneralList **main,
                             struct GeneralList *item) {
  struct GeneralList *p;

  p = *main;

  while (p->next != NULL) {
    p = p->next;
  }

  p->next = item;
  item->previous = p;
}

struct GeneralList *generalListPopItem(struct GeneralList **main) {
  struct GeneralList *p;

  p = *main;
  if (p->next != NULL) {
    *main = p->next;
  }

  p->next = NULL;
  p->previous = NULL;

  return p;
}

void generalListDelete(struct GeneralList **main) {
  struct GeneralList **p;
  struct GeneralList **temp;

  p = main;

  while ((*p) != NULL) {
    temp = &((*p)->next);
    free((*p)->data);
    (*p)->data = NULL;
    free(*p);
    *p = NULL;

    p = temp;
  }
}
