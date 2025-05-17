#include "hashtable.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashtable_init_test() {
  HashTable h;
  size_t capacity = 8;
  pool_allocator *a = pool_init(capacity, sizeof(item) + sizeof(const char *));
  assert(hashtable_init(&h, capacity, a, sizeof(const char *)) == 0);
  assert(h.capacity == capacity);
  hashtable_free(&h);
}
void hashtable_insert_test() {
  HashTable h;
  size_t capacity = 8;
  pool_allocator *a = pool_init(capacity, sizeof(item) + sizeof(const char *));
  hashtable_init(&h, capacity, a, sizeof(const char *));

  assert(hashtable_insert(&h, "44608", "Harry") == 0);
  assert(hashtable_insert(&h, "11392", "Peter") == 0);
  assert(hashtable_insert(&h, "16745", "Mike") == 0);
  assert(hashtable_insert(&h, "10897", "Tayler") == 0);
  hashtable_free(&h);
}
void hashtable_get_test() {
  HashTable h;
  size_t capacity = 8;
  pool_allocator *a = pool_init(capacity, sizeof(item) + sizeof(const char *));
  hashtable_init(&h, capacity, a, sizeof(const char *));
  hashtable_insert(&h, "44698", "Harry");
  hashtable_insert(&h, "11092", "Peter");
  hashtable_insert(&h, "16745", "Mike");
  hashtable_insert(&h, "10897", "Tayler");

  assert(strcmp(hashtable_get(&h, "44698"), "Harry") == 0);
  assert(strcmp(hashtable_get(&h, "11092"), "Peter") == 0);
  assert(strcmp(hashtable_get(&h, "16745"), "Mike") == 0);
  assert(strcmp(hashtable_get(&h, "10897"), "Tayler") == 0);
  hashtable_free(&h);
}

void hashtable_del_test() {
  HashTable h;
  size_t capacity = 8;
  pool_allocator *a = pool_init(capacity, sizeof(item) + sizeof(const char *));
  hashtable_init(&h, capacity, a, sizeof(const char *));
  hashtable_insert(&h, "44698", "Harry");
  hashtable_insert(&h, "11092", "Peter");
  hashtable_insert(&h, "16745", "Mike");
  hashtable_insert(&h, "10897", "Tayler");

  assert(strcmp(hashtable_get(&h, "16745"), "Mike") == 0);
  assert(hashtable_del(&h, "16745") == 0);
  assert(hashtable_get(&h, "16745") == NULL);
  hashtable_free(&h);
}

int main() {
  hashtable_init_test();
  hashtable_insert_test();
  hashtable_get_test();
  hashtable_del_test();
}
