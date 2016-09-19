// 5-23 还原二叉树   (25分)
// 给定一棵二叉树的先序遍历序列和中序遍历序列，要求计算该二叉树的高度。
//
// 输入格式:
//
// 输入首先给出正整数N（\le≤50），为树中结点总数。下面两行先后给出先序和中序遍历序列，均是长度为N的不包含重复英文字母（区别大小写）的字符串。
//
// 输出格式:
//
// 输出为一个整数，即该二叉树的高度。
//
// 输入样例:
//
// 9
// ABDFGHIEC
// FDHGIBEAC
// 输出样例:
//
// 5

#include <stdlib.h>
#include <stdio.h>

#define MaxNode 50

typedef enum {false, true} bool;
typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
typedef struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
} TNode;

int N;
char Pre[MaxNode], In[MaxNode];

void getChar(char cs[], int N, bool lineBreak)
{
    int i;
    for (i = 0; i < N; i++)
        if ((i == N - 1) && lineBreak)
            scanf("%c\n", &cs[i]);
        else
            scanf("%c", &cs[i]);
    return;
}

BinTree BuildTree(int Left, int Right, int L)
{
    if (Left >= Right)
        return NULL;
    int i, j, k = -1;

    for (j = 0; j < L; j++)
    {
        for (i = Left; i < Right; i++)
        {
            if (In[i] == Pre[j])
            {
                k = i;
                break;
            }
        }
        if (k > -1) break;
    }

    BinTree Root = (BinTree)malloc(sizeof(struct TNode));
    Root->Data = In[k];
    Root->Left = BuildTree(Left, i, L);
    Root->Right = BuildTree(i + 1, Right, L);

    return Root;
}


// 给定二叉树的高度。
int GetHeight(BinTree BT)
{
    if (!BT)
        return 0;

    int l = GetHeight(BT->Left);
    int r = GetHeight(BT->Right);

    int m = l > r ? l : r;
    return m + 1;
}

int main()
{
    int i;

    scanf("%d\n", &N);

    getChar(Pre, N, true);
    getChar(In, N, false);

    BinTree BT = BuildTree(0, N, N);
    printf("%d", GetHeight(BT));
}
