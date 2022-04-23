#include "ColorGraph.h"

#include "Utility/Converter.h"
#include "Utility/Error.h"

FColorGraph *CreateColorGraph() {
    FColorGraph *graph = malloc(sizeof(FColorGraph));
    graph->idIndex = malloc(sizeof(HashMap));
    if (hashmap_create(pow(2, 10), graph->idIndex) != 0) {
        Critical(ERROR_ALLOC_FAIL);
    }

    graph->edgeIndex = malloc(sizeof(HashMap));
    if (hashmap_create(pow(2, 10), graph->edgeIndex) != 0) {
        Critical(ERROR_ALLOC_FAIL);
    }

    graph->edges = NULL;

    return graph;
}

void FreeColorGraph(FColorGraph *graph) {
    ARRAY_FREE(graph->edges);

    hashmap_destroy(graph->idIndex);
    free(graph->idIndex);
    hashmap_destroy(graph->edgeIndex);
    free(graph->edgeIndex);
    free(graph);
}

bool AddEdgeToGraph(FColorGraph *graph, FBaseNode *node1, FBaseNode *node2) {
    FColorGraphEdge *edge1;
    int id1 = (int) hashmap_get(graph->edgeIndex, &node1->hash, 8);
    if (id1 <= 0) {
        id1 = ARRAY_SIZE(graph->edges) + 1;
        hashmap_put(graph->edgeIndex, &node1->hash, 8, (void*) (id1));

        edge1 = malloc(sizeof(FColorGraphEdge));
        ARRAY_PUSH(graph->edges, edge1);

        edge1->key = node1->location->token->str;
        edge1->linked = NULL;
        edge1->color = -1;
    } else {
        edge1 = graph->edges[id1 - 1];
    }

    FColorGraphEdge *edge2;
    int id2 = (int) hashmap_get(graph->edgeIndex, &node2->hash, 8);
    if (id2 <= 0) {
        id2 = ARRAY_SIZE(graph->edges) + 1;
        hashmap_put(graph->edgeIndex, &node2->hash, 8, (void*) (id2));

        edge2 = malloc(sizeof(FColorGraphEdge));
        ARRAY_PUSH(graph->edges, edge2);

        edge2->key = node2->location->token->str;
        edge2->linked = NULL;
        edge2->color = -1;
    } else {
        edge2 = graph->edges[id2 - 1];
    }


    ARRAY_PUSH(edge1->linked, id2 - 1);
    ARRAY_PUSH(edge2->linked, id1 - 1);
}

void GreedyGraph(FColorGraph *graph) {
    if (ARRAY_SIZE(graph->edges) <= 0) {
        return;
    }

    FColorGraphEdge *edge;
    ARRAY_FOREACH(graph->edges, edge) {
        edge->color = -1;
    }

    graph->edges[0]->color = 0;
    bool *available = NULL;
    int len = ARRAY_SIZE(graph->edges);
    for (int i = 0; i < len; i++) {
        ARRAY_PUSH(available, false);
    }

    len = ARRAY_SIZE(graph->edges);
    for (int i = 1; i < len; i++) {
        int linked = NULL;
        ARRAY_FOREACH(graph->edges[i]->linked, linked) {
            if (graph->edges[linked]->color != -1) {
                available[graph->edges[linked]->color] = true;
            }
        }

        for (int cr = 0; cr < len; cr++) {
            if (available[cr] == false) {
                graph->edges[i]->color = cr;
                break;
            }
        }

        ARRAY_FOREACH(graph->edges[i]->linked, linked) {
            if (graph->edges[linked]->color != -1) {
                available[graph->edges[linked]->color] = false;
            }
        }
    }

    // FOR DEBUG
    /*ARRAY_FOREACH(graph->edges, edge) {
        wprintf(U16("Vertex %ls ---> Color %d\n"), edge->key->data, edge->color);
    }*/
}

void ClearColorGraph(FColorGraph *graph) {
    ARRAY_FREE(graph->edges);

    hashmap_destroy(graph->idIndex);
    free(graph->idIndex);
    hashmap_destroy(graph->edgeIndex);
    free(graph->edgeIndex);

    graph->idIndex = malloc(sizeof(HashMap));
    if (hashmap_create(pow(2, 10), graph->idIndex) != 0) {
        Critical(ERROR_ALLOC_FAIL);
    }

    graph->edgeIndex = malloc(sizeof(HashMap));
    if (hashmap_create(pow(2, 10), graph->edgeIndex) != 0) {
        Critical(ERROR_ALLOC_FAIL);
    }

    graph->edges = NULL;
}

int GetColorFromGraph(FColorGraph *graph, FBaseNode *node1) {
    FColorGraphEdge *edge1;
    int id1 = (int) hashmap_get(graph->edgeIndex, &node1->hash, 8);
    if (id1 <= 0) {
        return -1;
    }
    edge1 = graph->edges[id1 - 1];

    return edge1->color;
}
