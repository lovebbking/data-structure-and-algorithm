// 算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。前缀表达式指二元运算符位于两个运算数之前，例如2+3*(7-4)+8/4的前缀表达式是：+ + 2 * 3 - 7 4 / 8 4。请设计程序计算前缀表达式的结果值。
//
// 输入格式:
//
// 输入在一行内给出不超过30个字符的前缀表达式，只包含+、-、*、\以及运算数，不同对象（运算数、运算符号）之间以空格分隔。
//
// 输出格式:
//
// 输出前缀表达式的运算结果，保留小数点后1位，或错误信息ERROR。
//
// 输入样例:
//
// + + 2 * 3 - 7 4 / 8 4
// 输出样例:
//
// 13.0

#include <stdlib.h>
#include <stdio.h>

#define MAX 40

int sp = 0;
double Stack[MAX];

void Push(double f)
{
    Stack[sp++] = f;
}

double Pop()
{
    return Stack[--sp];
}

int Calculate(char Ops[], int last)
{
    char op;
    double tmp;
    int i;

    for(i = last - 1; i >= 0; i--)
    {
        op = Ops[i];
        if (op >= '0' && op <= '9')
        {
            tmp = (double)(op - '0');
            Push(tmp);
            continue;
        }
        else if (op == '+') tmp = Pop() + Pop();
        else if (op == '-') tmp = Pop() - Pop();
        else if (op == '*') tmp = Pop() * Pop();
        else if (op == '/') tmp = Pop() / Pop();

        Push(tmp);
    }
    return Pop();
}

// 遇见数字，进栈，遇见运算符，把栈顶前两个数运算，得到的结果存到栈顶下一个，然后把栈顶弹出
int main()
{
    char C;
    int i, last = 0;
    char Ops[MAX];

    // TODO: 不能处理超过一位数。
    while (scanf("%c", &C) != EOF && C != '\n')
    {
        if ( C == ' ')
            continue;
        Ops[last++] = C;
    }

    double result = Calculate(Ops, last);
    printf("%.1f", result);
    return 0;
}
