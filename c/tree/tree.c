#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

void PreorderTraversal( BinTree BT )
{
	if (BT)
	{
		printf(" %c", BT->Data);
		PreorderTraversal(BT->Left);
		PreorderTraversal(BT->Right);
	}
}

void InorderTraversal(BinTree BT)
{
    if (BT)
	{
        InorderTraversal(BT->Left);
        printf(" %c", BT->Data);
        InorderTraversal(BT->Right);
    }
}

void PostorderTraversal( BinTree BT )
{
	if (BT)
	{
		PostorderTraversal(BT->Left);
		PostorderTraversal(BT->Right);
		printf(" %c", BT->Data);
	}
}

void LevelorderTraversal( BinTree BT ) {
    BinTree nodes[100];
    int rear = 0, front = -1;
    BinTree T;

    if(!BT)
        return;

    nodes[rear] = BT;
    while (rear != front)
	{
        T = nodes[++front];
        printf(" %c", T->Data);

        if(T->Left)
            nodes[++rear] = T->Left;
        if(T->Right)
            nodes[++rear] = T->Right;
    }
}

void PreorderPrintLeaves( BinTree BT )
{
    if (!BT) return;

    if (BT->Left == NULL && BT->Right == NULL)
    {
        printf(" %c", BT->Data);
        return;
    }
    PreorderPrintLeaves(BT->Left);
    PreorderPrintLeaves(BT->Right);
}

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

// 将X从二叉搜索树BST中删除，并返回结果树的根结点指针；如果X不在树中，则打印一行Not Found并返回原树的根结点指针
BinTree Delete( BinTree BST, ElementType X )
{
	Position tmp;
	if (!BST)
	{
		printf("Not Found\n");
		return BST;
	}
	// 找到该节点
	if (BST->Data > X)
		BST->Left = Delete(BST->Left, X);
	else if (BST->Data < X)
		BST->Right = Delete(BST->Right, X);
	// 找到
	else
	{
		// 有左右儿子结点
		if (BST->Left && BST->Right)
		{
			// 将右子树最小结点替换到要删除的结点上。
			tmp = FindMin(BST->Right);
			BST->Data = tmp->Data;
			BST->Right = Delete(BST->Right, BST->Data);
		}
		// 只有右儿子结点
		else if (!BST->Left)
		{
			// 交换right 和 BST, 然后free
			tmp = BST;
			BST = BST->Right;
			free(tmp);
		}
		// 只有左儿子结点
		else if (!BST->Right)
		{
			tmp = BST;
			BST = BST->Left;
			free(tmp);
		}
		// 没有儿子结点
		else
			free(BST);
	}

	return BST;
}

// 在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
Position Find( BinTree BST, ElementType X )
{
	Position node = BST;
	while (node)
	{
		if (node->Data == X)
			break;
		if (node->Data > X)
			node = node->Left;
		else
			node = node->Right;
	}
	return node;
}

// 返回二叉搜索树BST中最小元结点的指针
Position FindMin( BinTree BST )
{
	if (!BST->Left)
		return BST;
	return FindMin(BST->Left);
}

// 返回二叉搜索树BST中最大元结点的指针
Position FindMax( BinTree BST )
{
	if (!BST->Right)
		return BST;
	return FindMax(BST->Right);
}
