// 哥尼斯堡是位于普累格河上的一座城市，它包含两个岛屿及连接它们的七座桥，如下图所示。
//
//
//
// 可否走过这样的七座桥，而且每桥只走过一次？瑞士数学家欧拉(Leonhard Euler，1707—1783)最终解决了这个问题，并由此创立了拓扑学。
//
// 这个问题如今可以描述为判断欧拉回路是否存在的问题。欧拉回路是指不令笔离开纸面，可画过图中每条边仅一次，且可以回到起点的一条回路。现给定一个无向图，问是否存在欧拉回路？
//
// 输入格式:
//
// 输入第一行给出两个正整数，分别是节点数NN (1\le N\le 10001≤N≤1000)和边数MM；随后的MM行对应MM条边，每行给出一对正整数，分别是该条边直接连通的两个节点的编号（节点从1到NN编号）。
//
// 输出格式:
//
// 若欧拉回路存在则输出1，否则输出0。
//
// 输入样例1:
//
// 6 10
// 1 2
// 2 3
// 3 1
// 4 5
// 5 6
// 6 4
// 1 4
// 1 6
// 3 4
// 3 6
//
// 输出样例1:
//
// 1


#include <stdlib.h>
#include <stdio.h>

#define MAXVEX 1000
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
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = INFINITY;
        }
    return G;
}

void SetEdge(MGraph G, VertexType n1, VertexType n2)
{
    G->arc[n1][n2] = 1;
    G->arc[n2][n1] = 1;
}

int DFS(MGraph G, VertexType start, VertexType n, int depth, int visited[])
{
    int j;

    visited[n] = 1;

    // 到了最后一个结点， 看看它和首结点能不能连通
    if (depth == G->numNodes - 1)
    {
        if (G->arc[n][start] == 1) return 1;
        else return 0;
    }

    for (j = n; j < G->numNodes; j++)
        if (G->arc[n][j] == 1 && !visited[j])
            DFS(G, start, j, depth++, visited);
}

int main()
{
    int N, E, i, p, j, result;
    VertexType n1, n2;
    int visited[MAXVEX];

    scanf("%d %d", &N, &E);
    MGraph G = CreateMGraph(N, E);
    while (E--)
    {
        scanf("%d %d", &n1, &n2);
        SetEdge(G, n1 - 1, n2 - 1);
    }

    for (i = 0; i < G->numNodes; i++)
    {
        for (j = 0; j < G->numNodes; j++)
            visited[j] = 0;
        if (DFS(G, i, i, 0, visited))
        {
            printf("1");
            return 0;
        }
    }

    printf("0");

    return 0;
}
