#include <stdio.h>

int gcd(int a, int b);

int main()
{
	int arr[4] = { 12, 18, 72, 345 };
	int gcd_num;
	int i;

	gcd_num = arr[0];
	for (i = 1; i < sizeof(arr) / sizeof(int); i++)
	{
		gcd_num = gcd(arr[i], gcd_num);
	}

	printf("%d\n", gcd_num);

	return 0;
}

int gcd(int a, int b)
{
	int c;
	while (b) // 알아서 a에 큰수, b에 작은수 들어감! swap 할 필요가 없네!
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}