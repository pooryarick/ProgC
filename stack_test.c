#include "stack.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void stack_test_1() {
  Stack *st = create_stack(7);
  push(st, 3);
  push(st, 5);
  int *out = malloc(sizeof(int));
  assert(pop(st, out) == 0);
  assert(*out == 5);
  free(out);
  clean_memory(st);
}
void stack_test_2() {
  Stack *st = create_stack(2);
  push(st, 3);
  int *out = malloc(sizeof(int));
  assert(pop(st, out) == 0);
  assert(*out == 3);
  assert(pop(st, out) == STACK_IS_EMPTY);
  free(out);
  clean_memory(st);
}
void stack_test_3() {
  Stack *st = create_stack(2);
  assert(st->size == 2);
  push(st, 10);
  push(st, 2);
  push(st, 3);
  assert(st->size == 12);
  int *out = malloc(sizeof(int));
  assert(pop(st, out) == 0);
  assert(st->size == 2);
  clean_memory(st);
}

int main() {
  stack_test_1();
  stack_test_2();
  stack_test_3();
  return 0;
}
