#include "graph.h"

int main(int argc, char const *argv[]) {
    
    graph_t *graph;
    graph = graph_init();

    node_t *nodes[3];
    nodes[0] = node_create(1, "first");
    nodes[1] = node_create(2, "second");
    nodes[2] = node_create(3, "third");

    graph_add_node(graph, nodes[0]);
    graph_add_node(graph, nodes[1]);
    graph_add_node(graph, nodes[2]);

    graph_connect_nodes(graph, nodes[0], nodes[1]);
    graph_connect_nodes(graph, nodes[0], nodes[2]);
    graph_connect_nodes(graph, nodes[2], nodes[1]);
    graph_connect_nodes(graph, nodes[2], nodes[2]);

    graph_print(graph);

    return 0;
}

/* TODO:
 * - add nodes objects [done]
 * - reference nodes by it's objects [done]
 * - reference node by it's id or name 
 * - print nodes names (instead of numbers) [done] 
*/
