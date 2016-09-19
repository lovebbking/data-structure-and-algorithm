#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash.h"

int main()
{
    HashTable H = initHashTable(13);
    int Key = 5;
    Position Pos = Find(H, Key);
    Position newPos;

    assert(H->TheCells[Pos].Info == EMPTY);
    // test insert and find
    Insert(H, Key);
    assert(H->TheCells[Pos].Info == OCCUPY);
    InsertValue(H, Key, 90);
    newPos = Find(H, Key);
    assert(Pos == newPos);
    assert(H->TheCells[newPos].Info == OCCUPY);
    assert(H->TheCells[newPos].Value == 90);

    printf("pass!\n");
    return 0;
}
