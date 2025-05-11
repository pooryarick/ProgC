#include "pool_allocator.h"
#include <stdio.h>
typedef struct {
  const char *key;
  void *value;
  int is_deleted;
  int is_employed;
} item;

typedef struct {
  size_t capacity;
  pool_allocator *allocator;
  item *items;
} HashTable;

int hashtable_init(HashTable *table, size_t capacity,
                   pool_allocator *allocator);
int hashtable_insert(HashTable *table, const char *key, void *value);
void *hashtable_get(HashTable *table, const char *key);
int hashtable_del(HashTable *table, const char *key);
void hashtable_free(HashTable *table);
