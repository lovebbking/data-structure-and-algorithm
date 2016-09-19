// 不少航空公司都会提供优惠的会员服务，当某顾客飞行里程累积达到一定数量后，可以使用里程积分直接兑换奖励机票或奖励升舱等服务。现给定某航空公司全体会员的飞行记录，要求实现根据身份证号码快速查询会员里程积分的功能。
//
// 输入格式:
//
// 输入首先给出两个正整数NN（\le 10^5≤10
// ​5
// ​​ ）和KK（\le 500≤500）。其中KK是最低里程，即为照顾乘坐短程航班的会员,航空公司还会将航程低于KK公里的航班也按KK公里累积。随后NN行，每行给出一条飞行记录。飞行记录的输入格式为：18位身份证号码（空格）飞行里程。其中身份证号码由17位数字加最后一位校验码组成，校验码的取值范围为0~9和x共11个符号；飞行里程单位为公里，是(0, 15 000]区间内的整数。然后给出一个正整数MM（\le 10^5≤10
// ​5
// ​​ ），随后给出MM行查询人的身份证号码。
//
// 输出格式:
//
// 对每个查询人，给出其当前的里程累积值。如果该人不是会员，则输出No Info。每个查询结果占一行。
//
// 输入样例:
//
// 4 500
// 330106199010080419 499
// 110108198403100012 15000
// 120104195510156021 800
// 330106199010080419 1
// 4
// 120104195510156021
// 110108198403100012
// 330106199010080419
// 33010619901008041x
// 输出样例:
//
// 800
// 15000
// 1000
// No Info


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define EMPTY -1
#define OCCUPY 1
#define IDMAX 18
#define TABLESIZEMAX 10000

typedef int Position;
typedef char *KeyType;
typedef int ValueType;

typedef struct Cell *PtrToCell;
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

int Hash(KeyType key, int TableSize)
{
    // 取身份证号的年月日和最后一位算出hash值。
    // 33010619901008041x
    //          ^ ^ ^   ^  x算作11
    int sum =  (key[9] - '0') * (int)pow(32, 3)
    + (key[11] - '0') * (int)pow(32, 2)
    + (key[13] - '0') * (int)pow(32, 1)
    + (key[17] == 'x' ? 11 : (key[13] - '0'));
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
    // 最终会找到一个Info为EMPTY 或 Key 相同的位置。
    while (H->TheCells[NewPos].Info != EMPTY && strcmp(H->TheCells[NewPos].Key, Key) != 0)
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
int InsertValue(HashTable H, KeyType Key, ValueType Value)
{
    Position Pos = Find(H, Key);
    PtrToCell c = &H->TheCells[Pos];
    if (c->Info == EMPTY)
    {
        c->Info = OCCUPY;
        c->Key = (KeyType)malloc(sizeof(char) * IDMAX);
        strcpy(c->Key, Key);
        c->Value = Value;
    }
    else
        c->Value += Value;
    return Pos;
}

void PrintValue(HashTable H, KeyType K)
{
    Position Pos = Find(H, K);
    if (H->TheCells[Pos].Info == OCCUPY)
        printf("%d\n", H->TheCells[Pos].Value);
    else
        printf("No Info\n");
}

int main()
{
    int N, MinMile, Mile;
    char key[IDMAX];
    scanf("%d %d", &N, &MinMile);
    getchar();
    HashTable H = initHashTable(TABLESIZEMAX);

    while (N--)
    {
        scanf("%s %d", key, &Mile);
        InsertValue(H, key, (Mile < MinMile ? MinMile : Mile));
    }

    scanf("%d", &N);
    while (N--)
    {
        scanf("%s", key);
        PrintValue(H, key);
    }

    return 0;
}
