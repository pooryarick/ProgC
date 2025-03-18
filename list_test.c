#include "list.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void list_test_1() {
  node *head = create_list(0);
  assert(count(head) == 1 && find_node(head, 1) == 0);
  clean_memory(head);
}
void list_test_2() {
  node *head = create_list(0);
  add_to_start(&head, 10);
  assert(count(head) == 2 && find_node(head, 1) == 10);
  clean_memory(head);
}
void list_test_3() {
  node *head = create_list(0);
  add_to_start(&head, 10);
  add_to_end(head, 8);
  assert(count(head) == 3 && find_node(head, 3) == 8);
  clean_memory(head);
}
void list_test_4() {
  node *head = create_list(0);
  add_to_start(&head, 10);
  add_to_end(head, 8);
  add_by_number(head, 2, 100);
  assert(count(head) == 4 && find_node(head, 2) == 100);
  clean_memory(head);
}
void list_test_5() {
  node *head = create_list(0);
  add_to_start(&head, 10);
  add_to_end(head, 8);
  add_by_number(head, 2, 100);
  remove_node(head, 3);
  assert(count(head) == 3 && find_node(head, 3) == 8);
  clean_memory(head);
}
int main() {
  list_test_1();
  list_test_2();
  list_test_3();
  list_test_4();
  list_test_5();
  return 0;
}
