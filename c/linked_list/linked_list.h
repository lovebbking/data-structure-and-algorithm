// 链表
#define TRUE  1
#define FALSE 0

#define ERROR -1
#define POINT_ERROR NULL
typedef int ElementType;

typedef struct Node *PtrToNode;
typedef struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
} Node;
typedef PtrToNode Position; /* 定义位置类型 */
typedef PtrToNode List; /* 定义单链表类型 */

// 打印链表 （debug）
void printList(List l);

// 链表接口

// 判断链表是否为空
int isEmpty(List l);

// 返回链表长度
int length(List l);

// 根据index返回链表Node里的data，没有则返回ERROR
// index以1开始
ElementType findIndex(List l, int k);

// 返回线性表中首次出现X的位置。若找不到则返回ERROR；
Position find(List l, ElementType x);

// 将X插入在位置P指向的结点之前，返回链表的表头。如果参数P指向非法位置，则打印“Wrong Position for Insertion”，返回ERROR；
List insert(List l, ElementType x, Position p);

// 将位置P的元素删除并返回链表的表头。若参数P指向非法位置，则打印“Wrong Position for Deletion”并返回ERROR。
List delete(List l, Position p);
