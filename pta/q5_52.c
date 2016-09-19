// 5-52 两个有序链表序列的交集   (20分)
// 已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。
//
// 输入格式:
//
// 输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用-1−1表示序列的结尾（-1−1不属于这个序列）。数字用空格间隔。
//
// 输出格式:
//
// 在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
//
// 输入样例:
//
// 1 2 5 -1
// 2 4 5 8 10 -1
// 输出样例:
//
// 2 5


#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
typedef struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
} Node;
typedef PtrToNode Position; /* 定义位置类型 */
typedef PtrToNode List; /* 定义单链表类型 */

void printList(List l)
{
    for(; l; l = l->Next)
    {
        if (!l->Next)
        {
            printf("%d", l->Data);
        }
        else
        {
            printf("%d ", l->Data);
        }
    }
    printf("\n");
}

List createList()
{
    List l = NULL;
    List h;
    int x;
    PtrToNode tmp;

    scanf("%d", &x);

    while (x > -1)
    {
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Data = x;
        tmp->Next = NULL;

        if (l == NULL)
        {
            l = tmp;
            h = l;
        }
        else
        {
            h->Next = tmp;
            h = h->Next;
        }

        scanf("%d", &x);
    }
    return l;
}

List intersectionList(List l1, List l2)
{
    List u = NULL;
    PtrToNode h, tmp;
    PtrToNode i, j;
    for (i = l1; i; i = i->Next)
    {
        for (j = l2; j; j = j->Next)
        {
            if (i->Data == j->Data)
            {
                tmp = (PtrToNode)malloc(sizeof(struct Node));
                tmp->Data = i->Data;
                tmp->Next = NULL;
                if (u == NULL)
                {
                    u = tmp;
                    h = u;
                }
                else
                {
                    h->Next = tmp;
                    h = h->Next;
                }
            }
        }
    }
    return u;
}

int main()
{
    List l1, l2, u;
    l1 = createList();
    l2 = createList();
    u = intersectionList(l1, l2);
    if (u == NULL)
        printf("NULL");
    else
        printList(u);
}
