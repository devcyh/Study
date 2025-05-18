#include <stdio.h>
#include <stdlib.h>

int getnum();
void getq(int* query);
void ADD(int* a, int l, int r, int x);
void DIV(int* a, int l, int r, int x);
void MAX(int* a, int l, int r);

int main()
{
	int N = getnum();
	int Q = getnum();

	int i;

	int* pa = (int*)malloc(N * sizeof(int));
	for (i = 0; i < N; i++)
	{
		pa[i] = getnum();
	}

	int query[4];

	for (i = 0; i < Q; i++)
	{
		getq(query);
		switch (query[0])
		{
		case 0:
			ADD(pa, query[1], query[2], query[3]);
			break;
		case 1:
			DIV(pa, query[1], query[2], query[3]);
			break;
		case 2:
			MAX(pa, query[1], query[2]);
			break;
		}
	}

	free(pa);

	printf("\n");

	return 0;
}

int getnum()
{
	char num_str[11];
	char temp;
	int i = 0;

	temp = getchar();
	while (temp == ' ')
	{
		temp = getchar();
	}

	while (temp != ' ' && temp != '\n')
	{
		num_str[i] = temp;
		i++;
		temp = getchar();
	}
	num_str[i] = '\0';

	return atoi(num_str);
}

void getq(int* query)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		query[i] = getnum();
	}
}

void ADD(int* a, int l, int r, int x)
{
	int i;
	for (i = l; i <= r; i++)
	{
		a[i] = a[i] + x;
	}
}

void DIV(int* a, int l, int r, int x)
{
	int i;
	for (i = l; i <= r; i++)
	{
		a[i] = (a[i] / x);
	}
}

void MAX(int* a, int l, int r)
{
	int i;
	int max = a[l];
	for (i = l + 1; i <= r; i++)
	{
		if (a[i] > max) max = a[i];
	}
	printf("\n%d", max);
}