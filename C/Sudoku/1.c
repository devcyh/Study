/*
#include <stdio.h>

void P(int* t_nums, int size, int index);
void swap(int* a, int* b);
void print_arr(int* arr, int size);

//int count = 0;

int main()
{
	int nums[4] = { 1,2,3,4 };

	P(nums, sizeof(nums) / sizeof(int), 0);

	//printf("\n%d개", count);

	return 0;
}

void P(int* t_nums, int size, int index)
{
	if (index == size)
	{
		//print_arr(t_nums, size);
		//count++;
		return;
	}

	int i;

	for (i = index; i < size; i++)
	{
		swap(t_nums + index, t_nums + i);

		P(t_nums, size, index + 1);

		swap(t_nums + i, t_nums + index);
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