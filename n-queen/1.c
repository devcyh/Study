/*#include <stdio.h>

#define arr_size 5

int Q1(int(*arr)[arr_size]);
int Q2(int(*arr)[arr_size]);
int Q3(int(*arr)[arr_size]);

int main()
{
	int i, j, k, l, m;
	int arr[arr_size][arr_size] = { 0, };
	arr[0][0] = 1;
	arr[1][1] = 1;
	arr[2][2] = 1;
	arr[3][3] = 1;
	arr[4][4] = 1;

	for (i = 0; i < arr_size; i++) //배열 값 확인
	{
		for (j = 0; j < arr_size; j++)
		{
			printf("%2d", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	i = Q1(arr);
	printf("\n\n");
	j = Q2(arr);
	printf("\n\n");
	k = Q3(arr);
	printf("\n\n");

	printf("result = [%d]", i && j && k);

	return 0;
}

int Q1(int(*arr)[arr_size])
{
	int i, j;
	int bool;
	int i_bool = 1;
	int j_bool;

	for (i = 0; i < arr_size; i++)
	{
		j_bool = 0;
		for (j = 0; j < arr_size; j++)
		{
			bool = arr[i][j];
			j_bool = j_bool || bool;
			printf("arr[%d][%d] = [%d]\n", i, j, arr[i][j]);
		}
		i_bool = i_bool && j_bool;
		printf("[j_bool] = [%d]\n\n", j_bool);
	}
	printf("[i_bool] = [%d]\n", i_bool);

	return i_bool;
}

int Q2(int(*arr)[arr_size])
{
	int i, j, k;
	int bool;
	int tot_bool = 1;

	printf("[i, j, k]\t[ !arr[i][j] || !arr[k][j] = bool ]\t[tot_bool]\n\n");
	for (i = 0; i < arr_size; i++)
	{
		for (j = 0; j < arr_size - 1; j++)
		{
			for (k = j + 1; k < arr_size; k++)
			{
				printf("[%d, %d, %d]", i + 1, j + 1, k + 1);
				bool = !arr[i][j] || !arr[k][j];
				tot_bool = tot_bool && bool;
				printf("\t[%d || %d = %d]\t[%d]\n", !arr[i][j], !arr[k][j], bool, tot_bool);
			}
		}
	}
	printf("\n%d", tot_bool);

	return tot_bool;
}

int Q3(int(*arr)[arr_size])
{
	int i, j, k;
	int bool;
	int tot_bool = 1;

	printf("[i, j, k]\t[ !arr[i][j] || !arr[k][j] = bool ]\t[tot_bool]\n\n");
	for (j = 0; j < arr_size; j++)
	{
		for (i = 0; i < arr_size - 1; i++)
		{
			for (k = i + 1; k < arr_size; k++)
			{
				printf("[%d, %d, %d]", i + 1, j + 1, k + 1);
				bool = !arr[i][j] || !arr[k][j];
				tot_bool = tot_bool && bool;
				printf("\t[%d || %d = %d]\t[%d]\n", !arr[i][j], !arr[k][j], bool, tot_bool);
			}
		}
	}
	printf("\n%d", tot_bool);

	return tot_bool;
}*/

/*int Q2(int(*arr)[arr_size])
{
	int i, j, k;
	int bool;
	int tot_bool = 1;

	printf("[i, j, k]\t[ !arr[i][j] || !arr[k][j] = bool ]\t[tot_bool]\n\n");
	for (i = 0; i < arr_size; i++)
	{
		for (j = 0; j < arr_size - 1; j++)
		{
			for (k = j + 1; k < arr_size; k++)
			{
				printf("[%d, %d, %d]", i + 1, j + 1, k + 1);
				bool = !arr[i][j] || !arr[k][j];
				tot_bool = tot_bool && bool;
				printf("\t[%d || %d = %d]\t[%d]\n", !arr[i][j], !arr[k][j], bool, tot_bool);
			}
		}
	}
	printf("\n%d", tot_bool);

	return tot_bool;
}

int Q3(int(*arr)[arr_size])
{
	int i, j, k;
	int bool;
	int tot_bool = 1;

	printf("[i, j, k]\t[ !arr[i][j] || !arr[k][j] = bool ]\t[tot_bool]\n\n");
	for (j = 0; j < arr_size; j++)
	{
		for (i = 0; i < arr_size - 1; i++)
		{
			for (k = i + 1; k < arr_size; k++)
			{
				printf("[%d, %d, %d]", i + 1, j + 1, k + 1);
				bool = !arr[i][j] || !arr[k][j];
				tot_bool = tot_bool && bool;
				printf("\t[%d || %d = %d]\t[%d]\n", !arr[i][j], !arr[k][j], bool, tot_bool);
			}
		}
	}
	printf("\n%d", tot_bool);

	return tot_bool;
}*/