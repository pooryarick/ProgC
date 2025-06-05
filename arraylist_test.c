#include "arraylist.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_arraylist_init() {
  pool_allocator *allocator = pool_init(10, sizeof(int));
  ArrayList list;
  int result = arraylist_init(&list, allocator, sizeof(int));

  assert(result == SUCCESS);
  assert(list.allocator == allocator);
  assert(list.capacity == INITIAL_CAPACITY);
  assert(list.size == 0);
  assert(list.element_size == sizeof(int));
  assert(list.head != NULL);

  arraylist_free(&list);
  destruct_allocator(allocator);
}

void test_arraylist_add() {
  pool_allocator *allocator = pool_init(10, sizeof(int));
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int value1 = 42;
  int value2 = 100;

  assert(arraylist_add(&list, &value1, 0) == SUCCESS);
  assert(list.size == 1);

  int *result1 = (int *)arraylist_get(&list, 0);
  assert(*result1 == value1);

  assert(arraylist_add(&list, &value2, 0) == SUCCESS);
  assert(list.size == 2);

  int *result2 = (int *)arraylist_get(&list, 0);
  int *result3 = (int *)arraylist_get(&list, 1);
  assert(*result2 == value2);
  assert(*result3 == value1);

  arraylist_free(&list);
  destruct_allocator(allocator);
}

void test_arraylist_get() {
  pool_allocator *allocator = pool_init(10, sizeof(int));
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int value = 42;
  arraylist_add(&list, &value, 0);

  int *result = (int *)arraylist_get(&list, 0);
  assert(result != NULL);
  assert(*result == value);

  assert(arraylist_get(&list, 1) == NULL);
  assert(arraylist_get(NULL, 0) == NULL);

  arraylist_free(&list);
  destruct_allocator(allocator);
}

void test_arraylist_del() {
  pool_allocator *allocator = pool_init(10, sizeof(int));
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int value1 = 42;
  int value2 = 100;
  arraylist_add(&list, &value1, 0);
  arraylist_add(&list, &value2, 1);

  assert(arraylist_del(&list, 0) == SUCCESS);
  assert(list.size == 1);

  int *result = (int *)arraylist_get(&list, 0);
  assert(*result == value2);

  assert(arraylist_del(&list, 1) == OUTSIDE_LIST);
  assert(arraylist_del(NULL, 0) == ALLOC_ERROR);

  arraylist_free(&list);
  destruct_allocator(allocator);
}

void test_arraylist_free() {
  pool_allocator *allocator = pool_init(10, sizeof(int));
  ArrayList list;
  arraylist_init(&list, allocator, sizeof(int));

  int value = 42;
  arraylist_add(&list, &value, 0);

  assert(arraylist_free(&list) == SUCCESS);
  assert(list.head == NULL);
  assert(list.size == 0);
  assert(list.capacity == 0);
  assert(list.allocator == NULL);
  assert(list.element_size == 0);

  assert(arraylist_free(NULL) == ALLOC_ERROR);

  destruct_allocator(allocator);
}

int main() {
  test_arraylist_init();
  test_arraylist_add();
  test_arraylist_get();
  test_arraylist_del();
  test_arraylist_free();
  return 0;
}
