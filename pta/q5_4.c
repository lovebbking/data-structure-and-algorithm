// 给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。
//
// 输入格式:
//
// 输入包含若干组测试数据。每组数据的第1行给出两个正整数NN (\le 10≤10)和LL，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出NN个以空格分隔的正整数，作为初始插入序列。最后LL行，每行给出NN个插入的元素，属于LL个需要检查的序列。
//
// 简单起见，我们保证每个插入序列都是1到NN的一个排列。当读到NN为0时，标志输入结束，这组数据不要处理。
//
// 输出格式:
//
// 对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。
//
// 输入样例:
//
// 4 2
// 3 1 4 2
// 3 4 1 2
// 3 2 4 1
// 2 1
// 2 1
// 1 2
// 0
// 输出样例:
//
// Yes
// No
// No

#include <stdlib.h>
#include <stdio.h>

typedef enum {false, true} bool;
typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree newNode(ElementType E)
{
    BinTree t = (BinTree)malloc(sizeof(struct TNode));
    t->Data = E;
    t->Left = t->Right = NULL;
    return t;
}

BinTree Insert(BinTree T, ElementType X)
{
    if(!T)
        return newNode(X);

    if (X < T->Data)
        T->Left = Insert(T->Left, X);
    else
        T->Right = Insert(T->Right, X);
    return T;
}

BinTree createBinTree(int N)
{
    BinTree T = NULL;
    int i;
    while(N--)
    {
        scanf("%d", &i);
        T = Insert(T, i);
    }

    return T;
}

bool sameTree(BinTree T1, BinTree T2)
{
    if (T1 == NULL && T2 == NULL)
        return true;
    if ((T1 == NULL && T2 != NULL) || (T1 != NULL && T2 == NULL))
        return false;
    if (T1->Data != T2->Data)
        return false;
    return sameTree(T1->Left, T2->Left) && sameTree(T1->Right, T2->Right);
}

int main()
{
    int N, L;
    BinTree T1 = NULL, T2 = NULL;
    while (scanf("%d",&N) != EOF && N != 0) {

        scanf("%d", &L);

        T1 = createBinTree(N);
        while (L--) {
            T2 = createBinTree(N);

            if (sameTree(T1, T2))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}
