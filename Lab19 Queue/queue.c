#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "mylib.h"

struct queue {
    double *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new(){
    queue q = emalloc(sizeof *q);
    q->capacity = 7;
    q->items = emalloc((q->capacity+1) * sizeof q->items[0]);    
    q->head = 0;    
    q->num_items = 0;
    return q;
}

void enqueue(queue q, double item){
    if(q->num_items < q->capacity){
        q->items[q->head + q->num_items % q->capacity] = item;
        q->num_items++;
    }
}

double dequeue(queue q){
    double result = 0.0;
    if(q->num_items>0){
        result = q->items[q->head];
        if(q->head == q->capacity-1){
            q->head = 0;
        }else{
            q->head++;
        }
        q->num_items--;
    }
    return result;
}

void queue_print(queue q){
    /* print queue contents one per line to 2 decimal places */
    int i;
    for(i=q->head; i<q->num_items; i++){
        printf("%.2f\n", q->items[(i + q->head) % q->capacity]);
    }
}

int queue_size(queue q){
    return q->num_items;
}
queue queue_free(queue q){
    int i;
    for(i=0; i<q->capacity; i++){
        q->items[i] = 0.0;
    }
    free(q->items);
    free(q);
    return q;
}
