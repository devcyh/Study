#include <stdio.h>
#include <stdlib.h>

typedef struct _int2
{
    int x;
    int y;
} int2;

void bfs(int **maze, int **path, int2 rowcol, int2 start);
int drawpath(int **maze, int **path, int2 end);
void nprintf(int **arr, int2 rowcol);

int main()
{
    char fname[50] = "maze0-16-16.txt";
    FILE *pfile;
    int2 rowcol, start, end;
    int **maze, **path;
    int i, j;

    pfile = fopen(fname, "r");
    if (pfile == NULL)
    {
        printf("파일이 없습니다.");
        return 0;
    }

    sscanf(fname, "maze%*d-%d-%d.txt", &rowcol.x, &rowcol.y);

    maze = (int **)malloc(sizeof(int *) * rowcol.x);
    path = (int **)malloc(sizeof(int *) * rowcol.x);
    for (i = 0; i < rowcol.x; i++)
    {
        maze[i] = (int *)malloc(sizeof(int) * rowcol.y);
        path[i] = (int *)malloc(sizeof(int) * rowcol.y);
        for (j = 0; j < rowcol.y; j++)
        {
            fscanf(pfile, "%d", &maze[i][j]);
            switch (maze[i][j])
            {
            case 2:
                start.x = i;
                start.y = j;
                break;
            case 3:
                end.x = i;
                end.y = j;
                break;
            }
            path[i][j] = 0;
        }
    }
    fclose(pfile);

    bfs(maze, path, rowcol, start);
    i = drawpath(maze, path, end);

    nprintf(maze, rowcol);
    printf("이동 횟수 : [%d]", i);

    for (i = 0; i < rowcol.x; i++)
    {
        free(maze[i]);
        free(path[i]);
    }
    free(maze);
    free(path);
    return 0;
}

void bfs(int **maze, int **path, int2 rowcol, int2 start)
{
    int2 *point[2];
    int **state;
    int id0, id1, curr, i, j;

    state = (int **)malloc(sizeof(int *) * rowcol.x);
    for (i = 0; i < rowcol.x; i++)
    {
        state[i] = (int *)malloc(sizeof(int) * rowcol.y);
        for (j = 0; j < rowcol.y; j++)
            state[i][j] = maze[i][j];
    }
    point[0] = (int2 *)malloc(sizeof(int2) * rowcol.x * rowcol.y);
    point[1] = (int2 *)malloc(sizeof(int2) * rowcol.x * rowcol.y);

    curr = 0;
    id1 = 0;
    state[start.x][start.y] = 1;
    point[curr][id1].x = start.x;
    point[curr][id1].y = start.y;
    do
    {
        id0 = id1;
        id1 = 0;
        do
        {
            i = point[curr][id0].x;
            j = point[curr][id0].y;
            id0--;
            if (state[i][j + 1] != 1)
            {
                path[i][j + 1] = 1; // path[i][j]의 값 == 0(제자리) -> (0, 0) / 1(동) -> (0, 1) / 2(서) -> (0, -1) / 3(남) -> (1, 0) / 4(북) -> (-1, 0)
                state[i][j + 1] = 1;
                point[!curr][id1].x = i; // !curr == next를 의미
                point[!curr][id1].y = j + 1;
                id1++;
            }
            if (state[i][j - 1] != 1)
            {
                path[i][j - 1] = 2;
                state[i][j - 1] = 1;
                point[!curr][id1].x = i;
                point[!curr][id1].y = j - 1;
                id1++;
            }
            if (state[i + 1][j] != 1)
            {
                path[i + 1][j] = 3;
                state[i + 1][j] = 1;
                point[!curr][id1].x = i + 1;
                point[!curr][id1].y = j;
                id1++;
            }
            if (state[i - 1][j] != 1)
            {
                path[i - 1][j] = 4;
                state[i - 1][j] = 1;
                point[!curr][id1].x = i - 1;
                point[!curr][id1].y = j;
                id1++;
            }
        } while (id0 >= 0);
        id1--;
        curr = !curr;
    } while (id1 >= 0);

    for (i = 0; i < rowcol.x; i++)
        free(state[i]);
    free(state);
    free(point[0]);
    free(point[1]);
}

int drawpath(int **maze, int **path, int2 end)
{
    int i, j, move;

    i = end.x;
    j = end.y;
    move = 0;
    while (path[i][j] != 0)
    {
        switch (path[i][j])
        {
        case 1:
            j--;
            break;
        case 2:
            j++;
            break;
        case 3:
            i--;
            break;
        case 4:
            i++;
            break;
        }
        maze[i][j] = 4;
        move++;
    }
    maze[i][j] = 2;
    return move;
}

void nprintf(int **arr, int2 rowcol)
{
    int i, j;

    for (i = 0; i < rowcol.x; i++)
    {
        for (j = 0; j < rowcol.y; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
    printf("\n");
}