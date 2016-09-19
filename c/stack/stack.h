// 在一个数组中实现两个堆栈
#define ERROR 1e8
#define MAX 1000
typedef int ElementType;
typedef enum { false, true } bool;
typedef int Position;
struct SNode {
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

Stack CreateStack( int MaxSize );

bool Push( Stack S, ElementType X, int Tag );

ElementType Pop( Stack S, int Tag );
