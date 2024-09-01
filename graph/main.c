#include "graph.h"

int main(int argc, char const *argv[]) {
    
    graph_t *graph;

    graph = graph_init(3);

    graph_add_edge(graph, 0, 1);
    graph_add_edge(graph, 0, 2);
    graph_add_edge(graph, 2, 1);

    graph_print(graph);

    return 0;
}

/* TODO:
 * - add nodes objects
 * - reference nodes by it's objects (or names)
 * - print nodes names (instad of numbers) 
*/
