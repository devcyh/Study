#include <stdio.h>
#define arrsize 9

void findMaxMin(int *arr, int size, int *max, int *min);
void swap(int *a, int *b);
int findMax(int *arr, int size);
int findMin(int *arr, int size);

int main()
{
    int i, max, min;
    int arr[arrsize];

    printf("%d개의 값을 입력해주세요 : ", arrsize);
    for (i = 0; i < arrsize; i++)
        scanf("%d", arr + i);
    while (getchar() != '\n')
        ;
    findMaxMin(arr, arrsize, &max, &min);
    printf("Max : [%d], Min : [%d]", max, min);
    return 0;
}

void findMaxMin(int *arr, int size, int *max, int *min)
{
    int i, halfsize;

    halfsize = size / 2;
    for (i = 0; i < halfsize; i++)
    {
        if (arr[i] < arr[i + halfsize])
            swap(arr + i, arr + halfsize + i);
    }

    *max = findMax(arr, halfsize);
    *min = findMin(arr + halfsize, halfsize);

    if (size % 2 != 0)
    {
        if (arr[size - 1] > *max)
            *max = arr[size - 1];
        if (arr[size - 1] < *min)
            *min = arr[size - 1];
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findMax(int *arr, int size)
{
    int i;
    int max = arr[0];
    for (i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int findMin(int *arr, int size)
{
    int i;
    int min = arr[0];
    for (i = 1; i < size; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}