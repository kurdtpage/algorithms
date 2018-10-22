#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "mylib.h"

int main (void) {

    int a,b,c;

    graph g;

    scanf("%d", &a);
    
    g = graph_new(a);

    while(2 == scanf ("%d %d" , &b, &c)){
        graph_add_edge(g, b, c);
    }

    graph_search(g, 1);

    graph_print(g);

    graph_free(g);

    return EXIT_SUCCESS;
}
           
