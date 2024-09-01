#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>

typedef struct graph graph_t;

graph_t *graph_init(const unsigned int node_count);
void graph_destroy(graph_t *graph);
void graph_print(graph_t *graph);
bool graph_add_edge(graph_t *graph, unsigned int from_node, unsigned int to_node);

#endif /* _GRAPH_H_ */