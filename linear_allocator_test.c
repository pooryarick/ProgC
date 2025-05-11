#include "linear_allocator.h"
#include <assert.h>

void allocator_init_test() {
  lin_alloc *a = allocator_init(10);
  assert(a != NULL_SIZE);
  assert(a->capacity == 10);
  assert(a->used == 0);
  delete_allocator(a);
}
void linear_alloc_test() {
  lin_alloc *a = allocator_init(10);
  void *p1 = linear_alloc(a, 3);
  assert(p1 != NOT_ENOUGH_MEMORY);
  assert(a->used == 3);
  void *p2 = linear_alloc(a, 5);
  assert(p2 != NOT_ENOUGH_MEMORY);
  assert(a->used == 8);
  void *p3 = linear_alloc(a, 4);
  assert(p3 == NOT_ENOUGH_MEMORY);
  delete_allocator(a);
}
void linear_reset_test() {
  lin_alloc *a = allocator_init(10);
  void *p = linear_alloc(a, 3);
  linear_reset(a);
  assert(a->used == 0);
  delete_allocator(a);
}

int main() {
  allocator_init_test();
  linear_alloc_test();
  linear_reset_test();
}
