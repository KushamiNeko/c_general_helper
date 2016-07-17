#ifndef GENERAL_LIST_H
#define GENERAL_LIST_H

#include "general_helper.h"
#include <stdlib.h>

struct GeneralList {
  void *data;
  struct GeneralList *previous;
  struct GeneralList *next;

  //  struct GeneralList *head;
  //  struct GeneralList *end;
};

extern struct GeneralList *generalListNew(void *data);

extern void generalListAddItemStack(struct GeneralList **main,
                                    struct GeneralList *item);

extern void generalListAddItemQueue(struct GeneralList **main,
                                    struct GeneralList *item);

extern struct GeneralList *generalListPopItem(struct GeneralList **main);

// void generalListDeleteItem(struct GeneralList **main, struct GeneralList
// *item);

extern void generalListDelete(struct GeneralList **main);
// extern void generalListDelete(void *p);

#endif
