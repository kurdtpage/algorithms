#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

static void array_sort(int *a, int n) {
    int p; /* for each item in a */
    int q; /* value to the left of p */
    int key; /* temporary value, holding p */
    
    for(p=1; p<n; p++){
        key = a[p];
        q = p-1;
        while(q>=0 && a[q]>key){
            a[q+1] = a[q];
            q = q-1;
        }
        a[q+1] = key;
    }
}

static void array_print(int *a, int n) {
    int i;
    
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

int main(void) {
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = emalloc(capacity * sizeof my_array[0]);

    while (1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = erealloc(my_array, capacity * sizeof my_array[0]);
        }
        my_array[itemcount++] = item;
    }

    array_sort(my_array, itemcount);
    array_print(my_array, itemcount);
    free(my_array);
    
    return EXIT_SUCCESS;
}
