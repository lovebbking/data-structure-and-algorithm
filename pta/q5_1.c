// 5-1 最大子列和问题   (20分)
//
// 数据1：与样例等价，测试基本正确性；
// 数据2：102个随机整数；
// 数据3：103个随机整数；
// 数据4：104个随机整数；
// 数据5：105个随机整数；
// 输入格式:
//
// 输入第1行给出正整数KK (\le 100000≤100000)；第2行给出KK个整数，其间以空格分隔。
//
// 输出格式:
//
// 在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。
//
// 输入样例:
//
// 6
// -2 11 -4 13 -5 -2
// 输出样例:
//
// 20

#include <stdio.h>
#include <stdlib.h>

int maxSubSum(int a[], int l)
{
    int max = 0;
    int sum = 0;
    // int *p;
    int i;
    for (i = 0; i < l; i++) {
      sum += a[i];
      if (sum > max) {
        max = sum;
      }
      if (sum < 0) {
        sum = 0;
      }
    }
    return max;
}

int main()
{
    int l, i, k, subSum;
    scanf("%d", &l);

    int arr[l];

    for(i = 0; i < l; i++)
    {
        scanf("%d", &k);
        arr[i] = k;
    }

    subSum = maxSubSum(arr, l);
    printf("%d\n", subSum);
    // printf("%d\n", arr[0]);
    // printf("%d\n", arr[1]);
    // printf("%d\n", arr[2]);
    // printf("%d\n", arr[3]);
    // printf("%d\n", arr[4]);
    // printf("%d\n", arr[5]);
    return 0;
}
