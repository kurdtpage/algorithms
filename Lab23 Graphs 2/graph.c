#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "mylib.h"

static int step;

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
    g->size = capacity;
    g->vertices = emalloc(g->size * sizeof g->vertices[0]);
    g->edges = emalloc(capacity * sizeof g->edges[0]);
    for(i=0; i<capacity; i++){
        g->edges[i] = emalloc(capacity * sizeof g->edges[0][0]);
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
    g->edges[x][y] = 1;
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
    printf("Vertex Distance Predecessor Finish\n");
    for(i=0; i < g->size; i++){
        printf("%5d%9d%12d%7d\n", i, g->vertices[i].distance, g->vertices[i].predecessor, g->vertices[i].finish);
    }
    
}

static void visit(int v, graph g){
    int i;
    g->vertices[v].state = VISITED_SELF;
    step++;
    g->vertices[v].distance = step;
    for(i=0; i<g->size; i++){
        if(g->edges[v][i] == 1){
            if(g->vertices[i].state == UNVISITED){
                g->vertices[i].predecessor = v;
                visit(i, g);
            }
        }
    }
    step++;
    g->vertices[v].state = VISITED_DESCENDENTS;
    g->vertices[v].finish = step;
}

void graph_search(graph g){
    int i;
    for(i=0; i<g->size; i++){
        g->vertices[i].state = UNVISITED;
        g->vertices[i].predecessor = -1;
    }
    step = 0;
    for(i=0; i<g->size; i++){
        if(g->vertices[i].state == UNVISITED){
            visit(i,g);
        }
    }
}
