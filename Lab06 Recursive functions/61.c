#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 80
#define ARRAY_LEN 10000

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void insertion_sort(char **a, int n) {
    int p; /* for each item in a */
    int q;
    char *key;
    
    for(p=1; p<n; p++){
        key = a[p];
        
        for(q=p-1; q>=0; q--){
            if(strcmp(a[q], key) > 0){
                a[q+1] = a[q];
            }else{
                break;
            }
        }
        a[q+1] = key;
    }
}

void print_array(char **a, int n) {
    if (n > 0) {
        printf("%s\n", a[0]);
        print_array(a + 1, n - 1);
    }
}

int main(void) {
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words;
    
    num_words = 0;
    while (num_words < ARRAY_LEN && 1 == scanf("%79s", word)) {
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    insertion_sort(wordlist, num_words);

    printf("\n");
    print_array(wordlist, num_words);
    
    return EXIT_SUCCESS;
}
