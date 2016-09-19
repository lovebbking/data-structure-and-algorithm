#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100 /* 最大顶点数，应由用户定义 */
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

MGraph CreateMGraph(int numNodes, int numEdges);
