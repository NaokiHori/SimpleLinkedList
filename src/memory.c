#include <stdio.h>  // FILE, fprintf, stderr
#include <stdlib.h> // NULL, calloc, free, exit, EXIT_FAILURE
#include <stddef.h> // size_t
#include "memory.h" // my_calloc, my_free


void *my_calloc(const size_t count, const size_t size){
  FILE *stream = stderr;
  void *ptr = calloc(count, size);
  if(ptr == NULL){
    fprintf(stream, "memory allocation error\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void my_free(void *ptr){
  free(ptr);
  ptr = NULL;
}

