#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void multiply_by_3(int *a, int n) { /* note: pass int *a rather than int a[] */
    int i;
    for (i = 0; i < n; i++) {
        a[i] *= 3; /* note: can still use [] notation */
    }
}

int main(void) {
    int my_array[ARRAY_SIZE];
    int counter = 0;
    int i;
    
    printf("Type 10 integers:\n");
    while (counter < ARRAY_SIZE && 1 == scanf("%d", &my_array[counter])) {
        counter++;
    }

    printf("Here they are multiplied by 3:\n");
    multiply_by_3(my_array, counter);
    for (i = 0; i < counter; i++) {
        printf("%d\n", my_array[i]);
    }
    
    return EXIT_SUCCESS;
}
