#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct graph {
    unsigned int node_count;
    bool **edges;
};

void graph_destroy(graph_t *graph) {

    if (graph == NULL) {
        return;
    }

    if (graph->edges == NULL) {
        free(graph);
        return;
    }

    for (size_t node = 0; node < graph->node_count; node++) {
        if (graph->edges[node]) {
            free(graph->edges[node]);
        }
    }

    free(graph->edges);
    free(graph);
}

graph_t *graph_init(const unsigned int node_count) {

    graph_t *graph = malloc(sizeof(graph_t));
    if (!graph) {
        return NULL;
    }

    graph->node_count = node_count;
    graph->edges = calloc(sizeof(bool*), node_count);
    if (!graph->edges) {
        free(graph);
        return NULL;
    }

    for (size_t node = 0; node < node_count; node++) {
        graph->edges[node] = calloc(sizeof(bool), node_count);
        if (!graph->edges[node]) {
            graph_destroy(graph);
            return NULL;
        }
    }

    return graph;
}

void graph_print(graph_t *graph) {

    printf("digraph {\n");

    for (size_t from_node = 0; from_node < graph->node_count; from_node++) {
        for (size_t to_node = 0; to_node < graph->node_count; to_node++) {
            if (graph->edges[from_node][to_node]) {
                printf("%ld -> %ld;\n", from_node, to_node);
            }
        }
    }

    printf("}\n");
}

bool graph_has_edge(graph_t *graph, unsigned int from_node, unsigned int to_node) {

    assert(graph != NULL);
    assert(from_node < graph->node_count);
    assert(to_node < graph->node_count);

    return graph->edges[from_node][to_node];
}

bool graph_add_edge(graph_t *graph, unsigned int from_node, unsigned int to_node) {

    bool exist = false;

    if (graph_has_edge(graph, from_node, to_node)) {
        exist = true;
    } else {
        graph->edges[from_node][to_node] = true;
    }

    return exist;
}