#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "memory.h"
#include "linked_list.h"


int list_get_length(size_t *length, list_t *list){
  /*
   * compute length "length"
   *   of the given linked-list "list"
   *
   * NOTE: maximum index is length-1
   */
  list_t *node = list;
  *length = 0;
  while(node != NULL){
    (*length)++;
    if(node->next == NULL){
      break;
    }else{
      node = node->next;
    }
  }
  return 0;
}

int list_output(list_t *list){
  /*
   * output given list "list"
   *   to a file stream
   */
  FILE *stream = stdout;
  size_t length;
  list_get_length(&length, list);
  fprintf(stream, "list (length %3zu): ", length);
  list_t *node = list;
  while(node != NULL){
    fprintf(stream, "%c", node->data);
    if(node->next == NULL){
      break;
    }else{
      node = node->next;
    }
  }
  printf("\n");
  return 0;
}

int list_find(int *loc, list_t *list, const char c){
  /*
   * find a given component "c" (character for now)
   *   in the given list "list"
   *   and return its location (index) "loc"
   *
   * NOTE: -1 is assigned to "loc"
   *   when it is not found
   */
  list_t *node = list;
  *loc = -1;
  for(int cnt = 0; node != NULL; ){
    if(node->data == c){
      *loc = cnt;
      break;
    }
    if(node->next == NULL){
      break;
    }else{
      node = node->next;
      cnt++;
    }
  }
  return 0;
}

int list_insert(list_t **list, const size_t loc, const char c){
  /*
   * insert a node having data "c"
   *   at the given location (index) "loc"
   *
   * do nothing and return errorcode -1
   *   if the specified location is out-of-range
   */
  size_t length;
  list_get_length(&length, *list);
  // specified location exceed max index + 1
  // (gap exists)
  if(loc > length){
    return -1;
  }
  list_t *node_prev = NULL;
  list_t *node_curr = NULL;
  for(size_t i = 0; i <= loc; i++){
    if(i == 0){
      node_prev = NULL;
      node_curr = *list;
    }else{
      node_prev = node_curr;
      node_curr = node_curr->next;
    }
  }
  // initialise new node
  list_t *node_new = my_calloc(1, sizeof(list_t));
  node_new->data = c;
  node_new->next = node_curr;
  /*
   * update
   *   |prev|  |curr|
   * to
   *   |prev|  |new |  |curr|
   *
   * to do so,
   *   1. prev->next = new
   *   2. new ->next = curr
   */
  if(node_prev == NULL){
    // update head
    *list = node_new;
  }else{
    node_prev->next = node_new;
  }
  return 0;
}

int list_remove(list_t **list, const size_t loc){
  /*
   * remove a node
   *   at the given location (index) "loc"
   *
   * do nothing and return errorcode -1
   *   if the specified location is out-of-range
   */
  size_t length;
  list_get_length(&length, *list);
  // link list not initialised (no component)
  if(length == 0){
    return 0;
  }
  // specified location exceed max index
  const size_t max_index = length-1;
  if(loc > max_index){
    return -1;
  }
  list_t *node_prev = NULL;
  list_t *node_curr = NULL;
  list_t *node_next = NULL;
  for(size_t i = 0; i <= loc; i++){
    if(i == 0){
      node_prev = NULL;
      node_curr = *list;
    }else{
      node_prev = node_curr;
      node_curr = node_next;
    }
    node_next = node_curr->next;
  }
  if(node_prev == NULL){
    // update head
    *list = node_next;
  }else{
    node_prev->next = node_next;
  }
  my_free(node_curr);
  return 0;
}

