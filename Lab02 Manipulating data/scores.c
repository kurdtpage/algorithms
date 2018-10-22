#include <stdio.h>
#include <stdlib.h>
int main(void) {
    double s1, s2, s3; /*judges scores*/
    int return_code;
    printf("Welcome to Dunedin figure skating.\n");
    printf("Please enter the judges scores, separated by <enter>: ");
    /* make sure output is immediately written to screen */
    fflush(stdout);
    
    return_code = scanf("%lg%lg%lg", &s1, &s2, &s3);
    if (return_code != 3) {
        printf("Error: you need to enter 3 scores. return code is %d\n", return_code);
        return EXIT_FAILURE;
    }

    if(s1<s2 && s1<s3){
        printf("The average of 2 & 3 is: %3.1f\n", (s2+s3)/2);
    }else if(s2<s1 && s2<s3){
        printf("The average of 1 & 3 is: %3.1f\n", (s1+s3)/2);
    }else{
        printf("The average of 1 & 2 is: %3.1f\n", (s1+s2)/2);
    }

    fflush(stdout);
    return EXIT_SUCCESS;
}
