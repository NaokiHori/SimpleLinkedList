#if !defined(LINKED_LIST_H)
#define LINKED_LIST_H

#include <stddef.h>

typedef struct list_t_ {
  char data;
  void *next;
} list_t;

/* inspect list */
extern int list_get_length(size_t *length, list_t *list);
extern int list_output(list_t *list);
extern int list_find(int *loc, list_t *list, const char c);
/* modify list */
extern int list_insert(list_t **list, const size_t loc, const char c);
extern int list_remove(list_t **list, const size_t loc);

#endif // LINKED_LIST_H
