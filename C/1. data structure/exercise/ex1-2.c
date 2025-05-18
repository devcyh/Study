#include <stdio.h>

int lcm(int, int);

int main()
{
    int a, b, l;

    printf("Enter any two positive integers ");

    scanf("%d%d", &a, &b);

    if (a > b)
        l = lcm(a, b);

    else
        l = lcm(b, a);

    printf("LCM of two integers is %d", l);

    return 0;
}

int lcm(int a, int b)
{
    static int lcmnum = 0;
    lcmnum = lcmnum + a;
    if (lcmnum % a == 0 && lcmnum % b == 0)
        return lcmnum;
    else
        lcm(a, b);
}