#include <stdio.h>
#define sizeofarr 10

void quick_sort(int *arr, int head, int tail);
int partition(int *arr, int head, int tail);
void swap(int *a, int *b);

int main()
{
    int i;
    int arr[sizeofarr];

    printf("%d개의 숫자를 입력하세요 : ", sizeofarr);

    for (i = 0; i < sizeofarr; i++)
        scanf(" %d", &arr[i]);

    quick_sort(arr, 0, sizeofarr - 1);

    printf("정렬 결과 : ");
    for (i = 0; i < sizeofarr; i++)
        printf("%d ", arr[i]);

    return 0;
}

void quick_sort(int *arr, int head, int tail)
{
    if (head >= tail)
        return;
    int mid = partition(arr, head, tail);
    quick_sort(arr, head, mid - 1);
    quick_sort(arr, mid + 1, tail);
}

int partition(int *arr, int head, int tail)
{
    int i = head + 1; // pivot은 배열의 맨 처음 값. 따라서 head + 1부터 시작
    int j = tail;

    while (1)
    {
        while (arr[i] < arr[head] && i < j) // arr[i++] <= arr[head] 에서 =을 넣는 이유 -> 배열 중간에 pivot이랑 같은 값으로 이루어진 장벽이 있으면 영원히 루프 안끝날거같아서
            i++;
        while (arr[j] >= arr[head] && j > head)
            j--;
        if (i >= j)
            break;
        swap(arr + i, arr + j);
    }
    swap(arr + head, arr + j); // pivot(arr + head)이랑 arr + j랑 swap하는 이유 -> arr + i는 pivot보다 큰 값이라 바꾸면 안됨. arr + j가 pivot보다 작은 값이라 이 놈이랑 바꿈
    return j;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}