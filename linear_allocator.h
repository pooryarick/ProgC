#include <stdio.h>
typedef struct {
  char *start;
  size_t capacity;
  size_t used;
} lin_alloc;
#define NOT_ENOUGH_MEMORY NULL
#define NULL_SIZE NULL
lin_alloc *allocator_init(size_t size);
void *linear_alloc(lin_alloc *allocator, size_t size);
void linear_reset(lin_alloc *allocator);
void delete_allocator(lin_alloc *allocator);
