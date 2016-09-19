// 借助堆栈以非递归（循环）方式求解汉诺塔的问题（n, a, b, c），即将N个盘子从起始柱（标记为“a”）通过借助柱（标记为“b”）移动到目标柱（标记为“c”），并保证每个移动符合汉诺塔问题的要求。
//
// 输入格式:
//
// 输入为一个正整数N，即起始柱上的盘数。
//
// 输出格式:
//
// 每个操作（移动）占一行，按柱1 -> 柱2的格式输出。
//
// 输入样例:
//
// 3
// 输出样例:
//
// a -> c
// a -> b
// c -> b
// a -> c
// b -> a
// b -> c
// a -> c

#include <stdlib.h>
#include <stdio.h>
void move(char F, char T);

// TODO: 非递归算法

// 递归算法
// 如要从A移动到C。
void Hanoi(int n, char From, char To, char Bridge)
{
    if (n == 1)
    {
        move(From, To);
        return;
    }
    // 先将上面n - 1个移动到Bridge先。
    Hanoi(n - 1, From, Bridge, To);
    // move这一个
    move(From, To);
    // 再将n - 1个从Bridge移动到To
    Hanoi(n - 1, Bridge, To, From);
}

void move(char F, char T)
{
    printf("%c -> %c\n", F, T);
}

int main()
{
    int N;
    scanf("%d", &N);

    Hanoi(N,'a','c','b');
    return 0;
}
