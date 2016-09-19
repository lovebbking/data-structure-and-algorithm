#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

// typedef int Position;
// struct SNode {
//     ElementType *Data;
//     Position Top1, Top2;
//     int MaxSize;
// };
// typedef struct SNode *Stack;
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
            printf("Stack %d Empty\n",Tag);
            return ERROR;
        }
        else
            return S->Data[(S->Top1)--];
    }
    else
    {
        if (S->Top2 == S->MaxSize)
        {
            printf("Stack %d Empty\n",Tag);
            return ERROR;
        }
        else
            return S->Data[(S->Top2)++];
    }
}
