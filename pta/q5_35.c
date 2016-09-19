#include <stdlib.h>
#include <stdio.h>

#define MAXVEX 500
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define INFINITY 65535
typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
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
        {
            if (i == j)
            {
                G->arc[i][j] = 0;
            }

            else
            {
                G->arc[i][j] = INFINITY;
            }
        }
    return G;
}

void SetEdge(MGraph G, VertexType n1, VertexType n2, int p)
{
    G->arc[n1][n2] = p;
    G->arc[n2][n1] = p;
}

void Dijkstra(MGraph G, VertexType v0, VertexType vf, int rescue[])
{
    int i;
    int dist[MAXVEX], path[MAXVEX], collected[MAXVEX], total[MAXVEX] final[MAXVEX];
    for (i = 0; i < G->numNodes; i++)
    {
        dist[i] = INFINITY;
        path[i] = -1;
        collected[i] = 0;
        total[i] = rescue[i];
    }
    //    设置初始数据
    dist[v0] = 0;

    // 进入循环，每次收录一个最小结点
    while (1)
    {
        // 找到最小
        int min = INFINITY;
        EdgeType k;
        for (i = 0; i < G->numNodes; i++)
        {
            if (!collected[i] && dist[i] < min)
            {
                min = dist[i];
                k = i;
            }
        }

        // 找不到，退出while true 循环
        if (min == INFINITY) break;
        // 找到最小，收录
        collected[k] = 1;

        // 若收录u导致未收录的结点 的最短距离变短，则更新
        for (i = 0; i < G->numNodes; i++)
        {
            if (collected[i]) continue;

            if ((min + G->arc[k][i]) < dist[i])
            {
                dist[i] = min + G->arc[k][i];
                path[i] = k;
                total[i] = total[k] + rescue[i];
            }
            else if (((min + G->arc[k][i]) == dist[i])
                        && total[i] < (total[k] + rescue[i]))
            {
                path[i] = k;
                total[i] = total[k] + rescue[i];
            }
        }
    }

    printf("%d %d", dist[vf], total[vf]);
}

int main()
{
    int N, E, i, p, fee;
    VertexType n1, n2, v0, vf;
    int rescue[MAXVEX];

    scanf("%d %d %d %d", &N, &E, &v0, &vf);
    MGraph G = CreateMGraph(N, E);

    for (i = 0; i < N; i++)
        scanf("%d", &rescue[i]);

    while (E--)
    {
        scanf("%d %d %d", &n1, &n2, &p);
        SetEdge(G, n1, n2, p);
    }

    Dijkstra(G, v0, vf, rescue);

    return 0;
}
