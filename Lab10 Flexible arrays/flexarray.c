#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};
flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        /* do the old "double the capacity" trick */
        f->capacity *= 2;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    /* insert the item in the next free space */
    f->items[f->itemcount++] = num;
}
void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    
    for (i = 0; i < f->itemcount; i++) {
        printf("%d\n", f->items[i]);
    }
}
void flexarray_sort(flexarray f){
    /* insertion sort */
    int item; /* for each item in a */
    int left; /* value to the left of p */
    int temp; /* temporary value, holding p */

    int n = f->itemcount;
    
    for(item=1; item<n; item++){
        temp = f->items[item];
        left = item-1;
        while(left>=0 && f->items[left]>temp){
            f->items[left+1] = f->items[left];
            left--;
        }
        f->items[left+1] = temp;
    }
}
void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f);
}
