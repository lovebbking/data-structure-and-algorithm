#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "sequence_list.h"

int main()
{
    List L;
    ElementType X;
    Position P;
    int N;

    L = MakeEmpty();

    // test Insert
    Insert(L, 1, 0);
    Insert(L, 2, 0);
    Insert(L, 3, 0);
    assert(L->Data[2] == 1);
    assert(L->Data[1] == 2);
    assert(L->Last == 2);

    Insert(L, 4, 2);
    assert(L->Data[2] == 4);
    assert(L->Data[3] == 1);

    // test insert error
    assert(Insert(L, 5, 13) == false);

    // test find

    assert(Find(L, 4) == 2);
    assert(Find(L, 5) == ERROR);

    // test delete
    assert(Delete(L, 7) == false);
    assert(Delete(L, 1) == true);

    assert(L->Last == 2);
    assert(Find(L, 1) == ERROR);

    L = MakeEmpty();
    Insert(L, 101, 0);
    Insert(L, 89, 0);
    Insert(L, 55, 0);
    Insert(L, 31, 0);
    Insert(L, 12, 0);
    printf("\nSearch 31: %d\n", BinarySearch(L, 31));
    printf("\nSearch 102: %d\n", BinarySearch(L, 102));
    
    L = MakeEmpty();
    Insert(L, 233, 0);
    Insert(L, 78, 0);
    Insert(L, 26, 0);
    printf("\nSearch 31: %d\n", BinarySearch(L, 31));
    printf("\nSearch 233: %d\n", BinarySearch(L, 233));

    printf("\npass!\n");
}
