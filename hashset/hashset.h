#ifndef HASHSET_H_  
#define HASHSET_H_

#include <stdio.h>

typedef struct _list_t_ {
  char *str;
  struct _list_t_ *next;
} list_t;

typedef struct _hash_set_t_ {
  size_t size;     // actual number of elements
  size_t capacity; // overall number of buckets
  list_t **buckets;
} hash_set_t;

/**
   Creates an empty hash set of specified capacity.
   @param is an initial capacity of hash set.
   @return a pointer to a created empty hash set
 */
hash_set_t* create_hash_set(size_t capacity);

/**
   Releases memory occupied by a hash set.
   @param hash_set is a pointer to a hash set.
 */
void free_hash_set(hash_set_t *hash_set);

/**
   Prints all elements of a hash set to a specified stream.
   @param stream is a file stream for output.
   @param hash_set is a pointer to a hash set.
 */
void print_hash_set(FILE *stream, const hash_set_t *hash_set);

/**
   Checks if a specified string already in a hash set.
   @param hash_set is a pointer to a hash set.
   @str is a null-terminated string.
   @return 1 if string already in a hash set and 0 otherwise.
*/
int contains(const hash_set_t *hash_set, const char *str);

/**
   Tries to put new string into a hash set.
   @param hash_set is a pointer to a hash set.
   @param str is a null-terminated string.
   @return integer value to describe what happened:
           0 - string is added to a hash set
	   1 - string is not added because of error
	   2 - string is already in a hash set
 */
int insert(hash_set_t *hash_set, const char *str);

#endif // HASHSET_H_
