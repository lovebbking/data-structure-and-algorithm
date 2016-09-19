#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

MGraph CreateMGraph(int numNodes, int numEdges)
{
    int i, j;
    MGraph G = (MGraph)malloc(sizeof(struct MG));
    G->numNodes = numNodes;
    G->numEdges = numEdges;

    for (i = 0; i < G->numNodes; i++)
        G->vexs[i] = 0;
    for (i = 0; i < G->numNodes; i++)
        for (j = 0; j < G->numNodes; j++)
            G->arc[i][j] = 0;
    return G;
}
