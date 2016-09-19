#include <stdlib.h>
#include <stdio.h>

#define MAX 50
int main()
{
    int N, i, a;
    int Ages[MAX];

    for (i = 0; i < MAX; i++) Ages[i] = 0;

    scanf("%d", &N);
    while (N--) {
        scanf("%d", &a);
        Ages[a]++;
    }

    for (i = 0; i < MAX; i++)
        if (Ages[i] > 0)
            printf("%d:%d\n", i, Ages[i]);
    return 0;
}
