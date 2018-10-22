#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>

typedef struct graphrec *graph;
typedef enum state_e {UNVISITED, VISITED_SELF, VISITED_DESCENDENTS} state_t;

extern void graph_free(graph g);
extern graph graph_new(int capacity);
extern void graph_print(graph g);
extern void graph_search(graph g, int s);
extern void graph_add_edge(graph g, int x, int y);

#endif
