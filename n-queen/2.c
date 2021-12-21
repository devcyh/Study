#include <stdio.h>

#define arr_size 5

void func1(int(*arr)[arr_size], int row_index);
void erase_row(int(*arr)[arr_size], int row_index);
void print_arr(int(*arr)[arr_size]);

int count = 0;

int main()
{
	int j;
	int arr[arr_size][arr_size] = { 0, };

	for (j = 0; j < arr_size; j++)
	{
		arr[0][j] = 1;
		func1(arr, 1);
		erase_row(arr, 0);
	}
	printf("%d\n", count);

	return 0;
}

void func1(int(*arr)[arr_size], int row_index)
{
	if (row_index == arr_size)
	{
		print_arr(arr);
		printf("\n\n");
		count++;
		return;
	}

	int it, jt, j;
	int bool_col;

	for (j = 0; j < arr_size; j++)
	{
		bool_col = 0;
		for (it = 0; it < row_index; it++) // 위쪽 column
		{
			bool_col = bool_col || arr[it][j];
			if (bool_col == 1) break;
		}

		it = row_index - 1; // 북동쪽 대각선
		jt = j - 1;
		while (it >= 0 && jt >= 0)
		{
			bool_col = bool_col || arr[it][jt];
			if (bool_col == 1) break;
			it--;
			jt--;
		}

		it = row_index - 1; // 북서쪽 대각선
		jt = j + 1;
		while (it >= 0 && jt < arr_size)
		{
			bool_col = bool_col || arr[it][jt];
			if (bool_col == 1) break;
			it--;
			jt++;
		}

		if (bool_col == 0)
		{
			arr[row_index][j] = 1;
			func1(arr, row_index + 1);
			erase_row(arr, row_index);
		}
	}
}

void erase_row(int(*arr)[arr_size], int row_index)
{
	int j;

	for (j = 0; j < arr_size; j++)
	{
		arr[row_index][j] = 0;
	}
}

void print_arr(int (*arr)[arr_size])
{
	int i, j;
	for (i = 0; i < arr_size; i++)
	{
		for (j = 0; j < arr_size; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}