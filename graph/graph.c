#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node_list {
    node_t *this;
    node_list_t *next;
};

struct connection_list {
    node_t *from;
    node_t *to;
    connection_list_t *next;
};
struct graph {
    node_list_t nodes;
    connection_list_t connections;
};

void graph_destroy(graph_t *graph) {

    if (graph == NULL) {
        return;
    }

    /* TODO: free all nodes here */

    free(graph);
}

graph_t *graph_init() {

    graph_t *graph = calloc(sizeof(graph_t), 1);
    if (!graph) {
        return NULL;
    }

    return graph;
}

void graph_print(graph_t *graph) {

    connection_list_t *connection = &graph->connections;

    printf("digraph {\n");

    do {
        if (connection->from && connection->next) {
            printf("%s -> %s;\n", connection->from->name, connection->to->name);
        } 
        connection = connection->next;
    } while (connection);

    printf("}\n");
}

node_t *node_create(node_id_t id, const char *name) {

    node_t *node = malloc(sizeof(node_t));
    if (node) {
        node->id = id;
        node->name = name;
    }

    return node;
}

void node_delete(node_t *node) {

    if (node) {
        free(node);
    }
}

void graph_add_node(graph_t *graph, node_t *node) {

    node_list_t *nodes = &graph->nodes;

    while (nodes->this) {
        nodes = nodes->next;
    }

    nodes->this = node;
    nodes->next = calloc(sizeof(node_list_t), 1);
}

void graph_connect_nodes(graph_t *graph, node_t *source, node_t *target) {

    connection_list_t *connection = &graph->connections;

    while (connection->from && connection->to) {
        if ((connection->from == source) && (connection->to == target)) {
            return; /* connection exists */
        }
        connection = connection->next;
    }

    connection->from = source;
    connection->to = target;
    connection->next = calloc(sizeof(connection_list_t), 1);
}