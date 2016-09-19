#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"

#define MAX 9
int main()
{
    BinTree BT = NULL;
    ElementType ca[MAX] = { 4, 6, 5, 1, 8, 9, 2, 3, 7 };
    int i;
    for (i = 0; i < MAX; i++)
        BT = Insert(BT, ca[i]);

    printf("height: %d\n", GetHeight(BT));

    // test find
    assert(Find(BT, 4) == BT);
    assert(Find(BT, 5)->Data == 5);
    assert(Find(BT, 34) == NULL);

    // test min
    assert(FindMin(BT)->Data == 1);
    BT = Insert(BT, 0);
    assert(FindMin(BT)->Data == 0);

    // test max
    assert(FindMax(BT)->Data == 9);
    BT = Insert(BT, 12);
    assert(FindMax(BT)->Data == 12);

    // test delete
    Delete(BT, 1);
    assert(Delete(BT, 6) == BT);
    assert(Delete(BT, 53) == BT);
    assert(Find(BT, 1) == NULL);
    printf("pass!\n");

    return 0;
}
