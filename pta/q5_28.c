// 对于二叉搜索树，我们规定任一结点的左子树仅包含严格小于该结点的键值，而其右子树包含大于或等于该结点的键值。如果我们交换每个节点的左子树和右子树，得到的树叫做镜像二叉搜索树。
//
// 现在我们给出一个整数键值序列，请编写程序判断该序列是否为某棵二叉搜索树或某镜像二叉搜索树的前序遍历序列，如果是，则输出对应二叉树的后序遍历序列。
//
// 输入格式:
//
// 输入的第一行包含一个正整数N（\le≤1000），第二行包含N个整数，为给出的整数键值序列，数字间以空格分隔。
//
// 输出格式:
//
// 输出的第一行首先给出判断结果，如果输入的序列是某棵二叉搜索树或某镜像二叉搜索树的前序遍历序列，则输出YES，否侧输出NO。如果判断结果是YES，下一行输出对应二叉树的后序遍历序列。数字间以空格分隔，但行尾不能有多余的空格。
//
// 输入样例1:
//
// 7
// 8 6 5 7 10 8 11
// 输出样例1:
//
// YES
// 5 7 6 8 11 10 8
// 输入样例2:
//
// 7
// 8 6 8 5 10 9 11
// 输出样例2:
//
// NO


#include <stdlib.h>
#include <stdio.h>

#define MAX 1000
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

void PushDataToArray( BinTree BT, ElementType A[])
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (A[i] == 0)
        {
            A[i] = BT->Data;
            return;
        }
    }
}

void PreorderTraversal( BinTree BT, ElementType A[])
{
    if(BT)
    {
        PushDataToArray(BT, A);
        PreorderTraversal(BT->Left, A);
        PreorderTraversal(BT->Right, A);
    }
}

void PostorderTraversal( BinTree BT, ElementType A[])
{
    if(BT)
    {
        PostorderTraversal(BT->Left, A);
        PostorderTraversal(BT->Right, A);
        PushDataToArray(BT, A);
    }
}

bool samePreorderArray(ElementType A1[], ElementType A2[])
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        if (A1[i] != A2[i])
            return false;
        // 到数组尾
        if (A1[i] == 0 && A2[i] == 0)
            break;
    }
    return true;
}

//二叉树左右子树互换
void Swap(BinTree BT)
{
    BinTree T;
    if(!BT)
        return;

    T = BT->Left;
    BT->Left = BT->Right;
    BT->Right = T;

    Swap(BT->Left);
    Swap(BT->Right);
}

void PrintArray(ElementType A[], int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (i == 0)
            printf("%d", A[i]);
        else
            printf(" %d", A[i]);
    }
}

int main()
{
    BinTree T = NULL;
    int N, i, a;
    ElementType A1[MAX] = {0},
    A2[MAX] = {0},
    A3[MAX] = {0},
    A4[MAX] = {0},
    A5[MAX] = {0};
    scanf("%d", &N);

    for (i = 0; i < N; i++)
    {
        scanf("%d", &a);
        A1[i] = a;
        T = Insert(T, a);
    }
    PreorderTraversal(T, A2);

    if (samePreorderArray(A1, A2))
    {
        printf("YES\n");

        PostorderTraversal(T, A3);
        PrintArray(A3, N);
    }
    else
    {
        // 变成镜像二叉搜索树
        Swap(T);
        PreorderTraversal(T, A4);

        if (samePreorderArray(A1, A4))
        {
            printf("YES\n");

            PostorderTraversal(T, A5);
            PrintArray(A5, N);
        }
        else
            printf("NO\n");
    }

    return 0;
}
