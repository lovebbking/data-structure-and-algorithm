#include <stdlib.h>
#include <stdio.h>
#include "sequence_list.h"

List MakeEmpty()
{
    List l = (List)malloc(sizeof(List));
    l->Last = -1;
    return l;
}

// 将X插入在位置P并返回true。若空间已满，则打印“FULL”并返回false；如果参数P指向非法位置，则打印“ILLEGAL POSITION”并返回false；
bool Insert( List L, ElementType X, Position P )
{
    int i;
    // 空间已满
    if(L->Last >= MAXSIZE - 1)
    {
        printf("FULL");
        return false;
    }
    // 非法位置
    if(P < 0 || P > MAXSIZE - 1 || P > (L->Last + 1) )
    {
        printf("ILLEGAL POSITION");
        return false;
    }

    // 插在最后一个之后
    if (P > L->Last)
    {
        L->Data[P] = X;
    }
    else //插在最后一个或者之前
    {
        for (i = MAXSIZE - 2; i >= P; i--)
        {
            L->Data[i + 1] = L->Data[i];
        }
        L->Data[P] = X;
    }
    L->Last++;
    return true;
}

// 返回线性表中X的位置。若找不到则返回ERROR；
Position Find( List L, ElementType X )
{
    if( NULL == L || -1 == L->Last )
    {
        return ERROR;
    }
    int i;
    for (i = 0; i <= L->Last; i++)
        if (L->Data[i] == X)
            return i;
    return ERROR;
}

// 将位置P的元素删除并返回true。若参数P指向非法位置，则打印“POSITION P EMPTY”（其中P是参数值）并返回false。
bool Delete( List L, Position P )
{
    int i;

    if(P < 0 || P > L->Last)
    {
        printf("POSITION %d EMPTY", P);
        return false;
    }

    for (i = P; i < L->Last - 1; i++)
    {
        L->Data[i] = L->Data[i + 1];
    }

    L->Last--;
    return true;
}

// 二分查找， 前提是必须要保证list是递增有序的
Position BinarySearch( List l, ElementType K )
{
    Position low = 0;
    Position high = l->Last;
    Position mid;

    if(!l)
        return NotFound;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if (l->Data[mid] == K)
            return mid + 1;

        if (l->Data[mid] > K)
            high = mid - 1;
        else
            low = mid + 1;
    }

    return NotFound;
}
