// 5-19 求链式线性表的倒数第K项   (20分)
// 给定一系列正整数，请设计一个尽可能高效的算法，查找倒数第K个位置上的数字。
//
// 输入格式:
//
// 输入首先给出一个正整数K，随后是若干正整数，最后以一个负整数表示结尾（该负数不算在序列内，不要处理）。
//
// 输出格式:
//
// 输出倒数第K个位置上的数据。如果这个位置不存在，输出错误信息NULL。
//
// 输入样例:
//
// 4 1 2 3 4 5 6 7 8 9 0 -1
// 输出样例:
//
// 7

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

int k; //倒数第K个位置

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

PtrToNode findReverseIndex(List l)
{
    PtrToNode h;
    int length = 0;
    int i;

    for (h = l; h; h = h->Next)
        ++length;

    if ((length - k) < 0)
        return NULL;

    for(h = l, i = 0;  h; h = h->Next, i++)
        if (i == length - k)
            break;

    return h;
}

int main()
{
    List l;
    PtrToNode result;

    // 读取位置
    scanf("%d", &k);
    l = createList();

    result = findReverseIndex(l);

    if (result == NULL)
        printf("NULL\n");
    else
        printf("%d\n", result->Data);
    return 0;
}
