#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int data;
    struct _node *next;
} node;

int getnum(FILE *stream, int *num);
int linkedlist(node **head);
void deletelist(node *head);
int buildtour(int **arr);
int nextmax(int *arr, int size);

int main()
{
    int *arr;
    int size, i;
    printf("값을 입력해주세요 : ");
    size = buildtour(&arr);

    if (arr == NULL)
        return 0;

    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("max = [%d], nextmax = [%d]", arr[0], nextmax(arr, size));

    free(arr);
    return 0;
}

int getnum(FILE *stream, int *num)
{
    char str[11];
    int temp;
    int i = 0;

    temp = fgetc(stream);
    while (temp == ' ' && temp != '\n')
        temp = fgetc(stream);
    while (temp != ' ' && temp != '\n')
    {
        str[i++] = temp;
        temp = fgetc(stream);
    }
    str[i] = '\0';

    if (i == 0)
        return 0;
    *num = atoi(str);
    if (temp == '\n')
        return 1;
    else
        return 2;
}

int linkedlist(node **head)
{
    node *tail;
    int num, state, size;

    size = 0;
    state = getnum(stdin, &num);
    if (state == 0)
    {
        *head = NULL;
        return size;
    }
    *head = (node *)malloc(sizeof(node));
    tail = *head;
    tail->data = num;
    tail->next = NULL;
    size++;

    while (state == 2)
    {
        state = getnum(stdin, &num);
        if (state == 0)
            break;
        tail->next = (node *)malloc(sizeof(node));
        tail = tail->next;
        tail->data = num;
        tail->next = NULL;
        size++;
    }

    return size;
}

void deletelist(node *head)
{
    node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int buildtour(int **arr)
{
    node *list, *curr;
    int size, i;

    size = linkedlist(&list);
    if (list == NULL)
    {
        *arr = NULL;
        return size;
    }

    curr = list;
    size = (2 * size) - 1;
    *arr = (int *)malloc(sizeof(int) * size);
    for (i = (size - 1) / 2; i < size; i++)
    {
        (*arr)[i] = curr->data;
        curr = curr->next;
    }
    deletelist(list);

    for (i = size - 1; i > 0; i = i - 2)
    {
        if ((*arr)[i - 1] > (*arr)[i])
            (*arr)[(i / 2) - 1] = (*arr)[i - 1];
        else
            (*arr)[(i / 2) - 1] = (*arr)[i];
    }

    return size;
}

int nextmax(int *arr, int size)
{
    int i, nmax, temp;

    if (size < 3 || size % 2 == 0)
        return 0;

    i = 1;
    nmax = INT_MIN;
    while (i < size - 1)
    {
        if (arr[i] > arr[i + 1])
        {
            temp = arr[i + 1];
            i = (i * 2) + 1;
        }
        else
        {
            temp = arr[i];
            i = (i * 2) + 3;
        }
        if (temp > nmax)
            nmax = temp;
    }

    return nmax;
}