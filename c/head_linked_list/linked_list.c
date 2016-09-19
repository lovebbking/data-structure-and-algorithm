#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void printList(List l)
{
    for(; l->Next; l = l->Next)
    {
        printf("%d ", l->Next->Data);
    }
    printf("\n");
}

List MakeEmpty()
{
    List l = (List)malloc(sizeof(struct LNode));
    l->Next = NULL;
    return l;
}

bool Insert(List l, ElementType x, Position p)
{
    PtrToLNode tmp;
    PtrToLNode n = (PtrToLNode)malloc(sizeof(struct LNode));
    n->Data = x;
    n->Next = NULL;

    for (; l; l = l->Next)
    {
        if(l->Next == p)
        {
            tmp = l->Next;
            l->Next = n;
            n->Next = tmp;
            return true;
        }
    }
    free(n);
    printf("Wrong Position for Insertion\n");
    return false;
}

Position Find( List l, ElementType x )
{
    for (; l; l = l->Next)
    {
        if (l->Data == x)
        {
            return l;
        }
    }
    return ERROR;
}

bool Delete( List l, Position p )
{
    for(; l->Next; l = l->Next)
    {
        if (l->Next == p)
        {
            l->Next = l->Next->Next;
            return true;
        }
    }
    printf("Wrong Position for Deletion\n");
    return false;
}
