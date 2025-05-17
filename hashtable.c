#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(const char *key, size_t capacity) {
  unsigned int hash = 0;
  while (*key) {
    hash ^= (unsigned char)(*key);
    key++;
  }
  return hash % capacity;
}
int hashtable_init(HashTable *table, size_t capacity, pool_allocator *allocator,
                   size_t value_size) {
  if (allocator == NULL || capacity == 0) {
    return -1;
  }
  table->capacity = capacity;
  table->value_size = value_size;
  table->allocator = allocator;
  table->items = (item *)allocator->chunks;
  for (int i = 0; i < capacity; i++) {
    item *new_item = (item *)pool_alloc(allocator);
    new_item->key = NULL;
    new_item->value = NULL;
    new_item->is_deleted = 0;
    new_item->is_employed = 0;
  }
  return 0;
}
int hashtable_insert(HashTable *table, const char *key, void *value) {
  int index = hash(key, table->capacity);
  for (int i = index; i < table->capacity + index; i++) {
    int cur_index = i % table->capacity;
    if (table->items[cur_index].is_employed == 0) {
      table->items[cur_index].value = &table->items[cur_index] + sizeof(item);
      memcpy(table->items[cur_index].value, value, table->value_size);
      table->items[cur_index].key = key;
      table->items[cur_index].is_employed = 1;
      table->items[cur_index].is_deleted = 0;
      return 0;
    }
  }
  return -1;
}
void *hashtable_get(HashTable *table, const char *key) {
  int index = hash(key, table->capacity);
  for (int i = index; i < table->capacity + index; i++) {
    int cur_index = i % table->capacity;
    if (table->items[cur_index].is_employed == 1 &&
        table->items[cur_index].key == key) {
      return table->items[cur_index].value;
    }
    if (table->items[cur_index].is_employed == 0 &&
        table->items[cur_index].is_deleted == 0) {
      return NULL;
    }
  }
  return NULL;
}
int hashtable_del(HashTable *table, const char *key) {
  int index = hash(key, table->capacity);
  for (int i = index; i < table->capacity + index; i++) {
    int cur_index = i % table->capacity;
    if (table->items[cur_index].key == key) {
      table->items[cur_index].key = NULL;
      table->items[cur_index].value = NULL;
      table->items[cur_index].is_deleted = 1;
      table->items[cur_index].is_employed = 0;
      return 0;
    } else if (table->items[cur_index].is_employed == 0) {
      return -1;
    }
  }
  return -1;
}

void hashtable_free(HashTable *table) { destruct_allocator(table->allocator); }
