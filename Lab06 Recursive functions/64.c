#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i;
    
    printf("There %s %d program argument%s:\n",
           argc == 1 ? "is" : "are",
           argc-1,
           argc == 1 ? "" : "s");
    
    for (i = 1; i < argc; i++) {
        printf(" %s\n", argv[i]);
    }
    
    return EXIT_SUCCESS;
}
