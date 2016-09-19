#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTMAX 30000
#define ROOMMAX 100

typedef struct student *Student;
struct student {
    char Id[14];
    int Score;
    int Room; // 考点
    int RoomRanking; // 考点内排名
};

struct student students[STUDENTMAX];
int roomStarts[ROOMMAX];
int roomEnds[ROOMMAX];

int compare(Student a, Student b)
{
    if(a->Score != b->Score)
        return b->Score >= a->Score;
    else
        return !strcmp(a->Id, b->Id);
}

void MergeSort(int roomCount)
{
    int lastRanking, lastScore = -1, i, index, room, r, count = 1;
    Student tmp;
    while (1)
    {
        // 找到最大的
        tmp = NULL;
        for (i = 0; i < roomCount; i++)
        {
            index = roomStarts[i];
            if (index > roomEnds[i]) continue;
            if (tmp == NULL || compare(tmp, &students[index]))
            {
                tmp = &students[index];
                room = i;
            }
        }

        if (tmp == NULL) return;

        if (tmp->Score == lastScore)
            printf("%s %d %d %d\n", tmp->Id, lastRanking, tmp->Room, tmp->RoomRanking);
        else
        {
            printf("%s %d %d %d\n", tmp->Id, count, tmp->Room, tmp->RoomRanking);
            lastRanking = count;
        }

        lastScore = tmp->Score;
        roomStarts[room]++;
        count++;

    }
}


int main()
{
    int N, i, n, room, count = 0, start;
    scanf("%d", &N);

    for (room = 0; room < N; room++)
    {
        scanf("%d", &n);
        start = count;

        while (n--)
        {
            Student s = (Student)malloc(sizeof(struct student));
            scanf("%s %d", s->Id, &s->Score);
            s->Room = room + 1;
            students[count++] = *s;
        }

        roomStarts[room] = start;
        roomEnds[room] = count - 1;

        // 输入完一个考点后，排序当前考点
        qsort(&students[start], count - start, sizeof(struct student), compare);

        // 赋值考点排名
        students[start].RoomRanking = 1;
        for (i = start + 1; i < count; i++)
        {
            if (students[i].Score == students[i - 1].Score)
                students[i].RoomRanking = students[i - 1].RoomRanking;
            else
                students[i].RoomRanking = i - start + 1;
        }
    }
    printf("%d\n", count);
    MergeSort(room);
    return 0;
}
