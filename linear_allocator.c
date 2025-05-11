#include "linear_allocator.h"
#include <stdio.h>
#include <stdlib.h>

lin_alloc *allocator_init(size_t size) {
  if (size == 0) {
    return NULL_SIZE;
  }
  lin_alloc *allocator = (lin_alloc *)malloc(sizeof(lin_alloc));
  allocator->capacity = size;
  allocator->used = 0;
  allocator->start = malloc(size);
  return allocator;
}
void *linear_alloc(lin_alloc *allocator, size_t size) {
  if (allocator->used + size > allocator->capacity) {
    return NOT_ENOUGH_MEMORY;
  }
  void *ptr = (char *)allocator->start + allocator->used;
  allocator->used += size;
  return ptr;
}
void linear_reset(lin_alloc *allocator) { allocator->used = 0; }

void delete_allocator(lin_alloc *allocator) {
  free(allocator->start);
  free(allocator);
}
