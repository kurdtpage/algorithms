#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_MAX 100000

void print_array_r(int *a, int n) {
    /* recursive print */
    if (n > 0) {
        printf("%d\n", a[0]);
        print_array_r(a + 1, n - 1);
    }
}

void print_array(int *a, int n){
    /* non recursive print */
    int i;
    printf("{");
    for(i=0; i<n; i++){
        printf("%d,", a[i]);
    }
    printf("}\n");
}

void insertion_sort(int *a, int n) {
    int p; /* for each item in a */
    int q; /* value to the left of p */
    int key; /* temporary value, holding p */
    
    for(p=1; p<n; p++){
        key = a[p];
        q = p-1;
        while(q>=0 && a[q]>key){
            a[q+1] = a[q];
            q = q-1;
        }
        a[q+1] = key;
    }
}

void merge(int *a, int *w, int n){
    /* initialise indices to point to the beginning of the left and right
       halves of array */
    int i = 0; /* left */
    int j = n/2; /* right */
    int k = 0;
    /* printf("merge1 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
    
    /* while there are elements in both halves of array { */
    while(i<n/2 && j<n){
        /* compare the elements at the current left and right indices */
        /* put the smallest into workspace and increment both the index it was
           taken from, and the index in workspace */
        if(a[i] < a[j]){
            w[k] = a[i];
            i++;
        }else{
            w[k] = a[j];
            j++;
        }
        k++;
    }
    /* printf("merge2 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
    
    /* add any remaining elements from left half of array to workspace */
    while(i<(n/2)){
        w[k] = a[i];
        i++;
        k++;
    }
    /* printf("merge3 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
    
    /* add any remaining elements from right half of array to workspace */
    while(j<n){
        w[k] = a[j];
        j++;
        k++;
    }
    /* printf("merge4 i:%d j:%d k:%d n:%d\n", i, j, k, n); */
}

void merge_sort(int *a, int *w, int n){
    int i = 0;
    /* if the array to be sorted has fewer than two elements then return */
    if(n<2) return;
    /* call merge_sort on the first half of array a */
    merge_sort(a, w, n/2);
    /* call merge_sort on the second half of array a */
    merge_sort( a+(n/2), w, n-(n/2) );
    /* merge the two halves of array a into array w */
    merge(a, w, n);
    /* copy array w back into array a */
    for(i=0; i<n; i++){
        a[i] = w[i];
    }
}

int main(void) {
    int my_array[ARRAY_MAX];
    int workspace[ARRAY_MAX];
    clock_t start, end;
    int count = 0;

    /* read from stdin */
    /*
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    */

    /* generate random numbers */
    for(count=0; count<ARRAY_MAX; count++){
        my_array[count] = rand();
    }

    /* check if count is zero (just in case */
    if(count==0){
        fprintf(stderr, "Count is zero\n");
    }else{
        /* printf("Count:%d\n", count); */
    }

    /*
    printf("Unsorted array:\n");
    print_array(my_array, count);
    */
    
    start = clock();
    /* insertion_sort(my_array, count); */
    merge_sort(my_array, workspace, count);
    end = clock();

    /*
    printf("\nSorted array:\n");
    print_array(my_array, count);
    */

    fprintf(stderr, "Count:%d Time:%f\n", count, (end-start)/(double)CLOCKS_PER_SEC);
    
    return EXIT_SUCCESS;
}
