#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    /* variables */
    int i = 0;
    double j = 1.0;

    /* for loop */
    for(i = 0; i < 10; i++){
        printf("%3d %3.0f %6.3f\n", i, j, sqrt(j));
        j *= 2;
    }

    return EXIT_SUCCESS; /* defined in stdlib.h */
}
