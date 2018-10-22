#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

int main(void) {
    int item;

    /* create array, default size is 2 */
    flexarray my_flexarray = flexarray_new();

    while (1 == scanf("%d", &item)) {
        /* add to the array, if its too big, resize automatically */
        flexarray_append(my_flexarray, item);
    }

    flexarray_sort(my_flexarray);
    flexarray_print(my_flexarray);
    flexarray_free(my_flexarray);
    
    return EXIT_SUCCESS;
}
