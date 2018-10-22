#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"

struct htablerec {
    int capacity;
    int num_keys;
    int *frequencies;
    char **keys;
};

htable htable_new(int capacity) {
    int i;
    /* declare a htable and allocate memory as appropriate */
    htable new_htable = emalloc(sizeof *new_htable);
    /* initialise the htable's capacity and number of keys appropriately */
    new_htable->capacity = capacity;
    new_htable->num_keys = 0;
    /* allocate htable's frequency array to be able to store enough integers */
    new_htable->frequencies = emalloc(capacity * sizeof *new_htable->frequencies);
    /* allocate htable's keys array to be able to store enough strings */
    new_htable->keys = emalloc(capacity * sizeof *new_htable->keys);
    /* set each frequency and key to their initial values */
    for(i=0; i<capacity; i++){
        new_htable->frequencies[i] = 0;
        new_htable->keys[i] = NULL;
    }
    /* return the hash table */
    return new_htable;
}

void htable_free(htable h){
    int i;
    for(i=0; i<h->capacity; i++){
        h->frequencies[i] = 0;
        h->keys[i] = NULL;
    }
    free(h);
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *item){
    
    /* convert item to int */
    int item_int = htable_word_to_int(item);
    /* calculate step */
    int step = htable_step(h, item_int);
    /* position = int % capacity */
    int position = item_int % h->capacity;
    /* check string at that position */
    if(h->keys[position]==NULL){
        /* 1 */
        h->keys[position] = item;
        h->frequencies[position] = 1;
        h->num_keys++;
        return 1;
    }else{
        if(h->keys[position]==item){
            /* 2 */
            h->frequencies[position]+=step;
            return h->frequencies[position];
        }else{
            /* 3 */
            for(;;){
                if(h->keys[position]==NULL || h->keys[position]==item){
                    if(h->keys[position]==NULL){
                        /* 3a */
                        h->keys[position] = item;
                        h->frequencies[position] = 1;
                        h->num_keys++;
                        return 1;
                    }else{
                        /* 3b */
                        h->frequencies[position]+=step;
                        return h->frequencies[position];
                    }
                }else{
                    /* 3c */
                    position++;
                    if(position > h->capacity){
                        /* loop back around to start of array */
                        position = 0;
                    }
                }
            }
        }
    }
    return 0;
}

void htable_print(htable h, FILE *dest){
    int i;
    printf("htable_print:\n");
    for(i=0; i<h->capacity; i++){
        if(h->frequencies[i] > 0){
            fprintf(dest, "There are %d %s's\n", h->frequencies[i], h->keys[i]);
        }
    }
}

static unsigned int htable_step(htable h, unsigned int i_key) {
    return 1 + (i_key % (h->capacity - 1));
}
