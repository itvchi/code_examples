#include "graph.h"

int main(int argc, char const *argv[]) {
    
    graph_t *graph;
    graph = graph_init();

    node_t *nodes[4];
    nodes[0] = node_create(1, "first");
    nodes[1] = node_create(2, "second");
    nodes[2] = node_create(3, "third");
    nodes[3] = node_create(4, "fourth");

    graph_add_node(graph, nodes[0]);
    graph_add_node(graph, nodes[1]);
    graph_add_node(graph, nodes[2]);
    graph_add_node(graph, nodes[3]);

    graph_connect_nodes(graph, nodes[0], nodes[1]);
    graph_connect_nodes(graph, nodes[0], nodes[2]);
    graph_connect_nodes_by_id(graph, 1, 3);
    graph_connect_nodes_by_id(graph, 3, 4);
    graph_connect_nodes_by_name(graph, "fourth", "second");
    graph_connect_nodes_by_name(graph, "fourth", "first");
    graph_connect_nodes_by_name(graph, "second", "third");

    graph_print(graph);

    return 0;
}

/* TODO:
 * - add nodes objects [done]
 * - reference nodes by it's objects [done]
 * - reference node by it's id or name [done]
 * - print nodes names (instead of numbers) [done] 
*/
