// 哈利·波特要考试了，他需要你的帮助。这门课学的是用魔咒将一种动物变成另一种动物的本事。例如将猫变成老鼠的魔咒是haha
// ，将老鼠变成鱼的魔咒是hehe等等。反方向变化的魔咒就是简单地将原来的魔咒倒过来念，例如ahah可以将老鼠变成猫。另外，
// 如果想把猫变成鱼，可以通过念一个直接魔咒lalala，也可以将猫变老鼠、老鼠变鱼的魔咒连起来念：hahahehe。
//
// 现在哈利·波特的手里有一本教材，里面列出了所有的变形魔咒和能变的动物。老师允许他自己带一只动物去考场，要考察他把这
// 只动物变成任意一只指定动物的本事。于是他来问你：带什么动物去可以让最难变的那种动物（即该动物变为哈利·波特自己带去的动
// 物所需要的魔咒最长）需要的魔咒最短？例如：如果只有猫、鼠、鱼，则显然哈利·波特应该带鼠去，因为鼠变成另外两种动物都只需
// 要念4个字符；而如果带猫去，则至少需要念6个字符才能把猫变成鱼；同理，带鱼去也不是最好的选择。
//
// 输入格式:
//
// 输入说明：输入第1行给出两个正整数NN (\le 100≤100)和MM，其中NN是考试涉及的动物总数，MM是用于直接变形的魔咒条数
// 。为简单起见，我们将动物按1~NN编号。随后MM行，每行给出了3个正整数，分别是两种动物的编号、以及它们之间变形需要的魔咒的
// 长度(\le 100≤100)，数字之间用空格分隔。
//
// 输出格式:
//
// 输出哈利·波特应该带去考场的动物的编号、以及最长的变形魔咒的长度，中间以空格分隔。如果只带1只动物是不可能完成所有变
// 形要求的，则输出0。如果有若干只动物都可以备选，则输出编号最小的那只。
//
// 输入样例:
//
// 6 11
// 3 4 70
// 1 2 1
// 5 4 50
// 2 6 50
// 5 6 60
// 1 3 70
// 4 6 60
// 3 6 80
// 5 1 100
// 2 4 60
// 5 2 80
// 输出样例:
//
// 4 70

#include <stdlib.h>
#include <stdio.h>

#define MAXVEX 100
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

int D[MAXVEX][MAXVEX];
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

void SetEdge(MGraph G, VertexType n1, VertexType n2, int p)
{
    G->arc[n1][n2] = p;
    G->arc[n2][n1] = p;
}

void Floyd(MGraph G)
{

    int i, j, k;
    int min = INFINITY;
    for (i = 0; i < G->numNodes; i++)
        for (j = 0; j < G->numNodes; j++)
        {
            D[i][j] = G->arc[i][j];
        }

    for (k = 0; k < G->numNodes; k++)
        for (i = 0; i < G->numNodes; i++)
            for (j = 0; j < G->numNodes; j++)
            {
                if ((D[i][k] + D[k][j]) < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }


}

int main()
{
    int N, E, i, p, j;
    VertexType n1, n2;


    scanf("%d %d", &N, &E);
    MGraph G = CreateMGraph(N, E);
    while (E--)
    {
        scanf("%d %d %d", &n1, &n2, &p);
        SetEdge(G, n1 - 1, n2 - 1, p);
    }

    Floyd(G);
    int min = INFINITY, index = N;
    int flag = 0;
    for (int i = 0;i < G->numNodes; i++)
    {
        int t = 0;
        for (int j = 0; j < G->numNodes; j++)
        {
            if (i != j && D[i][j] == INFINITY)
            {
                flag = 1;
                break;
            }
            if (i != j && D[i][j] > t)
            {
                t = D[i][j];
            }
        }
        if (t < min)
        {
            min = t;
            index = i;
        }
    }
    if (flag)
        printf("0\n");
    else
        printf("%d %d",index + 1,min);

    return 0;
}
