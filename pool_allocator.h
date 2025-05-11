#include <stdio.h>

typedef struct chunk {
  struct chunk *next;
  char data[];
} chunk;

typedef struct {
  chunk *free_chunk;
  void *chunks;
  size_t chunks_num;
} pool_allocator;

pool_allocator *pool_init(size_t chunks_num, size_t chunk_size);
void *pool_alloc(pool_allocator *allocator);
void pool_free(pool_allocator *allocator, chunk *ptr);
void destruct_allocator(pool_allocator *allocator);
#define NULL_SIZE NULL
#define NOT_ENOUGH_MEMORY NULL
