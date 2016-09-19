// 给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。
//
// 输入格式:
//
// 输入首先给出正整数NN（\le 10^5≤10
// ​5
// ​​ ），为通话记录条数。随后NN行，每行给出一条通话记录。简单起见，这里只列出拨出方和接收方的11位数字构成的手机号码，其中以空格分隔。
//
// 输出格式:
//
// 在一行中给出聊天狂人的手机号码及其通话次数，其间以空格分隔。如果这样的人不唯一，则输出狂人中最小的号码及其通话次数，并且附加给出并列狂人的人数。
//
// 输入样例:
//
// 4
// 13005711862 13588625832
// 13505711862 13088625832
// 13588625832 18087925832
// 15005713862 13588625832
// 输出样例:
//
// 13588625832 3

#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1
#define OCCUPY 1

typedef int Position;
typedef long KeyType;
typedef int ValueType;

typedef struct Cell {
    int Info;
    KeyType Element;
    ValueType Value;
} Cell;

typedef struct HashTbl *HashTable;
typedef struct HashTbl {
    int TableSize;
    Cell *TheCells;
} HashTbl;

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
    return key % size;
}

// 平方探测
Position Find(HashTable H, KeyType Key)
{
    Position CurrentPos, NewPos;
    int CNum = 0;
    NewPos = CurrentPos = Hash(Key, H->TableSize);
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

void InsertOrAddOne(HashTable H, KeyType Key)
{
    Position Pos = Find(H, Key);
    if (H->TheCells[Pos].Info != OCCUPY)
    {
        // 插入！
        H->TheCells[Pos].Info = OCCUPY;
        H->TheCells[Pos].Element = Key;
        H->TheCells[Pos].Value = 1;
    }
    else
        H->TheCells[Pos].Value++;
}

int main()
{
    int N;
    long phone1, phone2, result;
    int Size = 10, i, tmp;
    HashTable H = initHashTable(Size);

    scanf("%d", &N);

    while (N--)
    {
        scanf("%ld %ld", &phone1, &phone2);
        InsertOrAddOne(H, phone1);
        InsertOrAddOne(H, phone2);
    }

    tmp = -1;
    for (i = 0; i < Size + 1; i++)
    {
        if (H->TheCells[i].Info == OCCUPY && H->TheCells[i].Value >= tmp)
        {
            tmp = H->TheCells[i].Value;
            result = H->TheCells[i].Element;
        }
    }

    printf("%ld %d", result, tmp);
    return 0;
}
