#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "linked_list.h"


static int output(llist_t *node_root);

int main(void){
  // original data on stack
  const char string[] = {"ello worl"};
  llist_t *node_root = NULL;
  // create
  {
    printf("--- create list ---\n");
    const size_t nitems_string = strlen(string);
    for(size_t i = 0; i < nitems_string; i++){
      int retval;
      // check current number of items of the linked list
      // and append a node to the end of it
      size_t loc;
      retval = llist_get_nitems(&loc, node_root);
      if(retval != 0){
        printf("llist_get_nitems error\n");
      }
      // assign address of the original string
      retval = llist_insert(&node_root, loc, (void *)(string+loc), sizeof(char), false);
      if(retval != 0){
        printf("llist_insert error\n");
      }
      output(node_root);
    }
    printf("-------------------\n");
  }
  // insert data to the defined linked list
  // NOTE: copy data and assign to the list
  {
    printf("--- insert ---\n");
    size_t loc;
    char c;
    int retval;
    // intermediate
    loc = 4;
    c = ',';
    retval = llist_insert(&node_root, loc, &c, sizeof(char), true);
    if(retval != 0){
      printf("llist_insert error\n");
    }
    output(node_root);
    // head
    loc = 0;
    c = 'h';
    retval = llist_insert(&node_root, loc, &c, sizeof(char), true);
    if(retval != 0){
      printf("llist_insert error\n");
    }
    output(node_root);
    // tail
    llist_get_nitems(&loc, node_root);
    c = 'd';
    retval = llist_insert(&node_root, loc, &c, sizeof(char), true);
    if(retval != 0){
      printf("llist_insert error\n");
    }
    output(node_root);
    // out-of-range
    loc = 100;
    c = 'x';
    printf("error expected\n");
    retval = llist_insert(&node_root, loc, &c, sizeof(char), true);
    if(retval != 0){
      printf("llist_insert error\n");
    }
    output(node_root);
    printf("--------------\n");
  }
  // find
  {
    printf("--- find ---\n");
    int loc;
    char c;
    int retval;
    c = 'h';
    retval = llist_find(&loc, node_root, &c, sizeof(char));
    if(retval != 0){
      printf("llist_find error\n");
    }
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'o';
    retval = llist_find(&loc, node_root, &c, sizeof(char));
    if(retval != 0){
      printf("llist_find error\n");
    }
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'r';
    retval = llist_find(&loc, node_root, &c, sizeof(char));
    if(retval != 0){
      printf("llist_find error\n");
    }
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'i';
    retval = llist_find(&loc, node_root, &c, sizeof(char));
    if(retval != 0){
      printf("llist_find error\n");
    }
    printf("'%c' is found at index % 3d\n", c, loc);
    printf("------------\n");
  }
  // remove specific location
  {
    printf("--- remove ---\n");
    int retval;
    size_t loc;
    // remove intermediate
    loc = 5;
    retval = llist_remove(&node_root, loc);
    if(retval != 0){
      printf("llist_remove error\n");
    }
    output(node_root);
    // remove head
    loc = 0;
    retval = llist_remove(&node_root, loc);
    if(retval != 0){
      printf("llist_remove error\n");
    }
    output(node_root);
    // remove tail
    retval = llist_get_nitems(&loc, node_root);
    if(retval != 0){
      printf("llist_get_nitems error\n");
    }
    loc -= 1;
    retval = llist_remove(&node_root, loc);
    if(retval != 0){
      printf("llist_remove error\n");
    }
    output(node_root);
    // out-of-range
    loc = 100;
    printf("error expected\n");
    retval = llist_remove(&node_root, loc);
    if(retval != 0){
      printf("llist_remove error\n");
    }
    output(node_root);
    printf("--------------\n");
  }
  // remove all
  {
    printf("--- remove all ---\n");
    while(true){
      size_t nitems;
      int retval;
      retval = llist_get_nitems(&nitems, node_root);
      if(retval != 0){
        printf("llist_get_nitems error\n");
      }
      if(nitems == 0){
        break;
      }else{
        retval = llist_remove(&node_root, 0);
        if(retval != 0){
          printf("llist_remove error\n");
        }
      }
    }
    output(node_root);
    printf("------------------\n");
  }
  return 0;
}

static int output(llist_t *node_root){
  /*
   * output given linked list
   *   to a file stream,
   *   assuming type(data) is char
   */
  FILE *stream = stdout;
  // 1. get number of items of the given list
  size_t nitems;
  llist_get_nitems(&nitems, node_root);
  fprintf(stream, "list (nitems %3zu): ", nitems);
  // 2. walk through the linked list and print
  llist_t *node_curr = node_root;
  for(size_t i = 0; i < nitems; node_curr = node_curr->next, i++){
    // regard void pointer "data" as a pointer to char
    fprintf(stream, "%c", *(char *)(node_curr->data));
  }
  fprintf(stream, "\n");
  return 0;
}

