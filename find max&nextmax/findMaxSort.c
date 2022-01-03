#include <stdio.h>
#include <stdlib.h>
#define sizeofarr 9

void findMaxSort(int *arr, int size);

int main()
{
    int i;
    int arr[sizeofarr];

    printf("%d개의 숫자를 입력하세요 : ", sizeofarr);

    for (i = 0; i < sizeofarr; i++)
        scanf(" %d", &arr[i]);

    findMaxSort(arr, sizeofarr);

    printf("정렬 결과 : ");
    for (i = 0; i < sizeofarr; i++)
        printf("%d ", arr[i]);

    return 0;
}

void findMaxSort(int *arr, int size)
{
    int i, tarrsize, parent, child;
    int *tourarr;

    tarrsize = (2 * size) - 1;
    tourarr = (int *)malloc(sizeof(int) * tarrsize);
    for (i = 0; i < size; i++)
        tourarr[size - 1 + i] = arr[i];
    for (i = tarrsize - 2; i > 0; i = i - 2)
    {
        if (tourarr[i] > tourarr[i + 1])
            tourarr[(i - 1) / 2] = tourarr[i];
        else
            tourarr[(i - 1) / 2] = tourarr[i + 1];
    }

    arr[size - 1] = tourarr[0];
    for (i = size - 2; i >= 0; i--)
    {
        parent = 0;
        child = 1;
        while (child < tarrsize)
        {
            if (tourarr[child] > tourarr[child + 1])
                parent = child;
            else
                parent = child + 1;

            child = (2 * parent) + 1;
            tourarr[parent] = INT_MIN;
        }

        parent = (parent - 1) / 2;
        while (child > 0)
        {
            child = (2 * parent) + 1;
            if (tourarr[child] > tourarr[child + 1])
                tourarr[parent] = tourarr[child];
            else
                tourarr[parent] = tourarr[child + 1];

            child = parent;
            parent = (parent - 1) / 2;
        }

        arr[i] = tourarr[0];
    }

    free(tourarr);
}