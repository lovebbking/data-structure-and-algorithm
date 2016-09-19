#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 30
typedef enum {false, true} bool;
typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
typedef struct TNode{
    ElementType Data[MAX];
    int Count;
    BinTree Left;
    BinTree Right;
} TNode;

BinTree newNode(ElementType E[])
{
    BinTree t = (BinTree)malloc(sizeof(struct TNode));
    strcpy(t->Data, E);
    t->Left = t->Right = NULL;
    t->Count = 1;
    return t;
}

BinTree Insert(BinTree T, ElementType X[])
{
    if(!T)
        return newNode(X);

    if (strcmp(T->Data, X) > 0)
        T->Left = Insert(T->Left, X);
    else if (strcmp(T->Data, X) < 0)
        T->Right = Insert(T->Right, X);
    else
        T->Count++;
    return T;
}

void InorderTraversal(BinTree BT, int c)
{
    if(BT) {
        InorderTraversal(BT->Left, c);
        printf("%s %.4f%%\n", BT->Data, (float)BT->Count/ c * 100);
        InorderTraversal(BT->Right, c);
    }
}

int main()
{
    int N, c;
    ElementType s[MAX];
    BinTree T = NULL;

    scanf("%d", &N);
    getchar();
    c = N;
    while (N--)
    {
        gets(s);
        T = Insert(T, s);
    }

    InorderTraversal(T, c);

    return 0;
}
