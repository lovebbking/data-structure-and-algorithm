// 5-3 树的同构   (25分)
// 给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。
//
//
// 图1
//
//
//
// 图2
//
// 现给定两棵树，请你判断它们是否是同构的。
// 输入格式:
//
// 输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数NN (\le 10≤10)，即该树的结点数（此时假设结点从0到N-1N−1编号）；随后NN行，第ii行对应编号第ii个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。
//
// 输出格式:
//
// 如果两棵树是同构的，输出“Yes”，否则输出“No”。
//
// 输入样例1（对应图1）：
//
// 8
// A 1 2
// B 3 4
// C 5 -
// D - -
// E 6 -
// G 7 -
// F - -
// H - -
// 8
// G - 4
// B 7 6
// F - -
// A 5 1
// H - -
// C 0 -
// D - -
// E 2 -
// 输出样例1:
//
// Yes
// 输入样例2（对应图2）：
//
// 8
// B 5 7
// F - -
// A 0 3
// C 6 -
// H - -
// D - -
// G 4 -
// E 1 -
// 8
// D 6 -
// B 5 -
// E - -
// H - -
// C 0 2
// G - 3
// F - -
// A 1 4
// 输出样例2:
//
// No

#include <stdlib.h>
#include <stdio.h>

#define MaxTree 10

typedef enum {false, true} bool;
typedef char ElementType;
typedef int Tree;

// 用数组实现树。
typedef struct TreeNode {
    ElementType Data;
    Tree  Left;
    Tree  Right;
} TreeNode;
typedef struct TreeNode *PtrToTNode;

TreeNode T1[MaxTree], T2[MaxTree];

int TransChar(char c)
{
    if(c == '-')
        return -1;
    return c - '0';
}

void checkRoot(int checks[], int i)
{
    if (i < 0)
        return;
    checks[i] = 1;
    return;
}

Tree CreateTree(TreeNode T[])
{
    int N, i = 0;
    char D, L, R;
    int checks[MaxTree] = {0};
    PtrToTNode Node;

    scanf("%d", &N);
    while (i < N)
    {
        scanf("\n%c %c %c", &D, &L, &R);
        Node = (PtrToTNode)malloc(sizeof(struct TreeNode));

        Node->Data = D;
        Node->Left = TransChar(L);
        Node->Right = TransChar(R);

        T[i] = *Node;
        checkRoot(checks, Node->Right);
        checkRoot(checks, Node->Left);
        i++;
    }

    for (i = 0; i < N; i++)
        if (checks[i] == 0)
            return i;
    return -1;
}

bool Isomorphic(Tree R1, Tree R2)
{
    if (R1 == -1 && R2 == -1)
        return true;
    if ((R1 == -1 && R2 != -1) || (R1 != -1 && R2 == -1))
        return false;
    // 现在R1, R2都不可能为空
    char D1 = T1[R1].Data;
    char D2 = T2[R2].Data;
    if (D1 != D2)
        return false;

    if (((T1[R1].Left != -1) && (T2[R2].Left != -1))
            && ((T1[T1[R1].Left].Data) == (T2[T2[R2].Left].Data)))
        return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
    else
        return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
}
int main()
{
    Tree R1 = CreateTree(T1);
    Tree R2 = CreateTree(T2);

    if (Isomorphic(R1, R2))
        printf("Yes\n");
    else
        printf("No\n");
    return 0;
}
