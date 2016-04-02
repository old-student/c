#include <stdlib.h>
#include <string.h>
#include "hashset.h"

#define CRITICAL_LOAD_FACTOR 0.7

/**
   Computes the load factor of a hash set.
   @param hash_set is a pointer to a hash set.
   @return a value of the load factor. 
 */
double load_factor(const hash_set_t *hash_set) {
  return hash_set->size * 1.0 / hash_set->capacity;
}

/**
   Creates an empty hash set of specified capacity.
   @param is an initial capacity of hash set.
   @return a pointer to a created empty hash set
 */
hash_set_t* create_hash_set(int capacity) {
  if (capacity < 1) return NULL;

  hash_set_t *hash_set;
  // attempt to allocate memory for the hash set structure
  if ((hash_set = (hash_set_t*)malloc(sizeof(hash_set_t))) == NULL)
    return NULL;

  // attempt to allocate memory for the buckets
  if((hash_set->buckets = (list_t**)malloc(sizeof(list_t*) * capacity)) == NULL)
    return NULL;

  // initialize hash set
  hash_set->size = 0;
  hash_set->capacity = capacity;
  for (int i = 0; i < capacity; ++i)
    hash_set->buckets[i] = NULL;

  return hash_set;
}

/**
   Releases memory occupied by a hash set.
   @param hash_set is a pointer to a hash set.
 */
void free_hash_set(hash_set_t *hash_set) {
  if (!hash_set) return;  
  // free content of all buckets
  for(int i = 0; i < hash_set->capacity; ++i) {
    list_t *tmp, *list = hash_set->buckets[i];
    while (list) {
      tmp = list;
      list = list->next;
      free(tmp->str);
      free(tmp);
    }
  }
  free(hash_set->buckets);
  free(hash_set);
}

/**
   Prints all elements of a hash set to a specified stream.
   @param stream is a file stream for output.
   @param hash_set is a pointer to a hash set.
 */
void print_hash_set(FILE *stream, const hash_set_t *hash_set) {
  if (!hash_set) return;
  fprintf(stream, "Elements of hash set:\n");
  for(int i = 0; i < hash_set->capacity; ++i) {
    list_t *list = hash_set->buckets[i];
    while (list) {
      fprintf(stream, "%s\n", list->str);
      list = list->next;
    }
  }
}

/**
   Jenkins' One-at-a-Time hash for strings.
   @param hash_set is a pointer to a hash set.
   @str is a null-terminated string
   @return computed hash value.
*/
size_t hash(const hash_set_t *hash_set, const char *str) {
  size_t h = 0;
  for(; *str; ++str) {
    h += *str;
    h += (h << 10);
    h ^= (h >> 6);
  }
  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);
  return h % hash_set->capacity;
}

/**
   Checks if a specified string already in a hash set.
   @param hash_set is a pointer to a hash set.
   @str is a null-terminated string.
   @return 1 if string already in a hash set and 0 otherwise.
*/
int contains(const hash_set_t *hash_set, const char *str) {
  if (!hash_set) return 0;
  size_t hash_value = hash(hash_set, str);
  list_t *list = hash_set->buckets[hash_value];
  while (list) {
    if (strcmp(list->str, str) == 0)
      return 1;
    list = list->next;
  }
  return 0;
}

/**
   Changes the capacity of a hash set according to new capacity
   and rehashes all its elements.
   @param hash_set is a pointer to a hash set.
   @param new_capacity is a new capacity value.
*/
void resize(hash_set_t *hash_set, int new_capacity) {
  //printf("Resizing. New capacity = %d\n", new_capacity);
  hash_set_t *new_hash_set = create_hash_set(new_capacity);
  // put all elements from existing set into new one
  for(int i = 0; i < hash_set->capacity; ++i) {
    list_t *list = hash_set->buckets[i];
    while (list) {
      insert(new_hash_set, list->str);
      list = list->next;
    }
  }
  // swap two hash sets
  hash_set_t tmp_hash_set = *hash_set;
  *hash_set = *new_hash_set;
  *new_hash_set = tmp_hash_set;
  // free temporary hash set
  free_hash_set(new_hash_set);
}

/**
   Tries to put new string into a hash set.
   @param hash_set is a pointer to a hash set.
   @param str is a null-terminated string.
   @return integer value to describe what happened:
           0 - string is added to a hash set
	   1 - string is not added because of error
	   2 - string is already in a hash set
 */
int insert(hash_set_t *hash_set, const char *str) {
  if (!hash_set) return 1;
  if (contains(hash_set, str)) return 2;

  list_t *new_list;
  // attempt to allocate memory for new element 
  if((new_list = (list_t*)malloc(sizeof(list_t))) == NULL)
    return 1;

  size_t hash_value = hash(hash_set, str);
  // printf("String = %s, Hashval = %lu\n", str, hashval);  
  new_list->str = strdup(str);
  new_list->next = hash_set->buckets[hash_value];
  
  hash_set->buckets[hash_value] = new_list;
  hash_set->size++;
  if (load_factor(hash_set) >= CRITICAL_LOAD_FACTOR)
    resize(hash_set, hash_set->capacity * 2);

  return 0;
}
