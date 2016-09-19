#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "linked_list.h"

int main()
{
    // 一个 [-2, -1, 8, 4, 3, 5, 1]的链表
    Node n1 = {1, NULL};
    Node n2 = {5, &n1};
    Node n3 = {3, &n2};
    Node n4 = {4, &n3};
    Node n5 = {8, &n4};
    Node n6 = {-1, &n5};
    Node n7 = {-2, &n6};
    List list = &n7;
    Position p;

    // test is empty
    assert(isEmpty(list) == FALSE);

    // test length
    assert(length(list) == 7);
    assert(length(&n1) == 1);
    assert(length(&n4) == 4);

    // test findIndex
    assert(findIndex(list, 0) == ERROR);
    assert(findIndex(list, 3) == 8);
    assert(findIndex(list, 2) == -1);
    assert(findIndex(list, 8) == ERROR);

    // test find
    assert(find(list, 4)->Data == 4);
    assert(find(list, -1)->Data == -1);
    assert(find(list, 345) == POINT_ERROR);

    // test insert
    list = insert(list, 6, find(list, -2));
    assert(findIndex(list, 1) == 6);

    // cannot insert an unvalid position
    p = (Position)malloc(sizeof(struct Node));
    assert(insert(list, 6, p) == POINT_ERROR);

    // insert to last
    list = insert(list, 10, NULL);
    assert(find(list, 10)->Data == 10);

    // test delete
    // success
    list = delete(list, find(list, 6));
    assert(find(list, 6) == POINT_ERROR);
    // fail
    assert(delete(list, p) == POINT_ERROR);


    printf("pass\n");
}
