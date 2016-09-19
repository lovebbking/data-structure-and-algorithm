# include <stdio.h>
# include <stdlib.h>

# define MAXVERTEX 100

typedef int edgeType;
typedef int vertexType;

typedef struct GNode {
    int vertexCount;  //定点数
    int edgeCount;  // 边数
    vertexType vertexs[MAXVERTEX]; // 顶点表
    edgeType edges[MAXVERTEX][MAXVERTEX];  // 边表
}GNode;
typedef GNode *MGraph;

void initGraph(MGraph m, int vertexCount) {
    int v, w;
    m->vertexCount = vertexCount;
    m->edgeCount = 0;
    for(v = 0; v < m->vertexCount; v++)
        for(w = 0; w < m->vertexCount; w++)
            m->edges[v][w] = 0;
}

int main() {
    MGraph m = (MGraph)malloc(sizeof(struct GNode));
    initGraph(m, 10);
    printf("%d\n", m->vertexCount);
}
