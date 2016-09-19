// 给定一系列由大写英文字母组成的字符串关键字和素数PP，用移位法定义的散列函数H(Key)H(Key)
// 将关键字KeyKey中的最后3个字符映射为整数，每个字符占5位；再用除留余数法将整数映射到长度为PP的散列表中。例如将字符串AZDEG插入长度为1009的散列表中，我们首先将26个大写英文字母顺序映射到整数0~25；再通过移位将其映射为3\times 32^2 + 4 \times 32 + 6 = 32063×32
// ​2
// ​​ +4×32+6=3206；然后根据表长得到，即是该字符串的散列映射位置。
//
// 发生冲突时请用平方探测法解决。
//
// 输入格式:
//
// 输入第一行首先给出两个正整数NN（\le 500≤500）和PP（\ge
// 2N≥2N的最小素数），分别为待插入的关键字总数、以及散列表的长度。第二行给出NN个字符串关键字，每个长度不超过8位，其间以空格分隔。
//
// 输出格式:
//
// 在一行内输出每个字符串关键字在散列表中的位置。数字间以空格分隔，但行末尾不得有多余空格。
//
// 输入样例1:
//
// 4 11
// HELLO ANNK ZOE LOLI
// 输出样例1:
//
// 3 10 4 0
// 输入样例2:
//
// 6 11
// LLO ANNA NNK ZOJ INNK AAA
// 输出样例2:
//
// 3 0 10 9 6 1


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define EMPTY -1
#define OCCUPY 1

typedef int Position;
typedef char *KeyType;
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

int Hash(KeyType key, int TableSize)
{
    int sum = 0, times = 3;
    for (int i = strlen(key) - 3; i < strlen(key); i++)
    {
        sum += (key[i] - 'A') * (int)pow(32, --times);
    }
    return sum % TableSize;
}

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
    Position CurrentPos, NewPos;
    int CNum = 0;
    NewPos = CurrentPos = Hash(Key, H->TableSize);
    while (H->TheCells[NewPos].Info != EMPTY)
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
int Insert(HashTable H, KeyType Key)
{
    Position Pos = Find(H, Key);
    H->TheCells[Pos].Info = OCCUPY;

    return Pos;
}

int main()
{
    int N, TableSize;
    char key[8];
    scanf("%d %d", &N, &P);
    getchar();
    TableSize = P;
    HashTable H = initHashTable(TableSize);

    while (N--)
    {
        scanf("%s", key);
        if (N == 0)
            printf("%d", Insert(H, key));
        else
            printf("%d ", Insert(H, key));
    }
    return 0;
}
