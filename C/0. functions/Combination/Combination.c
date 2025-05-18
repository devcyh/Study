#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void combi(int n, int r, int st);

int vis[5];

int main(void)
{
	int n, r;

	printf("n, r 입력 : ");
	scanf("%d %d", &n, &r);

	combi(n, r, 0);

	return 0;
}

void combi(int n, int r, int st)
{
	if (r == 0)
	{
		for (int i = 0; i < n; i++)
		{
			printf("%d ", vis[i]);
		}
		printf("\n");
	}
	else
	{
		for (int i = st; i < n; i++)
		{
			if (vis[i] == 0)
			{
				vis[i] = 1;
				combi(n, r - 1, i);
				vis[i] = 0;
			}
		}
	}
}