// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define C_RAND_MIN 10   // ���� ���� �������� ����
#define C_RAND_MAX 1000 // ���� ���� �������� ����

void insertionSort(int *arr, int size); // �迭�� ��� �����͸� ũ������� �������ִ� �Լ�
double logB(double x, double base);     // �ذ� ������ �Է��ϸ� �ش��ϴ� log ���� ��ȯ�ϴ� �Լ�

int main()
{
    int n, r, k, c, f, sumF, i;            // n : ������ ���� / r : �ڷ��� ���� / k : ����� �� / c : ��ް��� / f : ���� / sumRF : �������� / i : ��ȯ����
    int *data;                             // ������ �迭 ������
    double bound1, bound2, mid, rF, sumRF; // bound1 : ���� ��ް�� / bound2 : �� ��ް�� / mid : ��ް� / rF : ��뵵�� / sumRF : ������뵵��

    // �������� ������ �������� ������ �Է��Ѵ�
    printf("input data size (input 0 to exit): ");
    scanf("%d", &n); // ���� n�� ������� �Է��� ����
    while (n < 0)
    {
        printf("wrong input number\n");
        printf("input data size (input 0 to exit): ");
        scanf("%d", &n);
    }
    if (n == 0)
        return 0;

    // ũ�Ⱑ n�� �迭�� ����
    data = (int *)malloc(sizeof(int) * n);

    // �����͸� �����ϰ� �����Ѵ�
    printf("\n[ ���� �� ���� ���� : %d ~ %d ]", C_RAND_MIN, C_RAND_MAX);
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        data[i] = (rand() % (C_RAND_MAX - C_RAND_MIN + 1)) + C_RAND_MIN; // C_RAND_MIN ~ C_RAND_MAX ���� ������ ������ �� ����

        if (i % 10 == 0)
            printf("\n");
        printf("%d\t", data[i]);
    }

    // �ڷ� ���� r�� �����Ѵ�
    insertionSort(data, n); // �迭 ����
    r = data[n - 1] - data[0];

    // ����� �� k�� ���Ѵ�
    k = (int)(logB(n, 2) + 1 + 0.5); // k = 1 + log_2_n �� ���. + 0.5�� int�� ����ȯ �Ǹ鼭 �ݿø��� �ǰ��ϴ� ����

    // ��ް��� c = r / k �� �����Ѵ�
    c = (int)((double)(r / k) + 1); // + 1�� int�� ����ȯ �Ǹ鼭 �ø��� �ǵ��� �ϱ� ����. �����ϸ� c * k < r �� �Ǽ� �ø���.

    printf("\n[ �ּҰ� : %d, �ִ밪 : %d, ����� �� : %d, ��ް��� : %d ]\n", data[0], data[n - 1], k, c);
    printf("\n[��ޱ���\t\t����\t\t��뵵��\t��������\t������뵵��\t��ް�]\n");
    i = 0;                                                                  // ��ȯ���� �ʱ�ȭ
    sumF = 0;                                                               // �������� �ʱ�ȭ
    sumRF = 0;                                                              // ������뵵�� �ʱ�ȭ
    bound1 = ((double)(data[n - 1] + data[0]) / 2) - ((double)(c * k) / 2); // �� ó�� ����� ���۰�踦 �����Ѵ�. ���� ��� = (��ü �������� �߾Ӱ�) - (������ ��ü ����� ���� / 2)
    while (i < n)
    {
        // ���� ����� ����踦 �����Ѵ�
        bound2 = bound1 + c;

        // ��ް�(������ �߾Ӱ�)�� ���Ѵ�
        mid = (double)(bound1 + bound2) / 2;

        // ����, ���������� ���Ѵ�
        f = 0;
        while (i < n && data[i] < bound2)
        {
            f++;
            i++;
        }
        sumF += f;

        // ��뵵��, ������뵵���� ���Ѵ�
        rF = (double)f / n;
        sumRF += rF;

        // ���� print
        printf("%.1lf ~ %.1lf\t\t%d\t\t%.2lf\t\t%d\t\t%.2lf\t\t%.1lf\n", bound1, bound2, f, rF, sumF, sumRF, mid);

        // ���� ����� ���۰�踦 �����Ѵ�
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