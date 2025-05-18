#include <stdio.h>
#define sizeofarr 5

void bubble_sort(int *arr, int size);
void swap(int *a, int *b);

int main()
{
    int i;
    int arr[sizeofarr];

    printf("%d개의 숫자를 입력하세요 : ", sizeofarr);

    for (i = 0; i < sizeofarr; i++)
        scanf(" %d", &arr[i]);

    bubble_sort(arr, sizeofarr);

    printf("정렬 결과 : ");
    for (i = 0; i < sizeofarr; i++)
        printf("%d ", arr[i]);

    return 0;
}

void bubble_sort(int *arr, int size)
{
    int i, j;

    for (i = size - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}