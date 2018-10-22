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
    char *temp;
    
    for(p=1; p<n; p++){        
        if(strcmp(a[p], a[p+1]) > 0){
            temp = a[p];
            a[p] = a[p+1];
            a[p+1] = temp;
            /*
            strcpy(temp, a[p]);
            strcpy(a[p], a[p+1]);
            strcpy(a[p+1], temp);
            */
        }
    }
}

int main(void) {
    char word[STRING_LEN];
    char *wordlist[ARRAY_LEN];
    int num_words;
    int i;
    
    num_words = 0;
    while (num_words < ARRAY_LEN && 1 == scanf("%79s", word)) {
        wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
        strcpy(wordlist[num_words], word);
        num_words++;
    }

    insertion_sort(wordlist, num_words);
    
    for (i = 0; i < num_words; i++) {
        printf("%s\n", wordlist[i]);
        free(wordlist[i]);
    }
    
    return EXIT_SUCCESS;
}
