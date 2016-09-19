#include <stdlib.h>
#include <stdio.h>

#define MAX 100000

void Sort(int Arr[], int Length)
{
    int i, j, tmp;
    for (i = 0; i < Length; i++)
        for (j = i + 1; j < Length; j++)
            if (Arr[i] > Arr[j])
            {
                tmp = Arr[i];
                Arr[i] = Arr[j];
                Arr[j] = tmp;
            }
}

int main() {
    int Arr[MAX] = {0};
    int N, Length, t, i = 0;

    scanf("%d ", &N);
    Length = N;

    while (N--) {
        scanf("%d", &t);
        Arr[i++] = t;
    }

    Sort(Arr, Length);
    for(i = 0; i < Length; i++)
    {
        if (i == Length - 1)
            printf("%d", Arr[i]);
        else
            printf("%d ", Arr[i]);
    }

    return 0;
}
