// 实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。
//
// 输入格式:
//
// 输入首先给出一个正整数NN（\le 10^5≤10
// ​5
// ​​ ），随后给出NN行指令。每行指令的格式为：“命令符（空格）QQ号码（空格）密码”。其中命令符为“N”（代表New）时表示要新申请一个QQ号，后面是新帐户的号码和密码；命令符为“L”（代表Login）时表示是老帐户登陆，后面是登陆信息。QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。密码为不小于6位、不超过16位、且不包含空格的字符串。
//
// 输出格式:
//
// 针对每条指令，给出相应的信息：
//
// 1）若新申请帐户成功，则输出“New: OK”；
// 2）若新申请的号码已经存在，则输出“ERROR: Exist”；
// 3）若老帐户登陆成功，则输出“Login: OK”；
// 4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；
// 5）若老帐户密码错误，则输出“ERROR: Wrong PW”。
//
// 输入样例:
//
// 5
// L 1234567890 myQQ@qq.com
// N 1234567890 myQQ@qq.com
// N 1234567890 myQQ@qq.com
// L 1234567890 myQQ@qq
// L 1234567890 myQQ@qq.com
// 输出样例:
//
// ERROR: Not Exist
// New: OK
// ERROR: Exist
// ERROR: Wrong PW
// Login: OK

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PWMAX 17
#define AcLinkSize 10001

typedef struct Act *Account;
typedef struct Act *AccountList;

struct Act {
    long long  ID;
    char       PW[PWMAX];
    Account    Next;
};

AccountList createAccountList(Account A, long long ID, char *PW)
{
    Account newA = NULL;
    // AccountList 链表从小到大排列.
    // 所以当要插入的ID小于当前node的ID，就可以插入
    if (!A || A->ID > ID)
    {
        newA = malloc(sizeof(struct Act));
        newA->ID = ID;
        strcpy(newA->PW, PW);
        newA->Next = A;
        printf("New: OK\n");
        return newA;
    }

    else if (A->ID == ID)
        printf("ERROR: Exist\n");
    else
        A->Next = createAccountList(A->Next, ID, PW);
    return A;
}
void New(Account *AcLinks, long long ID, char *PW)
{
    AccountList A = AcLinks[ID % AcLinkSize];
    AcLinks[ID % AcLinkSize] = createAccountList(A, ID, PW);
}

void Login(Account *AcLinks, long long ID, char *PW)
{
    AccountList A = AcLinks[ID % AcLinkSize];
    for (; A && A->ID >= ID; A = A->Next)
        if(A->ID == ID)
        {
            if(strcmp(A->PW, PW))
            {
                printf("ERROR: Wrong PW\n");
                return;
            }
            else{
                printf("Login: OK\n");
                return;
            }
        }
    printf("ERROR: Not Exist\n");
}

int main()
{
    int N;
    char A;
    long long ID;
    char PW[30];
    Account *AcLinks = (Account *)malloc(sizeof(Account) * AcLinkSize);
    for(int i = 0; i < AcLinkSize; i++)
        AcLinks[i]=NULL;

    scanf("%d",&N);
    getchar();
    while (N--)
    {
        scanf(" %c%lld %s", &A, &ID, PW);
        if (A == 'N')      New(AcLinks, ID, PW);
        else if (A == 'L') Login(AcLinks, ID, PW);
    }
    return 0;
}
