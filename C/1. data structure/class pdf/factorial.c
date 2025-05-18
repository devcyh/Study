#include <stdio.h>

int factorial(int n);

int main()
{
    int n;
    printf("값 입력 : ");
    scanf("%d", &n);
    printf("%d", factorial(n));
    return 0;
}

int factorial(int n)
{
    if (n <= 1)
        return n;
    return n * factorial(n - 1);
}