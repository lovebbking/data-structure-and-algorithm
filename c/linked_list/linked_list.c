#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void printList(List l)
{
    for(; l; l = l->Next)
    {
        printf("%d ", l->Data);
    }
    printf("\n");
}

int isEmpty(List l)
{
    return l->Next == NULL;
}

int length(List l)
{
    int length = 0;
    for (; l; l = l->Next)
    {
        length++;
    }
    return length;
}

ElementType findIndex(List l, int k)
{
    if (k < 1) return ERROR;

    int i = 1;
    for (; l; l = l->Next, i++)
        if (i == k)
            return l->Data;
    return ERROR;
}

Position find(List l, ElementType x)
{
    for(; l; l = l->Next)
    {
        if (l->Data == x)
        {
            return l;
        }
    }
    return POINT_ERROR;
}

List insert(List l, ElementType x, Position p)
{
    Position tmp, head;
    PtrToNode n = (PtrToNode)malloc(sizeof(struct Node));
    n->Data = x;
    n->Next = NULL;

    // 插入表头时
    if (l == p)
    {
        n->Next = l;
        return n;
    }

    for (head = l; head; head = head->Next)
    {
        if (head->Next == p) {
            tmp = head->Next;
            head->Next = n;
            n->Next = tmp;
            return l;
        }
    }
    free(n);
    printf("Wrong Position for Insertion\n");
    return POINT_ERROR;
}

List delete(List l, Position p)
{
    Position head;

    // 删除表头时
    if (l == p)
    {
        return l->Next;
    }

    for (head = l; head; head = head->Next)
    {
        if (head->Next == p)
        {
            head->Next = head->Next->Next;
            return l;
        }
    }
    printf("Wrong Position for Deletion\n");
    return POINT_ERROR;
}
