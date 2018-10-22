#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "mylib.h"

int main(void){
    queue q = queue_new();
    enqueue(q, 1.2);
    enqueue(q, 2.4);
    enqueue(q, 3.6);
    enqueue(q, 4.7);
    queue_print(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    queue_print(q);
    queue_free(q);
    return EXIT_SUCCESS;
}
