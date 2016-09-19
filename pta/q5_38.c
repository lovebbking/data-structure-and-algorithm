// 2015年胡润研究院的调查显示，截至2014年9月，个人资产在600万元以上高净值人群达290万人。假设给出N个人的个人资产值，请快速找出资产排前M位的大富翁。
//
// 输入格式:
//
// 输入首先给出两个正整数NN（\le 10^6≤10
// ​6
// ​​ ）和MM（\le 10≤10），其中NN为总人数，MM为需要找出的大富翁数；接下来一行给出NN个人的个人资产值，以百万元为单位，为不超过长整型范围的整数。数字间以空格分隔。
//
// 输出格式:
//
// 在一行内按非递增顺序输出资产排前MM位的大富翁的个人资产值。数字间以空格分隔，但结尾不得有多余空格。
//
// 输入样例:
//
// 8 3
// 8 12 7 3 20 9 5 18
// 输出样例:
//
// 20 18 12

#define MAX 100000
#define FINDMAX 10

#include <stdlib.h>
#include <stdio.h>


int main()
{
    int N, c, i, j, k;
    int nums[MAX];
    int marks[FINDMAX];
    scanf("%d %d", &N, &c);
    for (i = 0; i < N; i++)
        scanf("%d", &nums[i]);
    for (i = 0; i < c; i++)
    {
        marks[i] = -1;
        maxs[i] = -1;
    }

    int max, markFlag, count = 0;

    while (1)
    {
        max = -1;
        for (i = 0; i < N; i++)
        {

            markFlag = 0;
            for (j = 0; j < count; j++)
                if (i == marks[j])
                {
                    markFlag = 1;
                    break;
                }

            if (markFlag) continue;

            if (nums[i] > max)
            {
                max = nums[i];
                marks[count] = i;
            }
        }
        if (++count == c)
        {
            printf("%d", max);
            return 0;
        }
        else
            printf("%d ", max);

    }
    return 0;
}
