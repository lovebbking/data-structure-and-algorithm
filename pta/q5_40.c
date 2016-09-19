#include <stdio.h>
#include <stdlib.h>

#define COUNTRYMAX 224

typedef struct country *Country;
typedef struct country {
    int Gold;
    int Medal;
    int Population;
} country;

int getGoldRanking(country countries[], int i, int N)
{
    int tmp = countries[i].Gold;
    int R = 1;
    for (int j = 0; j < N; j++)
        if (countries[j].Gold > tmp) R++;
    return R;
}

int getMedalRanking(country countries[], int i, int N)
{
    int tmp = countries[i].Medal;
    int R = 1;
    for (int j = 0; j < N; j++)
        if (countries[j].Medal > tmp) R++;
    return R;
}

int getAverageGoldRanking(country countries[], int i, int N)
{
    double tmp = 1.0 * countries[i].Gold / countries[i].Population;
    int R = 1;
    for (int j = 0; j < N; j++)
        if (1.0 * countries[j].Gold / countries[j].Population > tmp) R++;
    return R;
}

int getAverageMedalRanking(country countries[], int i, int N)
{
    double tmp = 1.0 * countries[i].Medal / countries[i].Population;
    int R = 1;
    for (int j = 0; j < N; j++)
        if (1.0 * countries[j].Medal / countries[j].Population > tmp) R++;
    return R;
}

void printMin(int G, int M, int AG, int AM)
{
    int min = 225, j;
    if (G < min)
    {
        min = G;
        j = 1;
    }
    if (M < min)
    {
        min = M;
        j = 2;
    }
    if (AG < min)
    {
        min = AG;
        j = 3;
    }
    if (AM < min)
    {
        min = AM;
        j = 4;
    }
    printf("%d:%d", min, j);
}

int main()
{
    int N, C, i;
    scanf("%d %d", &N, &C);
    country countries[COUNTRYMAX];

    for (i = 0; i < N; i++)
    {
        countries[i] = *(Country)malloc(sizeof(struct country));
        scanf("%d %d %d", &countries[i].Gold, &countries[i].Medal, &countries[i].Population);
    }


    while (C--)
    {
        scanf("%d", &i);
        int GoldRanking = getGoldRanking(countries, i, N);
        int MedalRanking = getMedalRanking(countries, i, N);
        int AverageGoldRanking = getAverageGoldRanking(countries, i, N);
        int AverageMedalRanking = getAverageMedalRanking(countries, i, N);

        printMin(GoldRanking, MedalRanking, AverageGoldRanking, AverageMedalRanking);
        if (C) printf(" ");
    }
    return 0;
}
