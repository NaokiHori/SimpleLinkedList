#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "linked_list.h"


int main(void){
  list_t *list = NULL;
  // create
  {
    printf("--- create list ---\n");
    const char string[] = {"ello worl"};
    const size_t nitems_string = strlen(string);
    for(size_t loc = 0; loc < nitems_string; loc++){
      char c = string[loc];
      list_insert(&list, loc, c);
      list_output(list);
    }
    printf("-------------------\n");
  }
  // insert some components
  {
    printf("--- insert ---\n");
    size_t loc;
    char c;
    // intermediate
    loc = 4;
    c = ',';
    list_insert(&list, loc, c);
    list_output(list);
    // head
    loc = 0;
    c = 'h';
    list_insert(&list, loc, c);
    list_output(list);
    // tail
    list_get_length(&loc, list);
    c = 'd';
    list_insert(&list, loc, c);
    list_output(list);
    // out-of-range
    loc = 100;
    c = 'x';
    list_insert(&list, loc, c);
    list_output(list);
    printf("--------------\n");
  }
  // find
  {
    printf("--- find ---\n");
    int loc;
    char c;
    c = 'h';
    list_find(&loc, list, c);
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'o';
    list_find(&loc, list, c);
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'r';
    list_find(&loc, list, c);
    printf("'%c' is found at index % 3d\n", c, loc);
    c = 'i';
    list_find(&loc, list, c);
    printf("'%c' is found at index % 3d\n", c, loc);
    printf("------------\n");
  }
  // remove specific location
  {
    printf("--- remove ---\n");
    size_t loc;
    // remove intermediate
    loc = 5;
    list_remove(&list, loc);
    list_output(list);
    // remove head
    loc = 0;
    list_remove(&list, loc);
    list_output(list);
    // remove tail
    list_get_length(&loc, list);
    loc -= 1;
    list_remove(&list, loc);
    list_output(list);
    // out-of-range
    loc = 100;
    list_remove(&list, loc);
    list_output(list);
    printf("--------------\n");
  }
  // remove all
  {
    printf("--- remove all ---\n");
    while(true){
      size_t length;
      list_get_length(&length, list);
      if(length == 0){
        break;
      }else{
        list_remove(&list, 0);
      }
    }
    list_output(list);
    printf("------------------\n");
  }
  return 0;
}

