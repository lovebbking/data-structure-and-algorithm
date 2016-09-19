#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int NextPrime(int size)
{
    return size + 1;
}

HashTable initHashTable(int TableSize)
{
    int i;
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));

    H->TableSize = NextPrime(TableSize);
    H->TheCells = (Cell *)malloc(sizeof(struct Cell) * H->TableSize);

    for (i = 0; i < H->TableSize; i++)
        H->TheCells[i].Info = EMPTY;

    return H;
}

int Hash(int key, int size)
{
    return key % 12;
}

// 平方探测
Position Find(HashTable H, ElementType Key)
{
    Position CurrentPos, NewPos;
    int CNum = 0;
    NewPos = CurrentPos = Hash(Key, H->TableSize);
    // 最终会找到一个Info为EMPTY 或 Key 一样的位置。
    while (H->TheCells[NewPos].Info != EMPTY && H->TheCells[NewPos].Element != Key)
    {
        if (++CNum % 2)
        {
            NewPos = CurrentPos + (CNum + 1) / 2 * (CNum + 1) / 2;
            // 加多了减回来
            while (NewPos >= H->TableSize)
                NewPos -= H->TableSize;
        }
        else
        {
            NewPos = CurrentPos - CNum / 2 * CNum / 2;
            while (NewPos < 0)
                NewPos += H->TableSize;
        }
    }
    return NewPos;
}

void Insert(HashTable H, ElementType Key)
{
    Position Pos = Find(H, Key);
    if (H->TheCells[Pos].Info != OCCUPY)
    {
        // 插入！
        H->TheCells[Pos].Info = OCCUPY;
        H->TheCells[Pos].Element = Key;
    }
}

void InsertValue(HashTable H, ElementType Key, ValueType Value)
{
    Position Pos = Find(H, Key);
    if (H->TheCells[Pos].Info != OCCUPY)
    {
        // 插入！
        H->TheCells[Pos].Info = OCCUPY;
        H->TheCells[Pos].Element = Key;
    }
    H->TheCells[Pos].Value = Value;
}
