#include "list.h"
#include <stdio.h>
#include <stdlib.h>

head *create_list() {
  head *new_list = (head *)malloc(sizeof(head));
  new_list->first = NULL;
  return new_list;
}
int count(head *h) {
  int cnt = 0;
  node *n = h->first;
  while (n != NULL) {
    cnt++;
    n = n->next;
  }
  return cnt;
}
void add_to_start(head *h, int v) {
  node *n = (node *)malloc(sizeof(node));
  n->value = v;
  n->next = h->first;
  h->first = n;
}
void add_to_end(head *h, int v) {
  if (h->first == NULL) {
    add_to_start(h, v);
  } else {
    node *n = h->first;
    while (n->next != NULL) {
      n = n->next;
    }
    node *m = (node *)malloc(sizeof(node));
    n->next = m;
    m->next = NULL;
    m->value = v;
  }
}

int add_by_index(head *h, int index, int v) {
  if (count(h) <= index || index < 0) {
    return INDEX_IS_OUT_OF_RANGE;
  }
  node *n = h->first;
  for (int i = 0; i < index - 1; i++) {
    n = n->next;
  }
  node *m = (node *)malloc(sizeof(node));
  m->value = v;
  m->next = n->next;
  n->next = m;
  return 0;
}

int remove_node(head *h, int index) {
  if (count(h) <= index || index < 0) {
    return INDEX_IS_OUT_OF_RANGE;
  }
  node *n = h->first;
  if (index == 0) {
    if (count(h) == 1) {
      free(h->first);
    } else {
      h->first = n->next;
      free(n);
    }
    return 0;
  }
  for (int i = 0; i < index - 1; i++) {
    n = n->next;
  }
  node *m = n->next;
  n->next = m->next;
  free(m);
  return 0;
}

int find_node(head *h, int index, node *out) {
  if (count(h) <= index || index < 0) {
    return INDEX_IS_OUT_OF_RANGE;
  }
  node *n = h->first;
  for (int i = 0; i < index; i++) {
    n = n->next;
  }
  out->value = n->value;
  return 0;
}

void clean_memory(head *h) {
  node *n = h->first;
  if (n->next == NULL) {
    free(n);
  } else {
    node *m = (node *)malloc(sizeof(node));
    while (n->next != NULL) {
      m = n->next;
      free(n);
      n = m;
    }
    free(m);
  }
}
