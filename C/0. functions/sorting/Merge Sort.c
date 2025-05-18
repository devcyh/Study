#include <stdio.h>
#include <stdlib.h>
#define sizeofarr 10

void merge_sort(int *arr, int head, int tail);
void merge(int *arr, int head, int mid, int tail);

int main()
{
    int i;
    int arr[sizeofarr];

    printf("%d개의 숫자를 입력하세요 : ", sizeofarr);

    for (i = 0; i < sizeofarr; i++)
        scanf(" %d", &arr[i]);

    merge_sort(arr, 0, sizeofarr - 1);

    printf("정렬 결과 : ");
    for (i = 0; i < sizeofarr; i++)
        printf("%d ", arr[i]);

    return 0;
}

void merge_sort(int *arr, int head, int tail)
{
    if (head >= tail)
        return;

    int mid = (head + tail) / 2;
    merge_sort(arr, head, mid);
    merge_sort(arr, mid + 1, tail);
    merge(arr, head, mid, tail);
}

void merge(int *arr, int head, int mid, int tail)
{
    int i, j, k;
    int *parr = (int *)malloc(sizeof(int) * (tail - head + 1));
    for (i = head; i <= tail; i++)
        parr[i - head] = arr[i];

    i = head;
    j = mid + 1;
    k = head;
    while (i <= mid && j <= tail)
    {
        if (parr[i - head] < parr[j - head])
            arr[k++] = parr[(i++) - head];
        else
            arr[k++] = parr[(j++) - head];
    }

    if (i <= mid)
        while (i <= mid)
            arr[k++] = parr[(i++) - head];
    else
        while (j <= tail)
            arr[k++] = parr[(j++) - head];

    free(parr);
}