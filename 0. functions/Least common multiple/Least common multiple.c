#include <stdio.h>

int find_max(int* arr, int size);
void swap(int* a, int* b);
int LCM(int* arr, int size);

int main()
{
	int arr[4] = { 241, 123, 948, 498 };

	swap(&arr[0], &arr[find_max(arr, sizeof(arr) / sizeof(int))]); // 가장 큰 수를 arr[0]로 이동.

	printf("최소공배수 : %d\n", LCM(arr, sizeof(arr) / sizeof(int)));

	return 0;
}

int find_max(int* arr, int size)
{
	int i;
	int index = 0;
	for (i = 1; i < size; i++)
	{
		switch (arr[i] > arr[index])
		{
		case 0:
			break;
		case 1:
			index = i;
			break;
		}
	}
	return index;
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int LCM(int* arr, int size)
{
	int i, j, sum;

	i = 1;
	while (1)
	{
		sum = 0;
		for (j = 1; j < size; j++)
		{
			sum = sum + ((i * arr[0]) % arr[j]); // arr[0]는 가장 큰 수. 가장 큰 수의 배수를 나머지 작은 수들로 나누었을때의 나머지가 0인지 확인.
			if (sum != 0) break;
		}
		if (sum == 0) break; // 나머지가 모두 0이면 그때의 가장 큰 수의 배수가 최소공배수.
		i++;
	}
	return i * arr[0];
}