// 设计函数分别求两个一元多项式的乘积与和。
//
// 输入格式:
//
// 输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
//
// 输出格式:
//
// 输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。
//
// 输入样例:
//
// 4 3 4 -5 2  6 1  -2 0
// 3 5 20  -7 4  3 1
// 输出样例:
//
// 15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
// 5 20 -4 4 -5 2 9 1 -2 0

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
typedef struct Node {
    ElementType Coefficient; /* 系数 */
    ElementType Exponent; /* 指数 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
    PtrToNode   Prev; /* 指向上一个结点的指针 */
} Node;
typedef PtrToNode Position; /* 定义位置类型 */
typedef PtrToNode List; /* 定义单链表类型 */

void printList(List l)
{
    if(!l)
    {
        printf("0 0");
        return;
    }
    for(; l; l = l->Next)
    {
        if (!l->Next)
            printf("%d %d", l->Coefficient, l->Exponent);
        else
            printf("%d %d ", l->Coefficient, l->Exponent);
    }
}

List createList(int N)
{
    List l = NULL;
    List h;
    PtrToNode tmp;

    int c, e;

    while (N--)
    {
        scanf("%d", &c);
        scanf("%d", &e);
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Coefficient = c;
        tmp->Exponent = e;
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
    }
    return l;
}

List addNode(List l, int c, int e)
{
    PtrToNode prev;
    PtrToNode node = (PtrToNode)malloc(sizeof(struct Node));
    node->Coefficient = c;
    node->Exponent = e;
    node->Next = node->Prev = NULL;
    if (l == NULL)
        return node;
    // 比较指数, 相同则加系数
    else if (l->Exponent == e)
    {
        l->Coefficient = l->Coefficient + c;
        free(node);
        return l;
    }
    // 若比当前结点的指数大，放到前面
    else if (l->Exponent < e)
    {
        // 若l是头结点
        if (!l->Prev)
        {
            node->Next = l;
            l->Prev = node;
            return node;
        }
        // 若l是尾结点，或中间结点
        else
        {
            // 插在前面
            prev = l->Prev;
            prev->Next = node;
            l->Prev = node;
            node->Prev = prev;
            node->Next = l;
            return node;
        }
    }
    // 比当前结点指数小，递归插入。
    else
        l->Next = addNode(l->Next, c, e);

    return l;
}

List Multiple(List l1, List l2)
{
    List m = NULL, h2;
    int c, e;

    for (; l1; l1 = l1->Next)
        for (h2 = l2; h2; h2 = h2->Next)
        {
            c = l1->Coefficient * h2->Coefficient;
            e = l1->Exponent + h2->Exponent;
            m = addNode(m, c, e);
        }
    return m;
}

List AddList(List l1, List l2)
{
    List a = NULL;
    int c, e;

    for (; l1; l1 = l1->Next)
        a = addNode(a, l1->Coefficient, l1->Exponent);
    for (; l2; l2 = l2->Next)
        a = addNode(a, l2->Coefficient, l2->Exponent);
    return a;
}

int main()
{
    // List l = createList();
    int N, c, e;
    List l1, l2, m, a;

    scanf("%d", &N);
    l1 = createList(N);

    getchar();
    scanf("%d", &N);
    l2 = createList(N);

    m = Multiple(l1, l2);
    a = AddList(l1, l2);

    printList(m);
    printf("\n");
    printList(a);
    return 0;
}
