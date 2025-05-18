#include <stdio.h>

int main()
{
    int n, max, nextmax, num, i;

    printf("숫자 개수 입력 : ");
    scanf("%d", &n);
    printf("%d개의 숫자 입력 : ", n);
    scanf("%d %d", &max, &num);
    if (max < num)
    {
        nextmax = max;
        max = num;
    }
    else
        nextmax = num;

    for (i = 0; i < n - 2; i++)
    {
        scanf("%d", &num);
        if (max < num)
        {
            nextmax = max;
            max = num;
        }
        else if (nextmax < num)
            nextmax = num;
    }

    printf("max = [%d]\nnextmax = [%d]", max, nextmax);

    return 0;
}