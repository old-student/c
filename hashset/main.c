#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashset.h"

#define MAX_LENGTH 256

/**
   Erases last newline character from a string
   @param is a null-terminated string
 */
void trim_newline(char *str);

/**
   Inserts all strings from a file into a hash set
   @param set is a pointer to a hash set
   @param file_name is a zero-terminated string with a file name
 */
void fill_hash_set(hash_set_t *set, const char *file_name);

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Error: input file is not specified\n");
    exit(EXIT_FAILURE);
  }
  // preparing a set
  hash_set_t *set = create_hash_set(16); 
  fprintf(stdout, "Reading file...\n");
  fill_hash_set(set, argv[1]);
  fprintf(stdout, "Done\n");

  // test string hits
  char line[MAX_LENGTH];
  while (fgets(line, MAX_LENGTH, stdin)) {
    trim_newline(line);
    if (strcmp(line, "exit") == 0)
      exit(0);
    fprintf(stdout, "%s\n", contains(set, line) ? "YES" : "NO");
  }
  
  // release memory
  free_hash_set(set);  
  return 0;
}

void trim_newline(char *str) {
  size_t len = strlen(str);
  if (str[len - 1] == '\n')
    str[len - 1] = '\0';
}

void fill_hash_set(hash_set_t *set, const char *file_name) {
  FILE *f = fopen(file_name, "r");
  if (!f) {
    fprintf(stderr, "Error: could not open file %s\n", file_name);
    exit(EXIT_FAILURE);
  }
  // read file line by line and fill out a set
  char line[MAX_LENGTH];
  while (fgets(line, MAX_LENGTH, f)) {
    trim_newline(line);
    insert(set, line);
  }
  fclose(f);
}
