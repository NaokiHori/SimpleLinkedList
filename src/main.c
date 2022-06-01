#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "linked_list.h"


static int output(llist_t *node_root);

int main(void){
  // original data on stack
  char string[] = {"abcd efgh"};
  llist_t *node_root = NULL;
  // create linked list (append to the head of it)
  {
    printf("--- create list ---\n");
    const size_t nitems_string = strlen(string);
    for(size_t i = 0; i < nitems_string; i++){
      // pass reference to the original string
      llist_insert(&node_root, 0, (void *)(string+nitems_string-i-1), sizeof(char), false);
      output(node_root);
    }
    printf("-------------------\n");
  }
  // changing the original string
  //   results in the change of linked list
  //   since the data is just a reference (address)
  {
    printf("--- modify original string ---\n");
    printf("%s -> ", string);
    string[0] = 'e';
    string[1] = 'l';
    string[2] = 'l';
    string[3] = 'o';
    string[4] = ' ';
    string[5] = 'w';
    string[6] = 'o';
    string[7] = 'r';
    string[8] = 'l';
    printf("%s\n", string);
    output(node_root);
    printf("------------------------------\n");
  }
  // insert data to the defined linked list
  // NOTE: copy data and assign to the list
  {
    printf("--- insert ---\n");
    size_t loc;
    char c;
    // intermediate
    loc = 4;
    c = ',';
    llist_insert(&node_root, loc, &c, sizeof(char), true);
    output(node_root);
    // head
    loc = 0;
    c = 'h';
    llist_insert(&node_root, loc, &c, sizeof(char), true);
    output(node_root);
    // tail
    llist_get_nitems(&loc, node_root);
    c = 'd';
    llist_insert(&node_root, loc, &c, sizeof(char), true);
    output(node_root);
    // out-of-range
    loc = 100;
    c = 'x';
    llist_insert(&node_root, loc, &c, sizeof(char), true);
    output(node_root);
    printf("--------------\n");
  }
  // find
  {
    printf("--- find ---\n");
    int loc;
    char c;
    c = 'h';
    llist_find(&loc, node_root, &c, sizeof(char));
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'o';
    llist_find(&loc, node_root, &c, sizeof(char));
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'r';
    llist_find(&loc, node_root, &c, sizeof(char));
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'i';
    llist_find(&loc, node_root, &c, sizeof(char));
    printf("'%c' is found at index % 3d\n", c, loc);
    printf("------------\n");
  }
  // remove specific location
  {
    printf("--- remove ---\n");
    size_t loc;
    // remove intermediate
    loc = 5;
    llist_remove(&node_root, loc);
    output(node_root);
    // remove head
    loc = 0;
    llist_remove(&node_root, loc);
    output(node_root);
    // remove tail
    llist_get_nitems(&loc, node_root);
    loc -= 1;
    llist_remove(&node_root, loc);
    output(node_root);
    // out-of-range
    loc = 100;
    llist_remove(&node_root, loc);
    output(node_root);
    printf("--------------\n");
  }
  // remove all
  {
    printf("--- remove all ---\n");
    while(true){
      size_t nitems;
      llist_get_nitems(&nitems, node_root);
      if(nitems == 0){
        break;
      }else{
        llist_remove(&node_root, 0);
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
  for(size_t i = 0; i < nitems; node_curr = node_curr->node_next, i++){
    // regard void pointer "data" as a pointer to char
    fprintf(stream, "%c", *(char *)(node_curr->data));
  }
  fprintf(stream, "\n");
  return 0;
}

