#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

#define PRE_AGREED 20

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
    /* insert the item in the last free space */
    f->items[f->itemcount++] = num;
}
void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for (i = 0; i < f->itemcount; i++) {
        printf("%d\n", f->items[i]);
    }
}
void flexarray_sort(flexarray f) {
    /* mergesort would be good */
    int p; /* for each item in a */
    int q; /* value to the left of p */
    int key; /* temporary value, holding p */

    int n = f->itemcount;
    
    for(p=1; p<n; p++){
        key = f->items[p];
        q = p-1;
        while(q>=0 && f->items[q]>key){
            f->items[q+1] = f->items[q];
            q = q-1;
        }
        f->items[q+1] = key;
    }
}

void insertion_sort(flexarray f) {
    int p; /* for each item in a */
    int q; /* value to the left of p */
    int key; /* temporary value, holding p */
    
    int n=f->itemcount;
    
    for(p=1; p<n; p++){
        key = f->items[p];
        q = p-1;
        while(q>=0 && f->items[q]>key){
            f->items[q+1] = f->items[q];
            q = q-1;
        }
        f->items[q+1] = key;
    }
}


void merge(flexarray f, int *w){
    int n=f->itemcount;
    /* initialise indices to point to the beginning of the left and right
       halves of array */
    int i = 0; /* left */
    int j = n/2; /* right */
    int k = 0;
    /* printf("merge1 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
    
    /* while there are elements in both halves of array { */
    while(i<n/2 && j<n){
        /* compare the elements at the current left and right indices */
        /* put the smallest into workspace and increment both the index it was
           taken from, and the index in workspace */
        if(f->items[i] < f->items[j]){
            w[k] = f->items[i];
            i++;
        }else{
            w[k] = f->items[j];
            j++;
        }
        k++;
    }
    /* printf("merge2 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
    
    /* add any remaining elements from left half of array to workspace */
    while(i<(n/2)){
        w[k] = f->items[i];
        i++;
        k++;
    }
    /* printf("merge3 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
    
    /* add any remaining elements from right half of array to workspace */
    while(j<n){
        w[k] = f->items[j];
        j++;
        k++;
    }
    /* printf("merge4 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
}


void quick_sort(flexarray f, int *w){
    int i = 0;
    int n = f->itemcount;
    
    /* if the array to be sorted has fewer than two elements then return */
    if(n<2) return;

    if(n < PRE_AGREED){
        insertion_sort(f);
    }else{
        /* call merge_sort on the first half of array a */
        quick_sort(f, w, n/2);
        /* call merge_sort on the second half of array a */
        quick_sort( f+(n/2), w, n-(n/2) );
        /* merge the two halves of array a into array w */
        merge(f, w);
        /* copy array w back into array a */
        for(i=0; i<n; i++){
            f->items[i] = w[i];
        }
    }
}


void quicksort(flexarray f){
    
    int tmp;
    /*if there are less than two items in the array then stop*/
    if(f->itemcount<2) return;
    /*let pivot hold a copy of the array's first element*/
    int pivot = f->items[0];
    /*let i be an index one to the left of the array's left-most position*/
    int i = -1;
    /*let j be an index one to the right of the array's right-most position*/
    int j = f->itemcount;
    /*loop forever {*/
    for(;;){
        /*increment i (at least once) while the value at position i < pivot*/
        do{
            i++;
        }while(f->items[i] < pivot);
        /*decrement j (at least once) while the value at position j > pivot*/
        do{
            j--;
        }while(f->items[j] > pivot);
        /*if i is to the left of j, then swap the values at their positions*/
        if(i<j){
            tmp = f->items[j];
            f->items[j] = f->items[i];
            f->items[i] = tmp;
        }
    /*else break out of the loop*/
    }else{
        break;
    }
    
    /*quicksort the left sub-array*/
    quicksort(f->items[i]);
    /*quicksort the right sub-array*/
    quicksort(f->items[j]);
}

void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f);
}
