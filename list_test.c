#include "list.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void list_test_adding_to_start() {
  head *head = create_list();
  add_to_start(head, 3);

  assert(count(head) == 1);
  assert(head->first->value == 3);
  clean_memory(head);
}
void list_test_adding_to_end() {
  head *head = create_list();

  add_to_start(head, 10);
  add_to_end(head, 8);

  assert(count(head) == 2);
  assert(head->first->next->value == 8);
  clean_memory(head);
}
void list_test_adding_by_index() {
  head *head = create_list();
  add_to_start(head, 10);
  add_to_end(head, 8);

  assert(add_by_index(head, 1, 100) == 0);
  assert(count(head) == 3);
  assert(head->first->next->value == 100);
  clean_memory(head);
}
void list_test_removing() {
  head *head = create_list();

  add_to_start(head, 10);
  add_to_end(head, 8);
  add_by_index(head, 1, 100);

  assert(remove_node(head, 0) == 0);
  assert(count(head) == 2);
  assert(head->first->value == 100);
  assert(remove_node(head, 3) == INDEX_IS_OUT_OF_RANGE);
  clean_memory(head);
}

void list_test_find_node() {
  head *head = create_list();

  node *out = (node *)malloc(sizeof(node));
  add_to_start(head, 10);
  add_to_end(head, 8);
  add_by_index(head, 1, 100);
  assert(find_node(head, 0, out) == 0);
  assert(out->value == 10);
  assert(find_node(head, 1, out) == 0);
  assert(out->value == 100);
  assert(find_node(head, 2, out) == 0);
  assert(out->value == 8);
  assert(find_node(head, 3, out) == INDEX_IS_OUT_OF_RANGE);
}

int main() {
  list_test_adding_to_start();
  list_test_adding_to_end();
  list_test_adding_by_index();
  list_test_removing();
  list_test_find_node();
  return 0;
}
