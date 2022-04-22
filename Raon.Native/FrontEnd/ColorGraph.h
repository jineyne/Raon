#ifndef __COLORGRAPH_H__
#define __COLORGRAPH_H__

#include "CoreMinimal.h"
#include "AST/AST.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ColorGraphEdge {
    FString *key;
    int *linked;
    int color;
} FColorGraphEdge;

typedef struct ColorGraph {
    HashMap *idIndex;
    HashMap *edgeIndex;

    FColorGraphEdge **edges;
} FColorGraph;

DLL_EXPORT FColorGraph *CreateColorGraph();
DLL_EXPORT void FreeColorGraph(FColorGraph *graph);

DLL_EXPORT bool AddEdgeToGraph(FColorGraph *graph, FBaseNode *node1, FBaseNode *node2);
DLL_EXPORT void GreedyGraph(FColorGraph *graph);

DLL_EXPORT void ClearColorGraph(FColorGraph *graph);

DLL_EXPORT int GetColorFromGraph(FColorGraph *graph, FBaseNode *node1);

#ifdef __cplusplus
}
#endif

#endif // __COLORGRAPH_H__
