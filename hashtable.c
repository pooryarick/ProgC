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
int hashtable_init(HashTable *table, size_t capacity,
                   pool_allocator *allocator) {
  if (allocator == NULL || capacity == 0) {
    return -1;
  }
  table->capacity = capacity;
  allocator = pool_init(capacity, sizeof(item));
  table->allocator = allocator;
  table->items = allocator->chunks;
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
    if (table->items[i % table->capacity].is_employed == 0) {
      table->items[i % table->capacity].key = key;
      table->items[i % table->capacity].value = value;
      table->items[i % table->capacity].is_employed = 1;
      table->items[i % table->capacity].is_deleted = 0;
      return 0;
    }
  }
  return -1;
}
void *hashtable_get(HashTable *table, const char *key) {
  int index = hash(key, table->capacity);
  for (int i = index; i < table->capacity + index; i++) {
    if (table->items[i % table->capacity].is_employed == 0 &&
        table->items[i % table->capacity].is_deleted == 0) {
      return NULL;
    }
    if (table->items[i % table->capacity].is_employed == 1 &&
        table->items[i % table->capacity].is_deleted == 0 &&
        table->items[i % table->capacity].key == key) {
      return table->items[i % table->capacity].value;
    }
  }
  return NULL;
}
int hashtable_del(HashTable *table, const char *key) {
  int index = hash(key, table->capacity);
  for (int i = index; i < table->capacity + index; i++) {
    if (table->items[i % table->capacity].key == key) {
      table->items[i % table->capacity].key = NULL;
      table->items[i % table->capacity].value = NULL;
      table->items[i % table->capacity].is_deleted = 1;
      table->items[i % table->capacity].is_employed = 0;
      return 0;
    }
  }
  return -1;
}

void hashtable_free(HashTable *table) { destruct_allocator(table->allocator); }
