#define EMPTY -1
#define OCCUPY 1

typedef int Position;
typedef int ElementType;
typedef int ValueType;

typedef struct Cell {
    int Info;
    ElementType Element;
    ValueType Value;
} Cell;

typedef struct HashTbl *HashTable;
typedef struct HashTbl {
    int TableSize;
    Cell *TheCells;
} HashTbl;

HashTable initHashTable(int TableSize);

Position Find(HashTable H, ElementType Key);

void Insert(HashTable H, ElementType Key);

int hash(int key);
int NextPrime(int size);

// TODO: insert 一个value
void InsertValue(HashTable H, ElementType Key, ValueType Value);
//
// void Delete(HashTable H, ElementType Key);
