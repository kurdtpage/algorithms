#include <stdio.h>
#include <stdlib.h>

int main(void){
    /* variables */
    int f = 0;
    int g = 1;
    int temp_g = 0;
    int loop = 0;

    /* for loop */
    for(loop = 0; loop < 40; loop++){
        printf("%8d ", g);
        temp_g = g;
        g += f;
        f = temp_g;
        if(loop % 5 == 0){
            printf("\n");
        }
    }
    printf("\n");

    return EXIT_SUCCESS; /* defined in stdlib.h */
}
