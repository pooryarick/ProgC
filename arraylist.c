#include "arraylist.h"
#include <string.h>

int arraylist_init(ArrayList *list, pool_allocator *alloc,
                   size_t element_size) {
  if (list == NULL || alloc == NULL) {
    return ALLOC_ERROR;
  }

  list->allocator = alloc;
  list->capacity = INITIAL_CAPACITY;
  list->size = 0;
  list->element_size = element_size;
  list->head = pool_alloc(alloc);

  if (list->head == NULL) {
    return ALLOC_ERROR;
  }

  memset(list->head, 0, list->capacity * list->element_size);
  return SUCCESS;
}

int arraylist_add(ArrayList *list, void *data, size_t index) {
  if (list == NULL || data == NULL) {
    return ALLOC_ERROR;
  }

  if (index > list->size) {
    return OUTSIDE_LIST;
  }

  if (list->size == list->capacity) {
    if (expand(list) != SUCCESS) {
      return ALLOC_ERROR;
    }
  }

  if (index < list->size) {
    memmove(list->head + (index + 1) * list->element_size,
            list->head + index * list->element_size,
            (list->size - index) * list->element_size);
  }

  memcpy(list->head + index * list->element_size, data, list->element_size);

  list->size++;
  return SUCCESS;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (list == NULL || index >= list->size) {
    return NULL;
  }

  return list->head + index * list->element_size;
}

int arraylist_del(ArrayList *list, size_t index) {
  if (list == NULL) {
    return ALLOC_ERROR;
  }

  if (index >= list->size) {
    return OUTSIDE_LIST;
  }

  memmove(list->head + index * list->element_size,
          list->head + (index + 1) * list->element_size,
          (list->size - index - 1) * list->element_size);

  memset(list->head + (list->size - 1) * list->element_size, 0,
         list->element_size);
  list->size--;

  return SUCCESS;
}

int arraylist_free(ArrayList *list) {
  if (list == NULL) {
    return ALLOC_ERROR;
  }

  if (list->head != NULL) {
    pool_free(list->allocator, list->head);
  }

  list->head = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = NULL;
  list->element_size = 0;

  return SUCCESS;
}

int expand(ArrayList *list) {
  if (list == NULL) {
    return ALLOC_ERROR;
  }

  list->capacity = list->capacity * 2;

  void *new_head = pool_alloc(list->allocator);

  if (new_head == NULL) {
    return ALLOC_ERROR;
  }

  if (new_head == NULL) {
    return ALLOC_ERROR;
  }

  memcpy(new_head, list->head, list->size * list->element_size);

  memset(new_head + list->size * list->element_size, 0,
         (list->capacity - list->size) * list->element_size);

  pool_free(list->allocator, list->head);
  list->head = new_head;

  return SUCCESS;
}
