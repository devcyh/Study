#include <stdio.h>
#include <stdlib.h>

int getnum();
void insertion_sort(int** parr, int parr_size);
int same_element(int* arr, int size, int K);
int photo_max(int** pcows, int N, int K);

int main()
{
	int N; // N cows (1 <= N <= 100,000)
	int K; // (K >= 2)
	int** pcows; // [position x_i][breed b_i]
	int i;

	N = getnum();
	K = getnum();

	pcows = (int**)malloc(N * sizeof(int*));
	for (i = 0; i < N; i++)
	{
		pcows[i] = (int*)malloc(2 * sizeof(int));
		pcows[i][0] = getnum();
		pcows[i][1] = getnum();
	}

	insertion_sort(pcows, N); // x 위치순으로 정렬

	i = photo_max(pcows, N, K);

	printf("\n%d", i);

	for (i = 0; i < N; i++)
	{
		free(pcows[i]);
	}
	free(pcows);

	return 0;
}

int getnum()
{
	char num_str[11];
	char temp;
	int i = 0;

	temp = getchar();
	while (temp == ' ')
	{
		temp = getchar();
	}

	while (temp != ' ' && temp != '\n')
	{
		num_str[i] = temp;
		i++;
		temp = getchar();
	}
	num_str[i] = '\0';

	return atoi(num_str);
}

void insertion_sort(int** parr, int parr_size)
{
	int i, j;
	int temp[2];

	for (i = 1; i < parr_size; i++)
	{
		temp[0] = parr[i][0];
		temp[1] = parr[i][1];
		j = i;

		while (j != 0 && parr[j - 1][0] > temp[0])
		{
			parr[j][0] = parr[j - 1][0];
			parr[j][1] = parr[j - 1][1];
			j--;
		}
		parr[j][0] = temp[0];
		parr[j][1] = temp[1];
	}
}

int same_element(int* arr, int size, int K)
{
	int i = 0;
	int j = 0;
	int temp = 0;

	while (temp == 0 && i < size)
	{
		if (arr[i] != 0)
		{
			temp = arr[i]; // 처음으로 발견한 0이 아닌 값을 temp에 대입
			j++; // 0이 아닌 값을 카운트
		}
		i++;
	}

	while (i < size)
	{
		if (arr[i] != 0)
		{
			j++; // 0이 아닌 값을 카운트
			if (arr[i] != temp) return 0; // 0이 아닌 값이 temp랑 다르면 0(거짓) 반환
		}
		i++;
	}

	if (j >= K) return 1; // 품종 수 j가 K보다 크거나 같으면 1(참) 반환
	else return 0;
}

int photo_max(int** pcows, int N, int K)
{
	int breeds[8]; // 최대 8 품종까지 있음
	int i, j, k;

	for (i = 0; i < N - 1; i++) // i == pcows가 줄어든 크기
	{
		for (j = 0; j <= i; j++) // j == pcows 인덱싱 시작지점
		{
			for (k = 0; k < 8; k++)
			{
				breeds[k] = 0; // breeds 배열 초기화
			}

			for (k = j; k < j + N - i; k++) // 시작부터 끝지점까지 인덱싱
			{
				breeds[pcows[k][1] - 1]++; // 품종 수 기록
			}

			if (same_element(breeds, 8, K) == 1) // 모든 품종의 개수가 같은지 확인
			{
				return pcows[j + N - i - 1][0] - pcows[j][0];
			}
		}
	}

	return -1; // 만족하는 경우 없으면 -1 반환
}