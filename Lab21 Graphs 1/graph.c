#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "queue.h"
#include "mylib.h"

struct graphrec {
    struct vertices_array *vertices;
    int size;
    int **edges;    
};

struct vertices_array {
    int predecessor;
    int distance;
    state_t state;
    int finish;
};

graph graph_new(int capacity){
    int i,j;
    graph g = emalloc(sizeof *g);
    g->size= capacity;
    g->vertices = emalloc(g->size * sizeof g->vertices[0]);
    g->edges = emalloc(capacity * sizeof g->edges[0]);
    for(i=0; i<capacity; i++){
        g->edges[i]=emalloc(capacity * sizeof g->edges[0][0]);
        for(j=0; j<capacity; j++){
            g->edges[i][j] = 0;
        }
    }
    return g;    
}

void graph_free(graph g){
    int i;
    for(i=0; i<g->size; i++){
        free(g->edges[i]);
    }
    free(g->edges);
    free(g->vertices);
    free(g);
}

void graph_add_edge(graph g, int x, int y){
    /*
    Undirected edge
    */
    g->edges[x][y] = 1;
    g->edges[y][x] = 1;
}

void graph_print(graph g){
    int i,j;

    printf("Adjacency list:\n");
    for(i=0; i < g->size; i++){
        printf("%d |", i);
        for (j=0; j<g->size;j++){
            if(g->edges[i][j] == 1){
                printf(" %d,", j);
            }
        }
        printf("\n");
    }
    printf("Vertex Distance Predecessor\n");
    for(i=0; i < g->size; i++){
        printf("%5d%9d%12d\n", i, g->vertices[i].distance, g->vertices[i].predecessor);
    }       
}

void graph_search(graph g, int s){
    queue q = queue_new();
    int i,u,v;
    
    for(i=0; i<g->size;i++){
        g->vertices[i].state = UNVISITED;
        g->vertices[i].distance = -1;
        g->vertices[i].predecessor = -1;
    }
    g->vertices[s].state = VISITED_SELF;
    g->vertices[s].distance = 0;
    enqueue(q,s);

    while(queue_size(q) != 0){
        u = dequeue(q);
        for(v=0; v<g->size;v++){
            if(g->edges[u][v]==1 && g->vertices[v].state==UNVISITED){
                g->vertices[v].state = VISITED_SELF;
                g->vertices[v].distance = g->vertices[u].distance + 1;
                g->vertices[v].predecessor = u;
                enqueue(q,v);
            }
            g->vertices[u].state = VISITED_DESCENDENTS;
        }
    }
    queue_free(q);
}
