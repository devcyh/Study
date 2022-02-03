#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _NODE
{
    int key;
    int d;
    struct _NODE *next;
} NODE;

int prim(NODE **graph, int gsize, int start);
void makegraph(FILE *pfile, NODE **graph, int gsize);
void freegraph(NODE **graph, int gsize);

int main()
{
    FILE *pfile;
    NODE **graph;
    int gsize, i;

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

    printf("시작점의 키값을 입력해주세요 : ");
    scanf("%d", &i);
    printf("Cost = [%d]", prim(graph, gsize, i));

    freegraph(graph, gsize);
    return 0;
}

int prim(NODE **graph, int gsize, int start)
{
    bool *visited = (bool *)malloc(sizeof(bool) * gsize);
    int vertex, distance, cost, i, j;
    NODE *gptr;

    // initialize visited, cost
    for (i = 0; i < gsize; i++)
        visited[i] = false;
    visited[start] = true;
    cost = 0;

    for (i = 0; i < gsize - 1; i++) // 노드개수 - 1(== 모든 노드를 연결하는데 필요한 최소의 엣지수)번 순환
    {
        // get shortest edge from (visited node, unvisited node) edges
        distance = INT_MAX;
        for (j = 0; j < gsize; j++)
            if (visited[j] == true)
            {
                gptr = graph[j];
                while (gptr != NULL)
                {
                    if (visited[gptr->key] == false && gptr->d < distance)
                    {
                        vertex = gptr->key;
                        distance = gptr->d;
                    }
                    gptr = gptr->next;
                }
            }
        // if (there is no such edge) break
        if (distance == INT_MAX)
            break;
        // update visited, cost
        visited[vertex] = true;
        cost = cost + distance;
    }

    free(visited);
    return cost;
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