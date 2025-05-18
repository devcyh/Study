#include <stdio.h>
#include <stdbool.h>
#define ARR_SIZE 10

typedef struct _ArrayInfo
{
    int *arr;
    int size;
    int nextIdx;
    bool isFull;
} ArrayInfo;

void initArrInfo(int *arr, int size, ArrayInfo *arrInfo);
void arrInsertVal(int value, ArrayInfo *arrInfo);
int arrGetVal(int logicalIdx, ArrayInfo arrInfo);

int main()
{
    int arr[ARR_SIZE];
    ArrayInfo arrInfo;

    for (int i = 0; i < ARR_SIZE; i++)
        arr[i] = -1;
    initArrInfo(arr, ARR_SIZE, &arrInfo);

    for (int i = 0; i < 100; i++)
    {
        arrInsertVal(i, &arrInfo);

        printf("< iteration %d >\n", i);
        for (int j = 0; j < ARR_SIZE; j++)
            printf("%d ", arrGetVal(j, arrInfo));
        printf("\n\n");
    }

    system("pause");
    return 0;
}

void initArrInfo(int *arr, int size, ArrayInfo *arrInfo)
{
    arrInfo->arr = arr;
    arrInfo->size = size;
    arrInfo->nextIdx = 0;
    arrInfo->isFull = false;
}

void arrInsertVal(int value, ArrayInfo *arrInfo)
{
    (arrInfo->arr)[arrInfo->nextIdx] = value;

    if (arrInfo->nextIdx < arrInfo->size - 1)
        arrInfo->nextIdx++;
    else
    {
        arrInfo->nextIdx = 0;
        arrInfo->isFull = true;
    }
}

int arrGetVal(int logicalIdx, ArrayInfo arrInfo)
{
    int actualIdx;

    if (arrInfo.isFull)
    {
        if (arrInfo.nextIdx + logicalIdx < arrInfo.size)
            actualIdx = arrInfo.nextIdx + logicalIdx;
        else
            actualIdx = arrInfo.nextIdx + logicalIdx - arrInfo.size;
    }
    else
        actualIdx = logicalIdx;

    return arrInfo.arr[actualIdx];
}