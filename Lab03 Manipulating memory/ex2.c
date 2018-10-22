#include <stdio.h>
#include <stdlib.h>

void max_min(int *a, int n, int *max, int *min){
    int i;
    
    for(i=0; i<n; i++){
        if(a[i] < *min){
            *min = a[i];
        }
        if(a[i] > *max){
            *max = a[i];
        }
    }
    
}

int main(void) {
    int my_array[] = { 5, 2, 7, 3, 4 };
    int biggest = 0;
    int smallest = 65000;
    
    max_min(my_array, 5, &biggest, &smallest);
    printf("max value is %d, min value is %d\n", biggest, smallest);
    
    return EXIT_SUCCESS;
}
