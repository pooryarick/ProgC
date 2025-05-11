#include "arraylist.h"
#include <string.h>

int arraylist_init(ArrayList *list, pool_allocator *alloc) {
  if (list == NULL || alloc == NULL) {
    return ALLOC_ERROR;
  }

  list->allocator = alloc;
  list->capacity = INITIAL_CAPACITY;
  list->size = 0;
  list->data = pool_alloc(alloc);

  if (list->data == NULL) {
    return ALLOC_ERROR;
  }

  memset(list->data, 0, INITIAL_CAPACITY * sizeof(void *));
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
    memmove(&list->data[index + 1], &list->data[index],
            (list->size - index) * sizeof(void *));
  }

  list->data[index] = data;
  list->size++;
  return SUCCESS;
}

void *arraylist_get(ArrayList *list, size_t index) {
  if (list == NULL || index >= list->size) {
    return NULL;
  }

  return list->data[index];
}

int arraylist_del(ArrayList *list, size_t index) {
  if (list == NULL) {
    return ALLOC_ERROR;
  }

  if (index >= list->size) {
    return OUTSIDE_LIST;
  }

  memmove(&list->data[index], &list->data[index + 1],
          (list->size - index - 1) * sizeof(void *));
  list->data[list->size - 1] = NULL;
  list->size--;

  return SUCCESS;
}

int arraylist_free(ArrayList *list) {
  if (list == NULL) {
    return ALLOC_ERROR;
  }

  if (list->data != NULL) {
    pool_free(list->allocator, (chunk *)list->data);
  }

  list->data = NULL;
  list->size = 0;
  list->capacity = 0;
  list->allocator = NULL;

  return SUCCESS;
}

int expand(ArrayList *list) {
  if (list == NULL) {
    return ALLOC_ERROR;
  }
  size_t new_capacity = list->capacity * 2;

  if (new_capacity > list->allocator->chunks_num) {
    return ALLOC_ERROR;
  }

  void **new_data = pool_alloc(list->allocator);

  if (new_data == NULL) {
    return ALLOC_ERROR;
  }

  memcpy(new_data, list->data, list->size * sizeof(void *));
  memset(&new_data[list->size], 0,
         (new_capacity - list->size) * sizeof(void *));

  pool_free(list->allocator, (chunk *)list->data);
  list->data = new_data;
  list->capacity = new_capacity;

  return SUCCESS;
}
