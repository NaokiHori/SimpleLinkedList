#if !defined(LINKED_LIST_H)
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct llist_t_ {
  // pointer to the stored data
  void *data;
  // size of data
  size_t data_size;
  bool data_is_copied;
  // pointer to the next node
  void *next;
} llist_t;

/* get info of list */
extern int llist_get_nitems(size_t *nitems, llist_t *node_root);
extern int llist_find(int *loc, llist_t *node_root, const void *pattern, const size_t pattern_size);
/* modify list */
extern int llist_insert(llist_t **node_root, const size_t loc, void *data, const size_t size, bool do_copy);
extern int llist_remove(llist_t **node_root, const size_t loc);

#endif // LINKED_LIST_H
