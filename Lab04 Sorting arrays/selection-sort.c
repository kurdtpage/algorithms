#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 30000

void selection_sort(int *a, int n) {
    int p; /* for each item in a */
    int q; /* partial loop through a to find min */
    int min; /* minimum value in a */
    int temp; /* temporary value (for swap) */
    
    for(p=0; p<n; p++){
        min = p;
        for(q=p+1; q<n; q++){
            if(a[q] < a[min]){
                min = q;
            }
        }
        if(min != p){
            temp = a[p];
            a[p] = a[min];
            a[min] = temp;
        }
    }
}

int main(void) {
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    start = clock();
    selection_sort(my_array, count);
    end = clock();
    
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end-start)/(double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
