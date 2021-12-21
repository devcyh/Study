/*
#include <stdio.h>

void P(int* sdk_part, int* t_nums, int index);
void sdk_parsing(int* sdk_part, int(*sudoku)[9], int part_index);
void merge(int* nums, int* sdk_part);
void reverse(int* arr_temp, int* sdk_part);
void copy(int* nums, int* sdk_part);
void swap(int* a, int* b);
void print_arr(int* arr, int size);

int count = 0;

int main()
{
	int sudoku[9][9] = { 8,0,0,0,0,0,0,0,0,6,4,0,0,0,0,0,0,0,3,0,9, };
	int nums[9] = { 0, };

	int sdk_part[9] = { 0, };
	sdk_parsing(sdk_part, sudoku, 0);
	merge(nums, sdk_part);

	P(sdk_part, nums, 0);

	printf("\n%d개", count);

	return 0;
}

void P(int* sdk_part, int* t_nums, int index)
{
	if (index == 9)
	{
		print_arr(t_nums, 9);
		count++;
		return;
	}

	if (sdk_part[index] != 0)
	{
		P(sdk_part, t_nums, index + 1);
		return;
	}

	int i;

	for (i = index; i < 9; i++)
	{
		if (sdk_part[i] != 0) continue;

		swap(t_nums + index, t_nums + i);

		P(sdk_part, t_nums, index + 1);

		swap(t_nums + i, t_nums + index);
	}
}

void sdk_parsing(int* sdk_part, int(*sudoku)[9], int part_index)
{
	int i, j;
	int index = 0;
	int x = (part_index / 3) * 3;
	int y = (part_index % 3) * 3;

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
	copy(nums, sdk_part);

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

void copy(int* nums, int* sdk_part)
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

void print_arr(int* arr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
*/