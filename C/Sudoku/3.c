/*
#include <stdio.h>
#include <stdlib.h>

void P(int** p_sdk_part, int** p_nums, int nums_index, int(*sudoku)[9], int sdk_index);
void sdk_parsing(int* sdk_part, int(*sudoku)[9], int sdk_index);
void merge(int* nums, int* sdk_part);
void reverse(int* arr_temp, int* sdk_part);
void copy_nums(int* nums, int* sdk_part);
void swap(int* a, int* b);
void copy_sdk(int(*sudoku)[9], int* nums, int sdk_index);
void print_sdk(int(*sudoku)[9]);

int count = 0;

int main()
{
	int sudoku[9][9] =
	{
		0,3,5,0,6,0,0,7,0,
		7,0,2,1,0,5,0,0,9,
		0,6,0,2,0,8,0,3,5,
		0,2,1,0,0,0,8,0,7,
		8,0,0,9,1,3,0,0,6,
		0,0,6,0,2,0,4,0,3,
		9,0,7,6,5,0,0,8,0,
		6,0,0,7,0,1,9,0,2,
		0,5,8,0,0,4,7,6,0
	};

	int* p_sdk_part[9];
	int* p_nums[9];
	int i;
	for (i = 0; i < 9; i++)
	{
		p_sdk_part[i] = (int*)malloc(9 * sizeof(int));
		p_nums[i] = (int*)malloc(9 * sizeof(int));
		sdk_parsing(p_sdk_part[i], sudoku, i);
		merge(p_nums[i], p_sdk_part[i]);
	}

	P(p_sdk_part, p_nums, 0, sudoku, 0);

	for (i = 0; i < 9; i++)
	{
		free(p_sdk_part[i]);
		free(p_nums[i]);
	}

	printf("\n%d개", count);

	return 0;
}

void P(int** p_sdk_part, int** p_nums, int nums_index, int(*sudoku)[9], int sdk_index)
{
	if (sdk_index == 9)
	{
		print_sdk(sudoku);
		count++;
		return;
	}

	if (nums_index == 9)
	{
		copy_sdk(sudoku, p_nums[sdk_index], sdk_index);

		P(p_sdk_part, p_nums, 0, sudoku, sdk_index + 1);

		return;
	}

	if (p_sdk_part[sdk_index][nums_index] != 0)
	{
		P(p_sdk_part, p_nums, nums_index + 1, sudoku, sdk_index);
		return;
	}

	int i;

	for (i = nums_index; i < 9; i++)
	{
		if (p_sdk_part[sdk_index][i] != 0) continue;

		swap(p_nums[sdk_index] + nums_index, p_nums[sdk_index] + i);

		P(p_sdk_part, p_nums, nums_index + 1, sudoku, sdk_index);

		swap(p_nums[sdk_index] + i, p_nums[sdk_index] + nums_index);
	}
}

void sdk_parsing(int* sdk_part, int(*sudoku)[9], int sdk_index)
{
	int i, j;
	int index = 0;
	int x = (sdk_index / 3) * 3;
	int y = (sdk_index % 3) * 3;

	for (i = x; i < x + 3; i++)
	{
		for (j = y; j < y + 3; j++)
		{
			sdk_part[index] = sudoku[i][j];
			index++;
		}
	}
}

void merge(int* nums, int* sdk_part)
{
	int arr_temp[9] = { 0, };
	int i;
	int j = 0;

	reverse(arr_temp, sdk_part);
	copy_nums(nums, sdk_part);

	for (i = 0; i < 9; i++)
	{
		if (nums[i] == 0)
		{
			nums[i] = arr_temp[j];
			j++;
		}
	}
}

void reverse(int* arr_temp, int* sdk_part)
{
	int i;
	int j = 0;

	for (i = 0; i < 9; i++)
	{
		if (sdk_part[i] != 0)
		{
			arr_temp[sdk_part[i] - 1] = sdk_part[i];
		}
	}

	for (i = 0; i < 9; i++)
	{
		if (arr_temp[i] == 0)
		{
			arr_temp[j] = i + 1;
			j++;
		}
	}

	for (i = j; i < 9; i++)
	{
		arr_temp[i] = 0;
	}
}

void copy_nums(int* nums, int* sdk_part)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		nums[i] = sdk_part[i];
	}
}

void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void copy_sdk(int(*sudoku)[9], int* nums, int sdk_index)
{
	int i, j;
	int index = 0;
	int x = (sdk_index / 3) * 3;
	int y = (sdk_index % 3) * 3;

	for (i = x; i < x + 3; i++)
	{
		for (j = y; j < y + 3; j++)
		{
			sudoku[i][j] = nums[index];
			index++;
		}
	}
}

void print_sdk(int(*sudoku)[9])
{
	int i, j;

	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			printf("%d ", sudoku[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
*/