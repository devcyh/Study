#include <stdio.h>
#define sizeofarr 5

void selection_sort(int *arr, int size);
void swap(int *a, int *b);

int main()
{
    int i;
    int arr[sizeofarr];

    printf("%d개의 숫자를 입력하세요 : ", sizeofarr);

    for (i = 0; i < sizeofarr; i++)
        scanf(" %d", &arr[i]);

    selection_sort(arr, sizeofarr);

    printf("정렬 결과 : ");
    for (i = 0; i < sizeofarr; i++)
        printf("%d ", arr[i]);

    return 0;
}

void selection_sort(int *arr, int size)
{
    int i, j;
    int minindex;

    for (i = 0; i < size - 1; i++)
    {
        minindex = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minindex])
                minindex = j;
        }
        swap(&arr[i], &arr[minindex]);
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}