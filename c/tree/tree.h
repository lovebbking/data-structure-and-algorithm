typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

// 打印树
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );


// 函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针；
BinTree Insert(BinTree BST, ElementType X);

// 给定二叉树的高度。
int GetHeight(BinTree BT);

// 按照先序遍历的顺序输出给定二叉树BT的叶结点，格式为一个空格跟着一个字符。
void PreorderPrintLeaves( BinTree BT );

// 将X从二叉搜索树BST中删除，并返回结果树的根结点指针；如果X不在树中，则打印一行Not Found并返回原树的根结点指针
BinTree Delete( BinTree BST, ElementType X );

// 在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
Position Find( BinTree BST, ElementType X );

// 返回二叉搜索树BST中最小元结点的指针
Position FindMin( BinTree BST );

// 返回二叉搜索树BST中最大元结点的指针
Position FindMax( BinTree BST );
