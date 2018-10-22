#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

int main(void) {
    int my_array[ARRAY_SIZE];
    int i;
    double total = 0.0;
    
    for (i = 0; i < ARRAY_SIZE; i++) {
        my_array[i] = rand() % ARRAY_SIZE; /* "%" is "mod", as in Java */
        total += my_array[i];
    }
    
    printf("The numbers are: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");
    printf("The average is: %f\n", total / ARRAY_SIZE);
    
    return EXIT_SUCCESS;
}
