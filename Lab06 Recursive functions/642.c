#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10000

void insertion_sort(int *a, int n) {
    int p; /* for each item in a */
    int q;
    int key;
    
    for(p=1; p<n; p++){
        key = a[p];
        
        for(q=p-1; q>=0; q--){
            /*if(strcmp(a[q], key) > 0){*/
            if(a[q] > key){
                a[q+1] = a[q];
            }else{
                break;
            }
        }
        a[q+1] = key;
    }
}

int main(int argc, char **argv) {
    FILE *infile;
    int my_array[ARRAY_SIZE];
    int num_items;
    int i;

    if(argc == 1){
        fprintf(stderr, "%s: you did not specify an input file\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (NULL == (infile = fopen(argv[1], "r"))) {
        fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }
    
    num_items = 0;
    while (num_items < ARRAY_SIZE &&
           1 == fscanf(infile, "%d", &my_array[num_items])) {
        num_items++;
    }
    
    fclose(infile);

    printf("Original array:\n");
    for (i = 0; i < num_items; i++) {
        printf("%d\n", my_array[i]);
    }
    
    insertion_sort(my_array, num_items);

    printf("\nSorted array:\n");
    for (i = 0; i < num_items; i++) {
        printf("%d\n", my_array[i]);
    }

    
    return EXIT_SUCCESS;
}
