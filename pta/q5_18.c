#include <stdlib.h>
#include <stdio.h>

#define MAX 1000
#define ERROR 1e8
typedef int ElementType;
typedef enum { false, true } bool;
typedef int Position;
struct SNode {
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;

int times = 0;

Stack CreateStack(int MaxSize)
{
    Stack stack;
    int *data;
    stack = (Stack)malloc(sizeof(struct SNode));
    data = (int*)malloc(sizeof(int) * MaxSize);
    stack->Data = data;
    stack->Top1 = -1;
    stack->Top2 = MaxSize;
    stack->MaxSize = MaxSize;
    return stack;
}

bool Push(Stack S,ElementType X,int Tag)
{
    if (S->Top2 - S->Top1 == 1)
    {
        printf("Stack Full\n");
        return 0;
    }

    if (Tag == 1)
        S->Data[++(S->Top1)] = X;
    else
        S->Data[--(S->Top2)] = X;

    return true;
}

ElementType Pop(Stack S,int Tag)
{
    if (Tag == 1)
    {
        if (S->Top1 == -1)
        {
            return ERROR;
        }
        else
            return S->Data[(S->Top1)--];
    }
    else
    {
        if (S->Top2 == S->MaxSize)
        {
            return ERROR;
        }
        else
            return S->Data[(S->Top2)++];
    }
}

bool Empty(Stack S, int Tag)
{
    if (Tag == 1)
        return S->Top1 < 0;
    else
        return S->Top2 >= S->MaxSize;
}

void Print(Stack S, int Tag, int N)
{
    int i = Pop(S, Tag);
    if (i == ERROR)
        return;
    if (++times == N)
        printf("%d", i);
    else
        printf("%d ", i);
}

void PopAll(Stack S, int N)
{
    int i;
    while (!Empty(S, 1) || !Empty(S, 2))
    {
        Print(S, 1, N);
        Print(S, 1, N);
        Print(S, 2, N);
    }
}

int main()
{
    int N, t, Time;
    int tmp[MAX] = {0};
    int i = 0;
    Stack S = CreateStack(MAX);

    scanf("%d ", &N);
    Time = N;
    while (N--) {
        scanf("%d", &t);
        tmp[i++] = t;
    }

    // TODO: 倒叙放入栈，能实现效果， 但用队列较好。
    for(i = i - 1; i >= 0; i--)
    {
        // 奇数去A
        if (tmp[i] % 2 == 1)
            Push(S, tmp[i], 1);
        else
            Push(S, tmp[i], 2);
    }

    PopAll(S, Time);
    return 0;
}
