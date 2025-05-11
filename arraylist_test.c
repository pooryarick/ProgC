#include "arraylist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_arraylist_init() {
  pool_allocator *alloc = pool_init(10, sizeof(void *));
  ArrayList list;

  int result = arraylist_init(&list, alloc);
  assert(result == SUCCESS);
  assert(list.size == 0);
  assert(list.capacity == INITIAL_CAPACITY);
  assert(list.data != NULL);
  assert(list.allocator == alloc);

  arraylist_free(&list);
  destruct_allocator(alloc);
}

void test_arraylist_add() {
  pool_allocator *alloc = pool_init(10, sizeof(void *));
  ArrayList list;
  arraylist_init(&list, alloc);

  int value1 = 42;
  int value2 = 99;

  assert(arraylist_add(&list, &value1, 0) == SUCCESS);
  assert(list.size == 1);
  assert(list.data[0] == &value1);

  assert(arraylist_add(&list, &value2, 0) == SUCCESS);
  assert(list.size == 2);
  assert(list.data[0] == &value2);
  assert(list.data[1] == &value1);

  assert(arraylist_add(&list, &value1, 3) == OUTSIDE_LIST);

  arraylist_free(&list);
  destruct_allocator(alloc);
}

void test_arraylist_get() {
  pool_allocator *alloc = pool_init(10, sizeof(void *));
  ArrayList list;
  arraylist_init(&list, alloc);

  int value = 42;
  arraylist_add(&list, &value, 0);

  assert(arraylist_get(&list, 0) == &value);

  assert(arraylist_get(&list, 1) == NULL);

  arraylist_free(&list);
  destruct_allocator(alloc);
}

void test_arraylist_del() {
  pool_allocator *alloc = pool_init(10, sizeof(void *));
  ArrayList list;
  arraylist_init(&list, alloc);

  int value1 = 42;
  int value2 = 99;
  arraylist_add(&list, &value1, 0);
  arraylist_add(&list, &value2, 1);

  assert(arraylist_del(&list, 0) == SUCCESS);
  assert(list.size == 1);
  assert(list.data[0] == &value2);

  assert(arraylist_del(&list, 1) == OUTSIDE_LIST);

  arraylist_free(&list);
  destruct_allocator(alloc);
}

void test_arraylist_expand() {
  pool_allocator *alloc = pool_init(10, sizeof(void *));
  ArrayList list;
  arraylist_init(&list, alloc);

  int values[5];
  for (int i = 0; i < 5; i++) {
    values[i] = i;
    assert(arraylist_add(&list, &values[i], i) == SUCCESS);
  }

  assert(list.capacity >= 5);
  assert(list.size == 5);
  for (int i = 0; i < 5; i++) {
    assert(*(int *)arraylist_get(&list, i) == i);
  }

  arraylist_free(&list);
  destruct_allocator(alloc);
}

void test_arraylist_expand_out_of_bounds() {
  pool_allocator *alloc = pool_init(9, sizeof(void *));
  ArrayList list;
  arraylist_init(&list, alloc);

  int values[9];
  for (int i = 0; i < 8; i++) {
    values[i] = i;
    assert(arraylist_add(&list, &values[i], i) == SUCCESS);
  }

  values[8] = 8;
  assert(arraylist_add(&list, &values[8], 8) == ALLOC_ERROR);

  assert(list.size == 8);
  for (int i = 0; i < 8; i++) {
    assert(*(int *)arraylist_get(&list, i) == i);
  }

  arraylist_free(&list);
  destruct_allocator(alloc);
}

void test_arraylist_null_cases() {
  ArrayList list;
  pool_allocator *alloc = NULL;

  assert(arraylist_init(&list, alloc) == ALLOC_ERROR);

  assert(arraylist_init(NULL, pool_init(10, sizeof(void *))) == ALLOC_ERROR);

  int value = 42;
  assert(arraylist_add(NULL, &value, 0) == ALLOC_ERROR);

  assert(arraylist_get(NULL, 0) == NULL);

  assert(arraylist_del(NULL, 0) == ALLOC_ERROR);

  assert(arraylist_free(NULL) == ALLOC_ERROR);
}

int main() {
  test_arraylist_init();
  test_arraylist_add();
  test_arraylist_get();
  test_arraylist_del();
  test_arraylist_expand();
  test_arraylist_expand_out_of_bounds();
  test_arraylist_null_cases();
  return 0;
}
