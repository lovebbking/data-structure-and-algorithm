#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"

int main()
{
    // 一个 [12, 2, 4, 87, 10, 2]的链表

    List l;

    // test make empty
    l = MakeEmpty();

    assert(l->Next == NULL);

    // test insert
    Insert(l, 12, NULL);
    Insert(l, 2, NULL);
    Insert(l, 4, NULL);
    Insert(l, 87, NULL);
    Insert(l, 10, NULL);
    Insert(l, 2, NULL);
    printList(l);

    assert(l->Next->Data == 12);

    // test find
    assert(Find(l, 12)->Data == 12);
    assert(Find(l, 2)->Data == 2);
    assert(Find(l, 54) == ERROR);

    // test delete
    assert(Delete(l, Find(l, 63)) == false);
    assert(Delete(l, Find(l, 2)) == true);
    assert(Delete(l, Find(l, 2)) == true);

    printf("pass\n");
}
