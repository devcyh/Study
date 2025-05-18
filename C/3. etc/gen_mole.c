#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **gen_mole(int row, int column, int mole, int bomb);
void shuffle(int *arr, int size);

int main()
{
    int i, j;
    int round = 10;
    int num = 3;
    int mole = 15;
    int bomb = 5;
    int **marr = gen_mole(round, num, mole, bomb);

    for (i = 0; i < round; i++)
    {
        for (j = 0; j < num; j++)
            printf("%d ", marr[i][j]);
        printf("\n");
    }

    for (i = 0; i < round; i++)
        free(marr[i]);
    free(marr);

    return 0;
}

int **gen_mole(int row, int column, int mole, int bomb)
{
    srand((unsigned int)time(NULL));
    int i, j, k;
    int *oarr = (int *)malloc(sizeof(int) * row);
    for (i = 0; i < row; i++)
        oarr[i] = i;
    int **marr = (int **)malloc(sizeof(int *) * row);
    for (i = 0; i < row; i++)
    {
        marr[i] = (int *)malloc(sizeof(int) * column);
        for (j = 0; j < column; j++)
            marr[i][j] = 0;
    }

    for (j = 0; j < column; j++)
    {
        shuffle(oarr, row);
        k = 0;
        for (i = 0; i < row; i++)
        {
            if (mole > 0)
            {
                marr[oarr[k]][j] = 1;
                mole--;
            }
            else if (bomb > 0)
            {
                marr[oarr[k]][j] = 2;
                bomb--;
            }
            else
                break;
            k++;
        }
    }

    for (i = 0; i < row; i++)
        shuffle(marr[i], column);

    free(oarr);
    return marr;
}

void shuffle(int *arr, int size)
{
    int i, r, temp;
    for (i = 0; i < size - 1; i++)
    {
        r = i + rand() % (size - i);
        temp = arr[i];
        arr[i] = arr[r];
        arr[r] = temp;
    }
}