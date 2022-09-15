// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define C_RAND_MIN 10   // 랜덤 생성 데이터의 하한
#define C_RAND_MAX 1000 // 랜덤 생성 데이터의 상한

void insertionSort(int *arr, int size); // 배열에 담긴 데이터를 크기순으로 정렬해주는 함수
double logB(double x, double base);     // 밑과 진수를 입력하면 해당하는 log 값을 반환하는 함수

int main()
{
    int n, r, k, c, f, sumF, i;            // n : 데이터 개수 / r : 자료의 범위 / k : 계급의 수 / c : 계급간격 / f : 도수 / sumRF : 누적도수 / i : 순환변수
    int *data;                             // 데이터 배열 포인터
    double bound1, bound2, mid, rF, sumRF; // bound1 : 시작 계급경계 / bound2 : 끝 계급경계 / mid : 계급값 / rF : 상대도수 / sumRF : 누적상대도수

    // 랜덤으로 생성할 데이터의 개수를 입력한다
    printf("input data size (input 0 to exit): ");
    scanf("%d", &n); // 변수 n에 사용자의 입력을 저장
    while (n < 0)
    {
        printf("wrong input number\n");
        printf("input data size (input 0 to exit): ");
        scanf("%d", &n);
    }
    if (n == 0)
        return 0;

    // 크기가 n인 배열을 생성
    data = (int *)malloc(sizeof(int) * n);

    // 데이터를 랜덤하게 생성한다
    printf("\n[ 랜덤 값 생성 범위 : %d ~ %d ]", C_RAND_MIN, C_RAND_MAX);
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        data[i] = (rand() % (C_RAND_MAX - C_RAND_MIN + 1)) + C_RAND_MIN; // C_RAND_MIN ~ C_RAND_MAX 범위 내에서 랜덤한 값 생성

        if (i % 10 == 0)
            printf("\n");
        printf("%d\t", data[i]);
    }

    // 자료 범위 r을 지정한다
    insertionSort(data, n); // 배열 정렬
    r = data[n - 1] - data[0];

    // 계급의 수 k를 정한다
    k = (int)(logB(n, 2) + 1 + 0.5); // k = 1 + log_2_n 을 사용. + 0.5는 int로 형변환 되면서 반올림이 되게하는 역할

    // 계급간격 c = r / k 을 결정한다
    c = (int)((double)(r / k) + 1); // + 1은 int로 형변환 되면서 올림이 되도록 하기 위함. 내림하면 c * k < r 이 되서 올림함.

    printf("\n[ 최소값 : %d, 최대값 : %d, 계급의 수 : %d, 계급간격 : %d ]\n", data[0], data[n - 1], k, c);
    printf("\n[계급구간\t\t도수\t\t상대도수\t누적도수\t누적상대도수\t계급값]\n");
    i = 0;                                                                  // 순환변수 초기화
    sumF = 0;                                                               // 누적도수 초기화
    sumRF = 0;                                                              // 누적상대도수 초기화
    bound1 = ((double)(data[n - 1] + data[0]) / 2) - ((double)(c * k) / 2); // 맨 처음 계급의 시작경계를 결정한다. 시작 경계 = (전체 데이터의 중앙값) - (설정된 전체 계급의 범위 / 2)
    while (i < n)
    {
        // 현재 계급의 끝경계를 결정한다
        bound2 = bound1 + c;

        // 계급값(구간의 중앙값)을 구한다
        mid = (double)(bound1 + bound2) / 2;

        // 도수, 누적도수를 구한다
        f = 0;
        while (i < n && data[i] < bound2)
        {
            f++;
            i++;
        }
        sumF += f;

        // 상대도수, 누적상대도수를 구한다
        rF = (double)f / n;
        sumRF += rF;

        // 값을 print
        printf("%.1lf ~ %.1lf\t\t%d\t\t%.2lf\t\t%d\t\t%.2lf\t\t%.1lf\n", bound1, bound2, f, rF, sumF, sumRF, mid);

        // 다음 계급의 시작경계를 결정한다
        bound1 = bound2;
    }

    free(data);
    system("pause");
    return 0;
}

void insertionSort(int *arr, int size)
{
    int i, j;
    int key;

    for (i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

double logB(double x, double base)
{
    return log(x) / log(base);
}