// 已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的并集新非降序链表S3。
//
// 输入格式:
//
// 输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用-1−1表示序列的结尾（-1−1不属于这个序列）。数字用空格间隔。
//
// 输出格式:
//
// 在一行中输出合并后新的非降序链表，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。
//
// 输入样例:
//
// 1 3 5 -1
// 2 4 6 8 10 -1
// 输出样例:
//
// 1 2 3 4 5 6 8 10

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
typedef struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
    PtrToNode   Prev; /* 指向上一个结点的指针 */
} Node;
typedef PtrToNode Position; /* 定义位置类型 */
typedef PtrToNode List; /* 定义单链表类型 */

List createList(int N)
{
    List l = NULL;
    List h;
    int x;
    PtrToNode tmp;

    scanf("%d", &x);

    while (1)
    {
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Data = x;
        tmp->Next = tmp->Prev = NULL;

        if (l == NULL)
        {
            l = tmp;
            h = l;
        }
        else
        {
            h->Next = tmp;
            tmp->Prev = h;
            h = h->Next;
        }
        if (!--N)
            break;
        scanf("%d", &x);
    }
    return l;
}

ElementType Median(List l1, List l2)
{
    PtrToNode h1 = l1, h2 = l2;
    PtrToNode t1, t2;
    int p = 0;
    int mid;
    // t1, t2放到链表末尾
    while (h1 && h2)
    {
        t1 = h1;
        t2 = h2;
        h1 = h1->Next;
        h2 = h2->Next;
    }

    while (l1 != t1 || l2 != t2)
    {
        p++;
        // 奇数次时删除最小的
        if (p % 2 == 1)
        {
            if (l1 == t1)
                l2 = l2->Next;
            else if (l2 == t2)
                l1 = l1->Next;
            else if (l1->Data < l2->Data)
                l1 = l1->Next;
            else
                l2 = l2->Next;
        }
        // 偶数次时删除最大的
        else
        {
            if (l1 == t1)
                t2 = t2->Prev;
            else if (l2 == t2)
                t1 = t1->Prev;
            else if (t1->Data > t2->Data)
                t1 = t1->Prev;
            else
                t2 = t2->Prev;
        }
    }
    mid = t1->Data < t2->Data ? t1->Data : t2->Data;
    return mid;
}

int main()
{
    int N;
    List l1, l2;
    ElementType M;
    scanf("%d", &N);
    getchar();
    l1 = createList(N);
    getchar();
    l2 = createList(N);

    printf("%d", Median(l1, l2));
}
