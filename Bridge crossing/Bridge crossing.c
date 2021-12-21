#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define man 5 // 사람 수
#define time 30 // 값 프린트 기준
#define upper_lower 0 // 모두 다리를 건너는데 걸린 시간이 time 기준으로 0이면 아래, 1이면 위일때 값 프린트. 이외의 값이면 모든 경우 프린트

void insertion_sort(int* arr, int arr_end_index);
void P(int* start, int* end, int(*state)[3]);
int put_num(int* arr, int num);
int erase_num(int* arr, int index);
int arr_end_index(int* arr);
void write_state(int(*state)[3], int index, int* erased);
void print_state(int(*state)[3], int limit_sec, int up_down);

int count = 0;

int main()
{
	int start[man + 1] = { 0, }; // 마지막에 NULL 역할의 0을 넣음
	int end[man + 1] = { 0, }; // 마지막에 NULL 역할의 0을 넣음
	int state[man][3] = { 0, }; // 마지막에 NULL 역할의 0[3]을 넣음
	int i;

	printf("%d명의 사람들의 속도를 입력해주세요 : ", man);

	for (i = 0; i < man; i++)
	{
		scanf("%d", &start[i]);
	}

	printf("\n");

	insertion_sort(start, i - 1);

	P(start, end, state);

	printf("경우의 수 : [%d]개", count);

	return 0;
}

void insertion_sort(int* arr, int arr_end_index)
{
	int i, j;
	int temp;

	for (i = 1; i <= arr_end_index; i++)
	{
		temp = arr[i];
		j = i;

		while (j != 0 && arr[j - 1] > temp)
		{
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = temp;
	}
}

void P(int* start, int* end, int(*state)[3])
{
	int i, j, k;
	int put_index[3];
	int erased[3] = { 0, };

	i = 0;
	while (start[i] != 0)
	{
		put_index[0] = put_num(end, start[i]);
		erased[0] = erase_num(start, i);

		j = i;
		while (start[j] != 0)
		{
			put_index[1] = put_num(end, start[j]);
			erased[1] = erase_num(start, j);

			switch (start[0] == 0)
			{
			case 0:
				k = 0;
				while (end[k] != 0)
				{
					put_index[2] = put_num(start, end[k]);
					erased[2] = erase_num(end, k);

					write_state(state, arr_end_index(end), erased);

					P(start, end, state);

					put_num(end, erased[2]);
					erase_num(start, put_index[2]);

					k++;
				}

				break;
			case 1:
				write_state(state, arr_end_index(end) - 1, erased);
				print_state(state, time, upper_lower);

				break;
			}
			put_num(start, erased[1]);
			erase_num(end, put_index[1]);

			j++;
		}
		put_num(start, erased[0]);
		erase_num(end, put_index[0]);

		i++;
	}
}

int put_num(int* arr, int num)
{
	int index = 0;
	int arr_end;
	int i;

	while (arr[index] != 0 && num >= arr[index]) index++;
	arr_end = index;
	while (arr[arr_end] != 0) arr_end++;

	for (i = arr_end; i > index; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[index] = num;

	return index;
}

int erase_num(int* arr, int index)
{
	int erased = arr[index];
	int i = index;

	while (arr[i] != 0)
	{
		arr[i] = arr[i + 1];
		i++;
	}

	return erased;
}

int arr_end_index(int* arr)
{
	int i = 0;

	while (arr[i] != 0) i++;

	return i - 1;
}

void write_state(int(*state)[3], int index, int* erased)
{
	switch (erased[0] > erased[1])
	{
	case 0:
		state[index][0] = erased[0];
		state[index][1] = erased[1];
		break;
	case 1:
		state[index][0] = erased[1];
		state[index][1] = erased[0];
		break;
	}
	state[index][2] = erased[2];
}

void print_state(int(*state)[3], int limit_sec, int up_down)
{
	int i = 0;
	int total = 0;

	while (state[i][0] != 0)
	{
		total = total + state[i][1] + state[i][2];
		i++;
	}

	switch (up_down)
	{
	case 0:
		if (total > limit_sec) return;
		break;
	case 1:
		if (total < limit_sec) return;
		break;
	default:
		break;
	}

	i--;
	int j;

	for (j = 0; j < i; j++)
	{
		printf("go : [%d, %d] (%dsec) -> back : [%d] (%dsec) -> ", state[j][0], state[j][1], state[j][1], state[j][2], state[j][2]);
	}
	printf("go : [%d, %d] (%dsec)\n", state[i][0], state[i][1], state[i][1]);
	printf("Total : [%d]sec\n\n", total);

	count++;
}