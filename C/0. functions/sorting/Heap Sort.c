#include <stdio.h>

void up_heap_sort(int *arr, int size);
void down_heap_sort(int *arr, int size);
void swap(int *a, int *b);

int main()
{
    int arr[10] = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
    int i, size;

    size = sizeof(arr) / sizeof(int);
    up_heap_sort(arr, size);

    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);

    return 0;
}

void up_heap_sort(int *arr, int size)
{
    int i, child, parent;

    for (i = 1; i < size; i = i + 2) // 힙을 구성
    {
        child = i;
        if (child + 1 < size && arr[child] < arr[child + 1])
            child++;
        do
        {
            parent = (child - 1) / 2;
            if (arr[child] > arr[parent])
            {
                swap(arr + child, arr + parent);
                child = parent;
            }
            else
                break;
        } while (child > 0);
    }

    for (i = size - 1; i > 0; i--) // 크기를 줄여가며 반복적으로 힙을 구성
    {
        swap(arr + i, arr);
        parent = 0;
        child = 1;
        while (child < i)
        {
            if (child + 1 < i && arr[child] < arr[child + 1])
                child++;
            if (arr[child] > arr[parent])
            {
                swap(arr + child, arr + parent);
                parent = child;
                child = (2 * child) + 1;
            }
            else
                break;
        }
    }
}

void down_heap_sort(int *arr, int size)
{
    int i, child, parent;

    for (i = size - 1; i > 0; i = i - 2) // 힙을 구성
    {
        parent = (i - 1) / 2;
        child = (2 * parent) + 1;
        while (child < size)
        {
            if (child + 1 < size && arr[child] < arr[child + 1])
                child++;
            if (arr[child] > arr[parent])
            {
                swap(arr + child, arr + parent);
                parent = child;
                child = (2 * parent) + 1;
            }
            else
                break;
        }
    }

    for (i = size - 1; i > 0; i--) // 크기를 줄여가며 반복적으로 힙을 구성
    {
        swap(arr + i, arr);
        parent = 0;
        child = 1;
        while (child < i)
        {
            if (child + 1 < i && arr[child] < arr[child + 1])
                child++;
            if (arr[child] > arr[parent])
            {
                swap(arr + child, arr + parent);
                parent = child;
                child = (2 * child) + 1;
            }
            else
                break;
        }
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}