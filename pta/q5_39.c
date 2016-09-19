#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

void Swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int Median3(int A[], int Left, int Right)
{
    int Center = (Right + Left) / 2;
    if (A[Left] > A[Center]) Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right]) Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right]) Swap(&A[Center], &A[Right]);
    Swap(&A[Center], &A[Right - 1]);
    return A[Right - 1];
}

void QuickSort(int A[], int Left, int Right)
{
    if (Left >= Right) return;
    int Pivot = Median3(A, Left, Right);

    int i = Left, j = Right - 1, k;

    while (1)
    {
        while (A[++i] < Pivot);
        while (A[--j] > Pivot);
        if (i < j) Swap(&A[i], &A[j]);
        else break;
    }
    if (i < Right - 1) Swap(&A[i], &A[Right - 1]);

    QuickSort(A, Left, i - 1);
    QuickSort(A, i + 1, Right);
}

void initArray(int A[], int N)
{
    for (int i = 0; i < N; i++) scanf("%d", &A[i]);
    QuickSort(A, 0, N - 1);
}

int main()
{
    int ProductCount, CouponCount;
    int Products[MAX], Coupons[MAX];
    scanf("%d", &ProductCount);
    initArray(Products, ProductCount);
    scanf("%d", &CouponCount);
    initArray(Coupons, CouponCount);

    int sum = 0, i, j, left = 0, right = CouponCount - 1;

    for (i = 0; i < ProductCount; i++)
        if (Products[i] >= 0 || Coupons[left] >= 0)
            break;
        else
            sum += Products[i] * Coupons[left++];

    for (i = ProductCount - 1; i > 0; i--)
        if (Products[i] < 0 || Coupons[right] < 0)
            break;
        else
            sum += Products[i] * Coupons[right--];

    printf("%d", sum);

    return 0;
}
