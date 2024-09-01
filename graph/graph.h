#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>

typedef struct node node_t;
typedef unsigned int node_id_t;
struct node {
    node_id_t id;
    const char *name;
};

typedef struct graph graph_t;
typedef struct node_list node_list_t;
typedef struct connection_list connection_list_t;


graph_t *graph_init();
void graph_destroy(graph_t *graph);
void graph_print(graph_t *graph);

node_t *node_create(node_id_t id, const char *name);
void graph_add_node(graph_t *graph, node_t *node);
void graph_connect_nodes(graph_t *graph, node_t *source, node_t *target);
// void graph_connect_nodes_by_name(graph_t *graph, const char *source, const char *target);
// void graph_connect_nodes_by_id(graph_t *graph, const node_id_t source, const node_id_t target);
void node_delete(node_t *node);

#endif /* _GRAPH_H_ */