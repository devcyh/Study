#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE
{
    int key;
    int d;
    struct _NODE *next;
} NODE;

int shortest(NODE **graph, int gsize, int start, int end);
void printpath(int *path, int gsize, int start, int end);
void makegraph(FILE *pfile, NODE **graph, int gsize);
void freegraph(NODE **graph, int gsize);

int main()
{
    FILE *pfile;
    NODE **graph;
    int gsize, i, j;

    pfile = fopen("graph0.txt", "r");
    if (pfile == NULL)
    {
        printf("파일이 없습니다.");
        return 0;
    }

    fscanf(pfile, "%d", &gsize);
    graph = (NODE **)malloc(sizeof(NODE *) * gsize);
    for (i = 0; i < gsize; i++)
        graph[i] = NULL;
    makegraph(pfile, graph, gsize);
    fclose(pfile);

    printf("시작점, 종점의 키값을 입력해주세요 : ");
    scanf("%d %d", &i, &j);
    printf("distance = [%d] (INT_MAX = 2147483647는 INF를 의미)", shortest(graph, gsize, i, j));

    freegraph(graph, gsize);
    return 0;
}

int shortest(NODE **graph, int gsize, int start, int end)
{
    bool *visited = (bool *)malloc(sizeof(bool) * gsize);
    int *distance = (int *)malloc(sizeof(int) * gsize);
    int *path = (int *)malloc(sizeof(int) * gsize);
    int vertex, i;
    NODE *gptr;

    // initialize visited, distance, path
    for (i = 0; i < gsize; i++)
    {
        visited[i] = false;
        distance[i] = INT_MAX;
        path[i] = -1;
    }
    visited[start] = true;
    distance[start] = 0;
    gptr = graph[start];
    while (gptr != NULL)
    {
        distance[gptr->key] = gptr->d;
        path[gptr->key] = start;
        gptr = gptr->next;
    }

    while (visited[end] == false)
    {
        // get nearest vertex from (visited vertex, unvisited vertex) paths
        vertex = end;
        for (i = 0; i < gsize; i++)
            if (visited[i] == true)
            {
                gptr = graph[i];
                while (gptr != NULL)
                {
                    if (visited[gptr->key] == false && distance[gptr->key] < distance[vertex])
                        vertex = gptr->key;
                    gptr = gptr->next;
                }
            }
        // update visited
        visited[vertex] = true;
        // update distance, path
        gptr = graph[vertex];
        while (gptr != NULL)
        {
            if (gptr->d + distance[vertex] < distance[gptr->key])
            {
                distance[gptr->key] = gptr->d + distance[vertex];
                path[gptr->key] = vertex;
            }
            gptr = gptr->next;
        }
    }

    printpath(path, gsize, start, end);
    i = distance[end];
    free(visited);
    free(distance);
    free(path);
    return i;
}

void printpath(int *path, int gsize, int start, int end)
{
    int i, j;
    int *arr = (int *)malloc(sizeof(int) * gsize);

    if (path[end] == -1)
    {
        printf("경로 없음\n");
        return;
    }

    i = end;
    arr[0] = end;
    j = 1;
    while (path[i] != start)
    {
        arr[j++] = path[i];
        i = path[i];
    }
    arr[j] = start;

    for (i = j; i > 0; i--)
        printf("[%d] -> ", arr[i]);
    printf("[%d]\n", arr[0]);

    free(arr);
}

void makegraph(FILE *pfile, NODE **graph, int gsize)
{
    int i, j;
    NODE temp;
    NODE *tail;

    for (i = 0; i < gsize; i++)
    {
        fscanf(pfile, "%d %*c %d", &(temp.key), &(temp.d));
        tail = &temp;
        for (j = 0; j < temp.d; j++)
        {
            tail->next = (NODE *)malloc(sizeof(NODE));
            tail = tail->next;
            fscanf(pfile, "%d %*c %d", &(tail->key), &(tail->d));
        }
        tail->next = NULL;
        graph[temp.key] = temp.next;
    }
}

void freegraph(NODE **graph, int gsize)
{
    int i;
    NODE *currptr, *nextptr;

    for (i = 0; i < gsize; i++)
    {
        currptr = graph[i];
        while (currptr != NULL)
        {
            nextptr = currptr->next;
            free(currptr);
            currptr = nextptr;
        }
    }
    free(graph);
}