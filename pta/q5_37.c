#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTMAX 10000
#define NAMEMAX 8

typedef struct student *Student;
struct student {
    int Id;
    char Name[NAMEMAX];
    int Score;
};

struct student *students[STUDENTMAX];

// a大，返回true
int Comp(Student a, Student b)
{
    return a->Id > b->Id;
}

void swap(Student *a, Student *b)
{
    Student t;
    t = *a;
    *a = *b;
    *b = t;
}

Student Median3(Student students[], int Left, int Right)
{
    // 最后的顺序： left <= center <= right
    int Center = (Left + Right) / 2;
    if (Comp(students[Left], students[Center]))
        swap(&students[Center], &students[Left]);
    if (Comp(students[Left], students[Right]))
        swap(&students[Right], &students[Left]);
    if (Comp(students[Center], students[Right]))
        swap(&students[Right], &students[Center]);

    swap(&students[Center], &students[Right - 1]);
    return students[Right - 1];
}

void QuickSort(Student students[], int Left, int Right)
{
    if (Left == Right) return;
    Student Pivot = Median3(students, Left, Right);
    int i = Left + 1, j = Right - 2;
    while (i <= j)
    {
        // 找到该交换的元素
        while (Comp(Pivot, students[i++]));
        while (Comp(students[j--], Pivot));
        swap(&students[i], &students[j]);
    }

    swap(&students[i], &students[Right - 1]);
    QuickSort(students, Left, i - 1);
    QuickSort(students, i + 1, Right);
}

int main()
{
    int N, t, i;
    scanf("%d %d", &N, &t);

    for (i = 0; i < N; i++)
    {
        students[i] = malloc(sizeof(Student));
        scanf("%d %s %d", &students[i]->Id, students[i]->Name, &students[i]->Score);
    }

    QuickSort(students, 0, N - 1);

    for (i = 0; i < N; i++)
        printf("%06d %s %d\n", students[i]->Id, students[i]->Name, students[i]->Score);

    return 0;
}
