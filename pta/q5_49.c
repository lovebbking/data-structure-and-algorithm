#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define EMPTY -1
#define OCCUPY 1
#define IDMAX 4
#define TABLESIZEMAX 26 * 26 * 26 * 10


typedef struct Student {
    int Lessions[40000];
    int Count;
} Student;

typedef int Position;
typedef char *KeyType;
typedef Student *ValueType;

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
    int fir = (int)(key[0] - 'A') + 1;
    int sed = (int)(key[1] - 'A') + 1;
    int thi = (int)(key[2] - 'A') + 1;
    int fou = (int)(key[3] - '0') + 1;
    return fir * sed * thi * fou;
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

int InsertValue(HashTable H, KeyType Key, int lession)
{
    Position Pos = Find(H, Key);
    PtrToCell c = &H->TheCells[Pos];
    if (c->Info == EMPTY)
    {
        c->Info = OCCUPY;
        c->Key = (KeyType)malloc(sizeof(char) * IDMAX);
        strcpy(c->Key, Key);
        // 初始化value
        c->Value = (ValueType)malloc(sizeof(struct Student));
        c->Value->Lessions[0] = lession;
        c->Value->Count = 0;
    }
    else
        c->Value->Lessions[++c->Value->Count] = lession;
    return Pos;
}

int main()
{
    int N, Count, lessionNum, n, i, j;
    char Name[5];

    scanf("%d %d", &Count, &N);
    getchar();
    HashTable H = initHashTable(TABLESIZEMAX);

    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &lessionNum, &n);
        for (j = 0; j < n; j++)
        {
            scanf("%s", Name);
            InsertValue(H, Name, lessionNum);
        }
    }

    Student S;
    while(Count--)
    {
        scanf("%s", Name);
        S = *H->TheCells[Find(H, Name)].Value;
        printf("%s %d", Name, S.Count + 1);
        for (i = 0; i <= S.Count; i++) printf(" %d", S.Lessions[i]);
        printf("\n");
    }

    return 0;
}
