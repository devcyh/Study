#include <stdio.h>

int findsum(int);

int main()
{
  int num, x;

  printf("\nEnter a number: ");

  scanf("%d", &num);

  x = findsum(num);

  printf("Sum of the digits of %d is: %d", num, x);

  return 0;
}

int findsum(int num)
{
  int q, r, sum;
  sum = 0;

  q = num / 10;
  r = num % 10;
  if (q != 0)
    sum = findsum(q);

  return sum + r;
}