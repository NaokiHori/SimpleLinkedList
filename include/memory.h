#if !defined(MEMORY_H)
#define MEMORY_H

#include <stddef.h>

extern void *my_calloc(const size_t count, const size_t size);
extern void my_free(void *ptr);

#endif // MEMORY_H
