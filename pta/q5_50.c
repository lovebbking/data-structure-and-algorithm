// 某地区经过对城镇交通状况的调查，得到现有城镇间快速道路的统计数据，并提出“畅通工程”的目标：使整个地区任何两个城镇间都可以实现快速交通（但不一定有直接的快速道路相连，只要互相间接通过快速路可达即可）。现得到城镇道路统计表，表中列出了任意两城镇间修建快速路的费用，以及该道路是否已经修通的状态。现请你编写程序，计算出全地区畅通需要的最低成本。
//
// 输入格式:
//
// 输入的第一行给出村庄数目NN (1\le N \le 1001≤N≤100)；随后的N(N-1)/2N(N−1)/2行对应村庄间道路的成本及修建状态：每行给出4个正整数，分别是两个村庄的编号（从1编号到NN），此两村庄间道路的成本，以及修建状态 — 1表示已建，0表示未建。
//
// 输出格式:
//
// 输出全省畅通需要的最低成本。
//
// 输入样例:
//
// 4
// 1 2 1 1
// 1 3 4 0
// 1 4 1 1
// 2 3 3 0
// 2 4 2 1
// 3 4 5 0
// 输出样例:
//
// 3
#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 100
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

void SetEdge(MGraph G, VertexType n1, VertexType n2, EdgeType P, int c)
{
    // 已建，成本为0
    if (c == 1)
    {
        G->arc[n1][n2] = 0;
        G->arc[n2][n1] = 0;
    }
    else
    {
        G->arc[n1][n2] = P;
        G->arc[n2][n1] = P;
    }
}

void Prim(MGraph G)
{
    VertexType v0 = G->vexs[0];
    int Path[MAXVEX], dist[MAXVEX], collected[MAXVEX], parent[MAXVEX];
    int i, total;

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
        {
            if (collected[i]) continue;
            if (G->arc[k][i] <= dist[i])
            {
                dist[i] = G->arc[k][i];
                parent[i] = k;
            }
        }
    }

    total = 0;
    // 树生成后，根据parent数组遍历
    for (i = 0; i < G->numNodes; i++)
    {
        if (parent[i] == -1) continue;
        total += G->arc[i][parent[i]];
    }

    printf("%d", total);
}

int main()
{
    int N, E, p, c;
    VertexType n1, n2, n;

    scanf("%d", &N);
    E = N * (N - 1) / 2;
    MGraph G = CreateMGraph(N, E);

    while (E--)
    {
        scanf("%d %d %d %d", &n1, &n2, &p, &c);
        SetEdge(G, n1 - 1, n2 - 1, p, c);
    }

    Prim(G);

    return 0;
}
