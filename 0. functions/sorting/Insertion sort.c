#include <stdio.h>
#define sizeofarr 5

void insertion_sort(int *arr, int arr_size);

int main()
{
	int i;
	int arr[sizeofarr];

	printf("%d개의 숫자를 입력하세요 : ", sizeofarr);

	for (i = 0; i < sizeofarr; i++)
		scanf(" %d", &arr[i]);

	insertion_sort(arr, sizeofarr);

	printf("정렬 결과 : ");
	for (i = 0; i < sizeofarr; i++)
		printf("%d ", arr[i]);

	return 0;
}

void insertion_sort(int *arr, int size)
{
	int i, j;
	int key;

	for (i = 1; i < size; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}