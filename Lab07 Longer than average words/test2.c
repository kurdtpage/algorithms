#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s){
    void *result = malloc(s);
    if(result == NULL){
        fprintf(stderr,"error");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_array(char **a, int n, double avg){
    if(n>0){
        if(strlen(a[0])>avg){
            printf("%s\n", a[0]);
        }
        print_array(a+1, n-1, avg);
    }
}

int main(void){
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words=0;
    double average = 0;
    int total=0;
    int i;

    while(num_words<ARRAY_LEN && 1==scanf("%79s",word)){
        wordlist[num_words] = emalloc((strlen(word)+1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    for(i=0; i<num_words; i++){
        total += strlen(wordlist[i]);
    }
    
    average = total/num_words;
    fprintf(stderr, "%.2f\n", average);

    print_array(wordlist, num_words, average);

    for(i=0; i<num_words; i++){
        free(wordlist[i]);
    }

    return EXIT_SUCCESS;
}
