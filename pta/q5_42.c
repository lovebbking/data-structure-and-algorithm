// 给定一系列整型关键字和素数PP，用除留余数法定义的散列函数将关键字映射到长度为PP的散列表中。用线性探测法解决冲突。
//
// 输入格式:
//
// 输入第一行首先给出两个正整数NN（\le 1000≤1000）和PP（\ge N≥N的最小素数），分别为待插入的关键字总数、以及散列表的长度。第二行给出NN个整型关键字。数字间以空格分隔。
//
// 输出格式:
//
// 在一行内输出每个整型关键字在散列表中的位置。数字间以空格分隔，但行末尾不得有多余空格。
//
// 输入样例:
//
// 4 5
// 24 15 61 88
// 输出样例:
//
// 4 0 1 3

#include <stdlib.h>
#include <stdio.h>

#define EMPTY -1
#define OCCUPY 1

typedef int Position;
typedef int KeyType;
typedef int ValueType;

typedef struct Cell {
    int Info;
    KeyType Key;
    ValueType Value;
} Cell;

typedef struct HashTbl *HashTable;
typedef struct HashTbl {
    int TableSize;
    Cell *TheCells;
} HashTbl;

int P;

int Hash(int key) { return key % P; }

HashTable initHashTable(int TableSize)
{
    int i;
    HashTable H = (HashTable)malloc(sizeof(struct HashTbl));

    H->TableSize = TableSize;
    H->TheCells = (Cell *)malloc(sizeof(struct Cell) * H->TableSize);

    for (i = 0; i < H->TableSize; i++)
        H->TheCells[i].Info = EMPTY;

    return H;
}

Position Find(HashTable H, KeyType Key)
{
    Position Pos = Hash(Key);
    while (H->TheCells[Pos].Info != EMPTY && H->TheCells[Pos].Key != Key)
    {
        if (Pos < H->TableSize)
            Pos++;
        else
            Pos = 0;
    }

    return Pos;
}

int main()
{
    int N, TableSize;
    int key;
    scanf("%d %d", &N, &P);
    getchar();
    TableSize = P;
    HashTable H = initHashTable(TableSize);

    while (N--)
    {
        scanf("%d", &key);
        if (N == 0)
            printf("%d", Find(H, key));
        else
            printf("%d ", Find(H, key));
    }
    return 0;
}
