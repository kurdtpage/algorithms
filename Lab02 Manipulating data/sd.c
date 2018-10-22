#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int reg;
    int winner = 0;
    double s1, s2, s3; /*judges scores*/
    double score; /*average*/
    double highest = 0;
    
    printf("Welcome to Dunedin figure skating.\n");
    /* make sure output is immediately written to screen */
    fflush(stdout);
    
    while(4 == scanf("%d%lg%lg%lg", &reg, &s1, &s2, &s3)){

        /*printf("reg:%d, s1:%f, s2:%f, s3:%f \n", reg, s1, s2, s3);*/
        
        if(s1<s2 && s1<s3){
            score = (s2 + s3)/2;
        }else if(s2<s1 && s2<s3){
            score = (s1 + s3)/2;
        }else{
            score = (s1 + s2)/2;
        }
        
        printf("Competitor %d got: %3.1f\n", reg, score);
        fflush(stdout);
        if(score > highest){
            winner = reg;
            highest = score;
        }

    }
    
    if(winner != 0){
        printf("The winner is competitor %d with a score of %3.1f\n", winner, highest);
    }else{
        printf("No winners today :(\n");
    }
    fflush(stdout);    
    
    return EXIT_SUCCESS;
}
