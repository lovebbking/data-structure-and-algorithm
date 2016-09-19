// 现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。
//
// 输入格式:
//
// 输入数据包括城镇数目正整数NN（\le 1000≤1000）和候选道路数目MM（\le 3N≤3N）；随后的MM行对应MM条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到NN编号。
//
// 输出格式:
//
// 输出村村通需要的最低成本。如果输入数据不足以保证畅通，则输出-1−1，表示需要建设更多公路。
//
// 输入样例:
//
// 6 15
// 1 2 5
// 1 3 3
// 1 4 7
// 1 5 4
// 1 6 2
// 2 3 4
// 2 4 6
// 2 5 2
// 2 6 6
// 3 4 6
// 3 5 1
// 3 6 1
// 4 5 10
// 4 6 8
// 5 6 3
// 输出样例:
//
// 12

#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 1000
#define INFINITY 65535

typedef int VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct MG *MGraph;
typedef struct MG {
    VertexType vexs[MAXVEX]; /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int numNodes, numEdges; /* 图中当前的顶点数和边数  */
} MG;

MGraph CreateMGraph(int numNodes, int numEdges)
{
    int i, j;
    MGraph G = (MGraph)malloc(sizeof(struct MG));
    G->numNodes = numNodes;
    G->numEdges = numEdges;

    for (i = 0; i < G->numNodes; i++)
        G->vexs[i] = i;

    for (i = 0; i < G->numNodes; i++)
        for (j = 0; j < G->numNodes; j++)
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = INFINITY;

    return G;
}

void SetEdge(MGraph G, VertexType n1, VertexType n2, EdgeType P)
{
    G->arc[n1][n2] = P;
    G->arc[n2][n1] = P;
}

void Prim(MGraph G)
{
    VertexType v0 = G->vexs[0];
    int Path[MAXVEX], dist[MAXVEX], collected[MAXVEX], parent[MAXVEX];
    int i, total, rootCount;

    for (i = 0; i < G->numNodes; i++)
    {
        Path[i] = -1;
        collected[i] = 0;
        dist[i] = G->arc[v0][i];
        parent[i] = -1;
    }

    while (1)
    {
        int min = INFINITY;
        VertexType k;
        // 找出当前距离已生成的树距离最小的结点
        for (i = 0; i < G->numNodes; i++)
            if (!collected[i] && dist[i] < min)
            {
                min = dist[i];
                k = i;
            }

        // 找不到，退出while true 循环
        if (min == INFINITY) break;

        // 收录k
        collected[k] = 1;

        // 若收录u导致未收录的结点 的最短距离变短，则更新
        for (i = 0; i < G->numNodes; i++)
            if (!collected[i] && (G->arc[k][i] <= dist[i]))
            {
                dist[i] = G->arc[k][i];
                parent[i] = k;
            }
    }

    total = 0;
    rootCount = 0
    // 树生成后，根据parent数组遍历
    for (i = 0; i < G->numNodes; i++)
        if (parent[i] == -1)
            rootCount++;
        else
            total += G->arc[i][parent[i]];

    if (rootCount == 1)
        printf("%d", total);
    else
        printf("-1");
}

int main()
{
    int N, E, p;
    VertexType n1, n2, n;

    scanf("%d %d", &N, &E);
    MGraph G = CreateMGraph(N, E);

    while (E--)
    {
        scanf("%d %d %d", &n1, &n2, &p);
        SetEdge(G, n1 - 1, n2 - 1, p);
    }

    Prim(G);

    return 0;
}
