#define MAXSIZE 5
#define NotFound 0
#define ERROR -1
typedef enum {false, true} bool;
typedef int ElementType;
typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

// 创建并返回一个空的线性表；
List MakeEmpty();

// 返回线性表中X的位置。若找不到则返回ERROR；
Position Find( List L, ElementType X );

// 将X插入在位置P并返回true。若空间已满，则打印“FULL”并返回false；如果参数P指向非法位置，则打印“ILLEGAL POSITION”并返回false；
bool Insert( List L, ElementType X, Position P );

// 将位置P的元素删除并返回true。若参数P指向非法位置，则打印“POSITION P EMPTY”（其中P是参数值）并返回false。
bool Delete( List L, Position P );

// 函数BinarySearch要查找K在Tbl中的位置，即数组下标（注意：元素从下标1开始存储）。找到则返回下标，否则返回一个特殊的失败标记NotFound。
Position BinarySearch( List Tbl, ElementType K );
