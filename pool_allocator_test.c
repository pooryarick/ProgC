#include "pool_allocator.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void pool_init_test() {
  pool_allocator *a = pool_init(5, 4);
  assert(a != NULL_SIZE);
  assert(a->chunks_num == 5);
  destruct_allocator(a);
}
void pool_alloc_test() {
  pool_allocator *a = pool_init(2, 4);
  void *p1 = pool_alloc(a);
  assert(p1 != NOT_ENOUGH_MEMORY);
  void *p2 = pool_alloc(a);
  assert(p2 != NOT_ENOUGH_MEMORY);
  void *p3 = pool_alloc(a);
  assert(p3 == NOT_ENOUGH_MEMORY);
  destruct_allocator(a);
}
void pool_free_test() {
  pool_allocator *a = pool_init(3, 4);
  void *p1 = pool_alloc(a);
  void *p2 = pool_alloc(a);
  pool_free(a, p1);
  void *p3 = pool_alloc(a);
  assert(p3 == p1);
  destruct_allocator(a);
}
int main() {
  pool_init_test();
  pool_alloc_test();
  pool_free_test();
}
