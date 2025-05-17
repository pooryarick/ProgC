#include "pool_allocator.h"
#include <stdio.h>
#include <stdlib.h>

pool_allocator *pool_init(size_t chunks_num, size_t chunk_size) {
  pool_allocator *allocator = malloc(sizeof(pool_allocator));
  if (allocator == NULL || chunks_num == 0) {
    return NULL;
  }
  allocator->chunks_num = chunks_num;
  allocator->chunks = malloc(chunks_num * (chunk_size + sizeof(chunk)));
  allocator->free_chunk = allocator->chunks;
  chunk *ch = (chunk *)allocator->chunks;
  for (int i = 0; i < chunks_num - 1; i++) {
    chunk *new_chunk = (chunk *)((char *)ch + chunk_size + sizeof(chunk));
    ch->next = new_chunk;
    new_chunk->next = NULL;
    ch = new_chunk;
  }
  return allocator;
}

void *pool_alloc(pool_allocator *allocator) {
  if (allocator == NULL) {
    return NULL_SIZE;
  }
  if (allocator->free_chunk == NULL) {
    return NOT_ENOUGH_MEMORY;
  }
  chunk *ch = allocator->free_chunk;
  allocator->free_chunk = allocator->free_chunk->next;
  return ch;
}
void pool_free(pool_allocator *allocator, chunk *ptr) {
  ptr->next = allocator->free_chunk;
  allocator->free_chunk = ptr;
}
void destruct_allocator(pool_allocator *allocator) {
  free(allocator->chunks);
  free(allocator);
}
