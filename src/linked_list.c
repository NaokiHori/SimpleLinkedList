#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include "memory.h"
#include "linked_list.h"


// maximum number of items
// more than 65535, sufficiently large for my purpose
#define NITEMS_MAX USHRT_MAX

// errorcode (return value)
#define RETVAL_SUCCESS ( 0)
#define RETVAL_FAILURE (-1)

int llist_get_nitems(size_t *nitems, llist_t *node_root){
  /*
   * compute nitems "nitems" of the given linked-list,
   *   whose root is "node_root"
   *
   * NOTE: maximum index is nitems-1
   *
   * param:
   *   nitems:    intent(out)
   *   node_root: intent(in)
   * return:
   *   RETVAL_SUCCESS: success
   *   RETVAL_FAILURE: too long (> NITEMS_MAX) linked list
   */
  // iterate until the current node is not allocated,
  //   i.e., node_curr == NULL
  llist_t *node_curr = node_root;
  for(*nitems = 0; node_curr != NULL; node_curr = node_curr->next, (*nitems)++){
    // abort when nitems is too large,
    //   which is to avoid infinte loop
    if(*nitems == NITEMS_MAX){
      return RETVAL_FAILURE;
    }
  }
  return RETVAL_SUCCESS;
}

int llist_find(int *loc, llist_t *node_root, const void *pattern, const size_t pattern_size){
  /*
   * find "pattern" in the given list,
   *   whose root is "node_root"
   *
   * when it is found,
   *   its location of the node is assigned to "loc"
   * otherwise -1 is set to "loc"
   *
   * NOTE: "not found" is an expected result
   *   and thus return RETVAL_SUCCESS
   * RETVAL_FAILURE is used for severer errors
   *   such as unexpected NULL detections
   *
   * WARNING: all allocated nodes are assumed to have
   *   data whose address is not NULL
   * Thus comparing NULLs
   *   (node_curr->data = NULL v.s. pattern = NULL) fails
   *
   * WARNING: user is responsible for giving
   *   consistent "pattern" (buffer) and "pattern_size" (buffer size)
   *
   * param:
   *   loc:       intent(out)
   *   node_root: intent(in)
   *   data:      intent(in)
   *   data_size: intent(in)
   * return :
   *   RETVAL_SUCCESS: checked all (found or not found does not matter)
   *   RETVAL_FAILURE: too long linked list, NULL comparison
   */
  /* 1. error check */
  // memcmp does not allow NULL
  if(pattern == NULL){
    return RETVAL_FAILURE;
  }
  // comparing zero-size patterns is useless
  if(pattern_size == 0){
    return RETVAL_FAILURE;
  }
  /* 2. loop */
  // iterate
  //   1. as long as node is allocated
  //   2. until pattern is found
  //   3. until cnt == NITEMS_MAX
  *loc = -1; // assume not found
  llist_t *node_curr = node_root;
  for(size_t cnt = 0; node_curr != NULL; node_curr = node_curr->next, cnt++){
    // do not compare if data sizes are different
    if(node_curr->data_size == pattern_size){
      // sanitise
      // memcmp does not allow NULL
      // check NULL of data (pattern)
      if(node_curr->data == NULL){
        return RETVAL_FAILURE;
      }
      // compare
      if(memcmp(node_curr->data, pattern, pattern_size) == 0){
        // two buffers have an identical pattern,
        //   so return its location
        //   and get out of the loop
        *loc = cnt;
        return RETVAL_SUCCESS;
      }
      // abort when cnt is too large,
      //   which is to avoid infinte loop
      if(cnt == NITEMS_MAX){
        return RETVAL_FAILURE;
      }
    }
  }
  // reach here if pattern not found
  // NOTE: "not found" is an expected result
  //   and thus return RETVAL_SUCCESS
  return RETVAL_SUCCESS;
}

int llist_insert(llist_t **node_root, const size_t loc, void *data, const size_t data_size, bool do_copy){
  /*
   * insert a node which contains data "data"
   *   at the given location (index) "loc"
   *
   * do nothing and return RETVAL_FAILURE
   *   if the specified location is out-of-range
   *
   * param:
   *   node_root: intent(in/out)
   *   loc:       intent(in)
   *   data:      intent(in)
   *   data_size: intent(in)
   *   do_copy:   intent(in)
   * return:
   *   RETVAL_SUCCESS: successfully appended
   *   RETVAL_FAILURE: out-of-range
   */
  /* 1. error handlings */
  {
    // already too many nodes
    size_t nitems;
    if(llist_get_nitems(&nitems, *node_root) == RETVAL_FAILURE){
      return RETVAL_FAILURE;
    }
    // specified location is out-of-range
    // (c.f. CURRENT maximum index = nitems-1)
    // (so loc == nitems means adding to the end)
    if(loc > nitems){
      return RETVAL_FAILURE;
    }
  }
  /* 2. move to the target location */
  // initially current node is the root node,
  //   and thus previous node is absent
  llist_t *node_prev = NULL;
  llist_t *node_curr = *node_root;
  for(size_t i = 0; i < loc; i++){
    // move forward, i.e., regard
    //   1. current node as previous node
    //   2. next    node as current  node
    node_prev = node_curr;
    node_curr = node_curr->next;
  }
  /* 3. initialise new node */
  llist_t *node_new = NULL;
  node_new = my_calloc(1, sizeof(llist_t));
  if(do_copy){
    // allocate new buffer to store COPIED data
    // this buffer should be freed when the node is freed
    //   so we need to remember this is indeed a copied data
    node_new->data = my_calloc(1, data_size);
    memcpy(node_new->data, data, data_size);
    node_new->data_is_copied = true;
  }else{
    // pass original address
    node_new->data = data;
    node_new->data_is_copied = false;
  }
  node_new->data_size = data_size;
  /* 4. update connection */
  if(node_prev == NULL){
    // this is the root node
    // update
    //                   |curr(root)|
    // to
    //   |new (root)| -> |curr      |
    // to do so,
    //   1. root       = new
    //   2. new ->next = curr
    *node_root = node_new;
  }else{
    // this is not the root node
    // update
    //   |prev| ->           |curr|
    // to
    //   |prev| -> |new | -> |curr|
    // to do so,
    //   1. prev->next = new
    //   2. new ->next = curr
    node_prev->next = node_new;
  }
  node_new->next = node_curr;
  return RETVAL_SUCCESS;
}

int llist_remove(llist_t **node_root, const size_t loc){
  /*
   * remove a node
   *   at the given location (index) "loc"
   *
   * do nothing and return RETVAL_FAILURE
   *   if the specified location is out-of-range
   *
   * param:
   *   node_root: intent(in/out)
   *   loc:       intent(in)
   * return:
   *   RETVAL_SUCCESS: successfully appended
   *   RETVAL_FAILURE: out-of-range
   */
  /* 1. error handlings */
  {
    size_t nitems;
    if(llist_get_nitems(&nitems, *node_root) == RETVAL_FAILURE){
      return RETVAL_FAILURE;
    }
    // link list has no component
    if(nitems == 0){
      return RETVAL_FAILURE;
    }
    // specified location is out-of-range
    // (c.f. maximum index = nitems-1)
    if(loc > nitems-1){
      return RETVAL_FAILURE;
    }
  }
  /* 2. move to the target location */
  // initially current node is the root node,
  //   and thus previous node is absent
  llist_t *node_prev = NULL;
  llist_t *node_curr = *node_root;
  for(size_t i = 0; i < loc; i++){
    // move forward, i.e., regard
    //   1. current node as previous node
    //   2. next    node as current  node
    node_prev = node_curr;
    node_curr = node_curr->next;
  }
  /* 3. update connection */
  if(node_prev == NULL){
    // this is the root node
    // update
    //   |curr(root)| -> |next      |
    // to
    //                   |next(root)|
    // to do so,
    //   root = next
    *node_root = node_curr->next;
  }else{
    // this is not the root node
    // update
    //   |prev| -> |curr| -> |next|
    // to
    //   |prev| ->           |next|
    // to do so,
    //   prev->next = next
    node_prev->next = node_curr->next;
  }
  /*4. clean-up */
  if(node_curr->data_is_copied){
    // the data stored in the node is not original
    //   which should be deallocated here
    // otherwise it is the reference to the original data
    //   for which the caller is responsible
    my_free(node_curr->data);
  }
  my_free(node_curr);
  return RETVAL_SUCCESS;
}

#undef NITEMS_MAX

#undef RETVAL_SUCCESS
#undef RETVAL_FAILURE

