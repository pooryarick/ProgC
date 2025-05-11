#include "hashtable.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void hashtable_init_test() {
  HashTable h;
  pool_allocator *a;
  size_t capacity = 8;
  assert(hashtable_init(&h, capacity, a) == 0);
  assert(h.capacity == capacity);
  hashtable_free(&h);
}
void hashtable_insert_test() {
  HashTable h;
  pool_allocator *a;
  size_t capacity = 8;
  hashtable_init(&h, capacity, a);

  assert(hashtable_insert(&h, "+449992332216", "Harry Potter") == 0);
  assert(hashtable_insert(&h, "+11392367326", "Peter Parker") == 0);
  assert(hashtable_insert(&h, "+16745362126", "Mickey Mouse") == 0);
  assert(hashtable_insert(&h, "+10897875626", "Tayler Derdan") == 0);
  hashtable_free(&h);
}
void hashtable_get_test() {
  HashTable h;
  pool_allocator *a;
  size_t capacity = 8;
  hashtable_init(&h, capacity, a);
  hashtable_insert(&h, "+449992332216", "Harry Potter");
  hashtable_insert(&h, "+11392367326", "Peter Parker");
  hashtable_insert(&h, "+16745362126", "Mickey Mouse");
  hashtable_insert(&h, "+10897875626", "Tayler Derdan");

  assert(hashtable_get(&h, "+449992332216") == "Harry Potter");
  assert(hashtable_get(&h, "+11392367326") == "Peter Parker");
  assert(hashtable_get(&h, "+16745362126") == "Mickey Mouse");
  assert(hashtable_get(&h, "+10897875626") == "Tayler Derdan");
  hashtable_free(&h);
}

void hashtable_del_test() {
  HashTable h;
  pool_allocator *a;
  size_t capacity = 8;
  hashtable_init(&h, capacity, a);
  hashtable_insert(&h, "+449992332216", "Harry Potter");
  hashtable_insert(&h, "+11392367326", "Peter Parker");
  hashtable_insert(&h, "+16745362126", "Mickey Mouse");
  hashtable_insert(&h, "+10897875626", "Tayler Derdan");

  assert(hashtable_get(&h, "+449992332216") == "Harry Potter");
  assert(hashtable_del(&h, "+449992332216") == 0);
  assert(hashtable_get(&h, "+449992332216") == NULL);
  hashtable_free(&h);
}

int main() {
  hashtable_init_test();
  hashtable_insert_test();
  hashtable_get_test();
  hashtable_del_test();
}
