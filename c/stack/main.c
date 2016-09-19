#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main ()
{
    Stack S = CreateStack(5);


    assert(StackEmpty(S, 1) == true);
    assert(StackEmpty(S, 2) == true);

    assert(S->Top1 == -1);
    Push(S, 3, 1);
    assert(S->Top1 == 0);
    Push(S, 5, 1);
    Push(S, 1, 1);
    Push(S, 2, 1);
    Push(S, 7, 1);
    assert(S->Top1 == 4);
    assert(StackFull(S, 1) == true);
    assert(Push(S, 8, 1) == false);
    PrintStack(S, 1);
    printf("\n");
    // assert(Pop(S, 2) == ERROR);
    // PrintStack(S, 2);
    // Push(S, 9, 2);
    // PrintStack(S, 2);

    printf("now pop from s1 :\n");
    printf("%d ", Pop(S, 1));
    printf("%d ", Pop(S, 1));
    printf("%d ", Pop(S, 1));
    printf("%d ", Pop(S, 1));
    printf("%d ", Pop(S, 1));

    // test pop
    // printf("pop top1 is: %d\n", Pop(S, 1));
    // assert(Pop(S, 1) == 7);

    printf("pass!");
    return 0;
}
