#include <stdio.h>
#include <stdlib.h>
#define MAXVEX 1000
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 10000
typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int VertexType; /* 顶点类型应由用户定义  */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct MG *MGraph;
typedef struct MG {
    VertexType vexs[MAXVEX]; /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];/* 邻接矩阵，可看作边表 */
    int numNodes, numEdges; /* 图中当前的顶点数和边数  */
} MG;

/* 用到的队列结构与函数********************************** */
/* 循环队列的顺序存储结构 */
typedef struct
{
    int data[MAXSIZE];
    int front;    	/* 头指针 */
    int rear;		/* 尾指针,若队列不空,指向队列尾元素的下一个位置 */
}Queue;

/* 初始化一个空队列Q */
Status InitQueue(Queue *Q)
{
    Q->front=0;
    Q->rear=0;
    return  OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty(Queue Q)
{
    if(Q.front==Q.rear) /* 队列空的标志 */
        return TRUE;
    else
        return FALSE;
}

/* 若队列未满,则插入元素e为Q新的队尾元素 */
Status EnQueue(Queue *Q,int e)
{
    if ((Q->rear+1)%MAXSIZE == Q->front)	/* 队列满的判断 */
        return ERROR;
    Q->data[Q->rear]=e;			/* 将元素e赋值给队尾 */
    Q->rear=(Q->rear+1)%MAXSIZE;/* rear指针向后移一位置, */
    /* 若到最后则转到数组头部 */
    return  OK;
}

/* 若队列不空,则删除Q中队头元素,用e返回其值 */
Status DeQueue(Queue *Q,int *e)
{
    if (Q->front == Q->rear)			/* 队列空的判断 */
        return ERROR;
    *e=Q->data[Q->front];				/* 将队头元素赋值给e */
    Q->front=(Q->front+1)%MAXSIZE;	/* front指针向后移一位置, */
    /* 若到最后则转到数组头部 */
    return  OK;
}

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
    int j, end = 1;
    printf("%d ", G->vexs[n] + 1);
    visited[n] = 1;
    for (j = n; j < G->numNodes; j++)
        if (G->arc[n][j] == 1 && !visited[j])
        {
            DFSTraverse(G, j, visited);
            end = 0;
        }
    if (!end) printf("%d ", G->vexs[n] + 1);
}

int main()
{
    int N, E, travelAll;
    VertexType n1, n2, n;
    int visited[MAXVEX];


    scanf("%d %d %d", &N, &E, &n);
    MGraph G = CreateMGraph(N, E);

    for (int i = 0; i < G->numNodes; i++)
        visited[i] = 0;

    while (E--)
    {
        scanf("%d %d", &n1, &n2);
        SetEdge(G, n1 - 1, n2 - 1);
    }

    DFSTraverse(G, (n - 1), visited);

    // 判断是否可以所有遍历完
    travelAll = 1;
    for (int i = 0; i < G->numNodes; i++)
        if (visited[i] == 0)
        {
            travelAll = 0;
            break;
        }
        
    if (!travelAll) printf("0");

    return 0;
}
