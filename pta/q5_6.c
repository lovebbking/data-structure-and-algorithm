#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 10

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
            G->arc[i][j] = 0;
    return G;
}

void SetEdge(MGraph G, VertexType n1, VertexType n2)
{
    G->arc[n1][n2] = 1;
    G->arc[n2][n1] = 1;
}

void DFSTraverse(MGraph G, VertexType n, int visited[])
{
    int j;
    printf("%d ", G->vexs[n]);
    visited[n] = 1;
    for (j = n; j < G->numNodes; j++)
        if (G->arc[n][j] == 1 && !visited[j])
            DFSTraverse(G, j, visited);
}

void DFS(MGraph G)
{
    int visited[MAXVEX];
    for (int i = 0; i < G->numNodes; i++)
        visited[i] = 0;

    for (int i = 0; i < G->numNodes; i++)
        if (!visited[i])
        {
            printf("{ ");
            DFSTraverse(G, i, visited);
            printf("}\n");
        }
}

void BFS(MGraph G)
{
    int visited[MAXVEX];
    int Q[MAXVEX];
    int head = 0, rear = 0, i, j;
    for (i = 0; i < G->numNodes; i++)
    {
        visited[i] = 0;
        Q[i] = -1;
    }

    for (i = 0; i < G->numNodes; i++)
    {
        if(visited[i]) continue;
       	printf("{ ");
        // 入队，必须在入队的时候访问
		VertexType v = G->vexs[i];
        Q[rear] = v;
		printf("%d ", v);
		visited[v] = 1;
        rear++;

        while (rear != head)
        {
            // 出队
            VertexType vex = Q[head];
            head++;

            // 把相邻结点入队
            for (j = 0; j < G->numNodes; j++)
            {
                if (G->arc[vex][j] == 1 && !visited[j])
                {
                    // 入队并访问
					VertexType v = G->vexs[j];
                    Q[rear] = v;
					printf("%d ", v);
					visited[v] = 1;
                    rear++;
                }
            }
        }
        printf("}\n");
    }
}

int main()
{
    int N, E, i;
    VertexType n1, n2;


    scanf("%d %d", &N, &E);
    MGraph G = CreateMGraph(N, E);
    while (E--)
    {
        scanf("%d %d", &n1, &n2);
        SetEdge(G, n1, n2);
    }

    DFS(G);
    BFS(G);

    return 0;
}
