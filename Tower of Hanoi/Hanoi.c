#include <stdio.h>
#define total 5

void move(int start, int des, int mid, int num);
void nprintf();

int tower[3][total] = {
    0,
};
int top[3] = {total - 1, -1, -1};
int count;

int main()
{
    int i;
    for (i = 0; i < total; i++)
        tower[0][i] = total - i;
    nprintf();
    count = 0;
    move(0, 2, 1, total);
    nprintf();
    printf("원반을 움직인 횟수 = %d", count);
    return 0;
}

void move(int start, int des, int mid, int num)
{
    if (num == 1)
    {
        tower[des][++top[des]] = tower[start][top[start]];
        tower[start][top[start]--] = 0;
    }
    else
    {
        move(start, mid, des, num - 1);
        nprintf();
        move(start, des, mid, 1);
        nprintf();
        move(mid, des, start, num - 1);
    }
}

void nprintf()
{
    int i, j;
    count++;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < total; j++)
            printf("%d ", tower[i][j]);
        printf("\n");
    }
    printf("\n");
}