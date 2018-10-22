#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    char **keys;
    int *freqeuncies;
    int *stats;
    hashing_t method;
};

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
    int current_entries = h->capacity * percent_full / 100;
    double average_collisions = 0.0;
    int at_home = 0;
    int max_collisions = 0;
    int i = 0;

    if (current_entries > 0 && current_entries <= h->num_keys) {
        for (i = 0; i < current_entries; i++) {
            if (h->stats[i] == 0) {
                at_home++;
            }
            if (h->stats[i] > max_collisions) {
                max_collisions = h->stats[i];
            }
            average_collisions += h->stats[i];
        }

        fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full,
                current_entries, at_home * 100.0 / current_entries,
                average_collisions / current_entries, max_collisions);
    }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
    int i;

    fprintf(stream, "\n%s\n\n",
            h->method == LINEAR_P ? "Linear Probing" : "Double Hashing");
    fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
    fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
    fprintf(stream, "-----------------------------------------------------\n");
    for (i = 1; i <= num_stats; i++) {
        print_stats_line(h, stream, 100 * i / num_stats);
    }
    fprintf(stream, "-----------------------------------------------------\n\n");
}

/**
 * Prints information about the hash table such as the postion of a key, the
 * frequency of duplicates inserted and the number of collisions that occurred
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 */
void htable_print_entire_table(htable h, FILE *stream) {
  int i;
  char *word;

  fprintf(stream, "  Pos  Freq  Stats  Word\n");
  fprintf(stream, "----------------------------------------\n" );
  for( i = 0; i < h->capacity; i++) {
    if (NULL == h->keys[i]) {
      word = "\0";
    } else {
      word = h->keys[i];
    }
    fprintf(stream, "%5d %5d %5d   %s\n", i, h->freqeuncies[i], h->stats[i],
            word);
  }
}

/**
 * Takes a char** as input and for every char convert it to a number and add
 * the newly conveted character to an unsigned integer variable and return it
 *
 * @param word - the char* to conver to and integer
 */
static unsigned int htable_word_to_int(char *word){
    unsigned int result = 0;

    /*add an offset of size 31 bits multiplied by result to get an unsigned int*/
    while(*word != '\0'){
        result = (*word++ + 31 * result);
    }
    return result;
}

/**
 * Depending on the collision strategy provid a step amount to step through
 * the hash.
 *
 * @param h - the hash table.
 * @param key - the unsigned integer made from htable_word_to_int
 */
static unsigned int htable_step(htable h, unsigned int key){
  if(h->method == DOUBLE_H){
    return 1 + (key % (h->capacity -1));
  }
    return 1;
}

/**
 * Clean up the hashtable after its not used and any associated data.
 * Memory for the struct must be deallocated in reverse order, this is to
 * prevent losing pointer references to anything "inside" the struct.
 *
 * @param h - the hash table.
 */
void htable_free(htable h){
  free(h->stats);
  free(h->freqeuncies);  
  free(h->keys);
  free(h);
}

/**
 * Inserts the key into the hash table, uses a collision strategy that was
 * set using the constructor.
 *
 * @param str - the key to insert into the table
 * @param h - the hash table.
 */
int htable_insert(htable h, char *str){
    /*convert string to integer*/
    unsigned int index = htable_word_to_int(str) % h->capacity;
    unsigned int step = htable_step(h, htable_word_to_int(str));
    unsigned int num_collisions = 0;

    if(h->capacity == h->num_keys) {
      return 0;
    }

    while (1) {
      /*case of no string at current index*/
      if (NULL == h->keys[index]) {
        h->keys[index] = emalloc((strlen(str) +1) * sizeof str[0]);
        strcpy(h->keys[index], str);
        h->freqeuncies[index] = 1;
        h->stats[h->num_keys++] = num_collisions;
        return 1;
      }

      /*case of existing same key at index*/
      if(strcmp(h->keys[index], str) == 0) {
        h->freqeuncies[index]++;
        return h->freqeuncies[index];
      }
      /*step using collision resolution method*/
      index = (index + step) % h->capacity;
      num_collisions++;

    }
}

/**
 * Clean up the hashtable after its not used and any associated data.
 * Memory for the struct must be deallocated in reverse order, this is to
 * prevent losing pointer references to anything "inside" the struct.
 *
 * @param capacity - size to make the hash table.
 * @param hash_method - the type of method to use for hashing
 */
htable htable_new(int capacity, hashing_t hash_method) {
    int i;
    /*Allocate memory to the htable according to its size*/
    htable table = emalloc(sizeof *table);
    table->capacity = capacity;
    table->num_keys = 0;
    table->method = hash_method;

    /*allocate memory for the frequency array relative to table capacity*/
    table->freqeuncies = emalloc(table->capacity
                                * sizeof table->freqeuncies[0]);

    /*allocate memory for the keys based on the capacity and allocate enough
      memory to store the key*/
    table->keys = emalloc(table->capacity * sizeof table->keys[0]);

    /*allocate memory to states based on capacity*/
    table->stats = emalloc(table->capacity * sizeof table->stats[0]);

    /*set the frequency and initial key values to nothing*/
    for(i = 0; i < table->capacity; i++){
        table->stats[i] = 0;
        table->freqeuncies[i] = 0;
        table->keys[i] = NULL;
    }
    return table;
}

/**
 * Prints the hashtable frequency of duplicate inserts and the word associated
 * with it.
 * @param f - the function used to print the keys and frequency
 * @param h - the hash table.
 */
void htable_print(htable h, void f(int freq, char *word)){
  int i;
  for (i = 0; i < h->capacity; i++) {
    if (h->freqeuncies[i] != 0) {
      f(h->freqeuncies[i], h->keys[i]);
    }
  }
}

/**
 * Searches the hashtable for the key. Hashes the key first and uses the Hash
 * tables collision strategy in order to find the key same time it took to
 * insert.
 *
 * @param the key to search.
 * @param h - the hash table.
 */

int htable_search(htable h, char *str){
  int num_collisions = 0;
  unsigned int index = htable_word_to_int(str) % h->capacity;
  unsigned int step = htable_step(h, htable_word_to_int(str));

  while(1){
    if(NULL == h->keys[index]){
      return 0;
    }
    if(strcmp(h->keys[index], str) == 0){
      return h->freqeuncies[index];
    }
    num_collisions++;
    if (num_collisions == h->capacity) {
      return 0;
    }
    index = (index + step) % h->capacity;
  }
}
