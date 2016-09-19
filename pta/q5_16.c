// 5-16 一元多项式求导   (20分)
// 设计函数求一元多项式的导数。
//
// 输入格式:
//
// 以指数递降方式输入多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。
//
// 输出格式:
//
// 以与输入相同的格式输出导数多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。
//
// 输入样例:
//
// 3 4 -5 2 6 1 -2 0
// 输出样例:
//
// 12 3 -10 1 6 0

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct Node *PtrToNode;
typedef struct Node {
    ElementType Coefficient; /* 系数 */
    ElementType Exponent; /* 指数 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
} Node;
typedef PtrToNode Position; /* 定义位置类型 */
typedef PtrToNode List; /* 定义单链表类型 */

void printList(List l)
{
    for(; l; l = l->Next)
    {
        if (l->Exponent == 0)
            printf("%d %d", l->Coefficient, l->Exponent);
        else
            printf("%d %d ", l->Coefficient, l->Exponent);
    }
    printf("\n");
}

List createList()
{
    List l = NULL;
    List h;
    PtrToNode tmp;

    int c, e;

    while (1)
    {
        scanf("%d", &c);
        scanf("%d", &e);
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Coefficient = c;
        tmp->Exponent = e;
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
        if (e == 0)
            return l;
    }
}

List Derivation(List l)
{
    List der = NULL;
    List h;
    PtrToNode tmp;
    for (; l->Exponent > 0; l = l->Next)
    {
        tmp = (PtrToNode)malloc(sizeof(struct Node));
        tmp->Coefficient = l->Coefficient * l->Exponent;
        tmp->Exponent = l->Exponent - 1;
        tmp->Next = NULL;
        
        if (der == NULL)
        {
            der = tmp;
            h = der;
        }
        else
        {
            h->Next = tmp;
            h = h->Next;
        }
    }
    return der;
}

int main()
{
    List l = createList();
    List der;

    der = Derivation(l);
    printList(der);
    return 0;
}
