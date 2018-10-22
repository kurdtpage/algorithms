#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 100

void *emalloc(size_t s) {
    void *result = malloc(s);
    if(NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void print_words(char **a, int n, double avg){
    if(n > 0) {
        if(strlen(a[0]) > avg){
            printf("%s\n", a[0]);
        }
        print_words(a + 1, n - 1, avg);
    }
}

int main(void) {
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words;
    double average = 0.0;
    double total = 0.0;
    int i;
    num_words = 0;
    while(num_words < ARRAY_LEN && 1 == scanf("%79s", word)) {
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }
    
        
    for(i = 0; i < num_words; i++){
        total += strlen(wordlist[i]);
    }
    if(num_words>0){
        average = total / num_words;
        fprintf(stderr, "%.2f\n", average);
    }
    print_words(wordlist, num_words, average);
    
    for(i = 0; i < num_words; i++) {
        free(wordlist[i]);
    }
    return EXIT_SUCCESS;

}
