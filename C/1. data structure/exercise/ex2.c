#include <stdio.h>
#include <stdlib.h>

int **gen_2d(int m, int n);
void free_2d(int **arr_2d, int m);
int getnum(FILE *pfile);

int main()
{
    FILE *pfile = fopen("input.txt", "r"); // 파일 포인터 담음
    if (pfile == NULL)
    {
        printf("파일이 없습니다.");
        return 0;
    }

    int m = getnum(pfile); // A행렬의 행
    getnum(pfile);         // k값이랑 똑같아서 버림
    int k = getnum(pfile); // A행렬의 열, B행렬의 행
    int n = getnum(pfile); // B행렬의 열

    int **A = gen_2d(m, k); // A배열 생성
    int **B = gen_2d(k, n); // B배열 생성
    int **C = gen_2d(m, n); // C배열 생성

    int i, l, j; // 순환변수

    for (i = 0; i < m; i++) // A배열에 값 삽입
    {
        for (l = 0; l < k; l++)
            A[i][l] = getnum(pfile);
    }

    for (l = 0; l < k; l++) // B배열에 값 삽입
    {
        for (j = 0; j < n; j++)
            B[l][j] = getnum(pfile);
    }

    fclose(pfile);

    for (i = 0; i < m; i++) // 행렬 곱셈 결과를 C배열에 삽입
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (l = 0; l < k; l++)
                C[i][j] = C[i][j] + A[i][l] * B[l][j];
        }
    }

    for (i = 0; i < m; i++) // 결과 프린트
    {
        for (j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    free_2d(A, m); // A배열을 free
    free_2d(B, k); // B배열을 free
    free_2d(C, m); // C배열을 free

    return 0;
}

int **gen_2d(int m, int n) // 2차원 배열 생성
{
    int i;

    int **arr_2d = (int **)malloc(sizeof(int *) * m);
    for (i = 0; i < m; i++)
        arr_2d[i] = (int *)malloc(sizeof(int) * n);

    return arr_2d;
}

void free_2d(int **arr_2d, int m) // 동적 할당 2차원 배열을 free
{
    int i;
    for (i = 0; i < m; i++)
        free(arr_2d[i]);
    free(arr_2d);
}

int getnum(FILE *pfile) // str을 atoi하는 함수
{
    char str[11];
    char temp;
    int i = 0;

    temp = fgetc(pfile);
    while ((temp == ' ' || temp == '\n') && temp != EOF) // 스페이스, 개행 없앰. EOF면 종료.
        temp = fgetc(pfile);
    while (temp != ' ' && temp != '\n' && temp != EOF) // 스페이스, 개행 나오기 전까지 str에 넣어줌. EOF면 종료.
    {
        str[i] = temp;
        i++;
        temp = fgetc(pfile);
    }
    str[i] = '\0'; // 마지막 널문자 삽입

    if (i == 0)
        return EOF;   // 한번도 안돌았으면 EOF밖에 없다는 것이므로 EOF 리턴함.
    return atoi(str); // 숫자문자열을 정수로
}