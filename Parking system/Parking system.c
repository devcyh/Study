#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int disp_menu(void);
void in_park(int(*)[2][5], int*);
void out_park(int(*)[2][5]);
void book_park(int(*)[2][5], int*);
void cancel_book(int(*)[2][5], int*);
void show_park(int(*)[2][5]);

int main(void)
{
	int i, j, k; // park_space 초기화 for문의 순환변수
	int park_space[3][2][5]; // 3층 2행 5열의 주차 공간. 저장값 0 == 비어있음, 1 == 사용중, 2 == 예약된자리
	int reserved[30]; // 예약차량번호 목록, 최대 30대 지정 가능.
	int sel; // 메뉴 출력 함수의 반환값을 저장

	for (i = 0; i < 3; i++) // park_space 배열을 0(비어있음)으로초기화
	{
		for (j = 0; j < 2; j++)
		{
			for (k = 0; k < 5; k++)
			{
				park_space[i][j][k] = 0;
			}
		}
	}

	while (1)
	{
		sel = disp_menu(); // 메뉴 출력
		if (sel == 0) break; // 값이 종료에 해당하는 0이면 while문을 탈출합니다.

		switch (sel) // sel 값에 따라 각 케이스가 선택됩니다.
		{
		case 1: in_park(park_space, reserved); break; // 주차
		case 2: out_park(park_space); break; // 출차
		case 3: book_park(park_space, reserved); break; // 주차 예약
		case 4: cancel_book(park_space, reserved); break; // 예약 취소
		case 5: show_park(park_space); break; // 주차 목록
		default: printf("잘못된 입력입니다.\n"); break; // 0~5가 아닌 값이 입력되면 선택됩니다.
		}
		printf("\n");
	}
	return 0;
}

int disp_menu(void) // 메뉴를 출력하는 함수입니다.
{
	int sel;
	printf("1. 주차\n");
	printf("2. 출차\n");
	printf("3. 지정차량 등록\n");
	printf("4. 지정차량 등록취소\n");
	printf("5. 주차현황 출력\n");
	printf("0. 종료\n");
	printf("> 번호 선택 : ");
	scanf("%d", &sel);
	while (getchar() != '\n');
	return sel;
}

void in_park(int(*pps)[2][5], int* pres) // 주차 함수입니다. 포인터를 통해 park_space, reserved 배열의 주소를 입력받습니다.
{
	show_park(pps); // 주차 현황 출력 함수를 실행합니다.

	int i, j, k; // [층], [자리번호], [차량번호] 입력값 임시 보관 변수

	while (1)
	{
		printf("\n사용하려는 자리의 [층], [자리번호]를 입력하세요 (뒤로가려면 -1을 입력하세요) : ");
		scanf("%d", &i); // [층] 값을 입력받습니다.
		if (i == -1) // -1(뒤로가기)이 입력되면 함수를 끝냅니다.
		{
			while (getchar() != '\n'); // 버퍼를 비웁니다.
			return;
		}
		scanf("%d", &j); // [자리번호] 값을 입력받습니다.
		while (getchar() != '\n');
		if ((i > 0 && i <= 3) && (j > 0 && j <= 10)) // (1 <= [층]값 <= 3) and (1 <= [자리번호]값 <= 10)인지 확인합니다.
		{
			if (pps[i - 1][(j - 1) / 5][(j - 1) % 5] == 0) // park_space[3][2][5]에서 선택한 자리에 들어있는 값 == 0(빈자리)이면 while문을 탈출합니다.
			{
				printf("\n<선택 위치>\n층 : [%d], 자리번호 : [%d], 상태 : [비어있음]\n", i, j);
				break;
			}
			if (pps[i - 1][(j - 1) / 5][(j - 1) % 5] == 2) // park_space[3][2][5]에서 선택한 자리에 들어있는 값 == 2(예약된자리)
			{
				printf("\n<선택 위치>\n층 : [%d], 자리번호 : [%d], 상태 : [예약된자리]\n", i, j);

				while (1)
				{
					printf("\n차량 번호 4자리를 입력해주세요 (뒤로가려면 -1을 입력하세요) : ");
					scanf("%d", &k); // 차량 번호 4자리를 입력합니다.
					while (getchar() != '\n');
					if (k == -1) return; // -1(뒤로가기)이 입력되면 함수를 끝냅니다.
					else
					{
						if (pres[((i - 1) * 10) + (j - 1)] == k) break; // reserved[30]에 저장된 선택한 자리의 차량번호 == k(입력된 값)이면 while문을 탈출합니다.
						else printf("잘못된 입력입니다.\n");
					}
				}
				break;
			}
			else printf("사용중인 자리입니다.\n"); // park_space[3][2][5]에서 선택한 자리에 들어있는 값 == 1(사용중)일때 출력
		}
		else printf("잘못된 입력입니다.\n"); // (1 <= [층]값 <= 3) and (1 <= [자리번호]값 <= 10)이 아니면 출력합니다.
	}

	pps[i - 1][(j - 1) / 5][(j - 1) % 5] = 1; // park_space[3][2][5](층,행,열) 배열의 선택한 자리에 1(사용중)을 대입합니다.

	printf("\n주차되었습니다.\n");
}

void out_park(int(*pps)[2][5]) // 출차 함수입니다. 포인터를 통해 park_space 배열의 주소를 입력받습니다.
{
	int i, j; // [층], [자리번호] 입력값 임시 보관 변수

	while (1)
	{
		printf("\n출차하려는 자리의 [층], [자리번호]를 입력하세요 (뒤로가려면 -1을 입력하세요) : ");
		scanf("%d", &i); // 출차하려는 자리의 [층]을 입력합니다.
		if (i == -1)
		{
			while (getchar() != '\n');
			return;
		}
		scanf("%d", &j); // 출차하려는 자리의 [자리번호]를 입력합니다.
		while (getchar() != '\n');
		if ((i > 0 && i <= 3) && (j > 0 && j <= 10))
		{
			if (pps[i - 1][(j - 1) / 5][(j - 1) % 5] == 1) break;
			else printf("차량이 없습니다.\n");
		}
		else printf("잘못된 입력입니다.\n");
	}
	printf("\n<선택 위치>\n층 : [%d], 자리번호 : [%d]\n", i, j);

	pps[i - 1][(j - 1) / 5][(j - 1) % 5] = 0; // 입력된 자리에 해당하는 배열의 [층], [행], [열]에 0(비어있음)을 대입합니다.

	printf("\n출차되었습니다.\n");
}

void book_park(int(*pps)[2][5], int* pres) // 예약 함수입니다. 포인터를 통해 park_space, reserved 배열의 주소를 입력받습니다.
{
	show_park(pps);

	int i, j, k; // [층], [자리번호], [차량번호] 입력값 임시 보관 변수

	while (1)
	{
		printf("\n예약하려는 자리의 [층], [자리번호]를 입력하세요 (뒤로가려면 -1을 입력하세요) : ");
		scanf("%d", &i); // 예약하려는 자리의 [층]을 입력합니다.
		if (i == -1)
		{
			while (getchar() != '\n');
			return;
		}
		scanf("%d", &j); // 예약하려는 자리의 [자리번호]를 입력합니다.
		while (getchar() != '\n');
		if ((i > 0 && i <= 3) && (j > 0 && j <= 10))
		{
			if (pps[i - 1][(j - 1) / 5][(j - 1) % 5] == 0) break;
			else printf("예약불가 위치입니다.\n");
		}
		else printf("잘못된 입력입니다.\n");
	}
	printf("\n<선택 위치>\n층 : [%d], 자리번호 : [%d]\n", i, j);

	while (1)
	{
		printf("\n차량 번호 4자리를 입력해주세요 (뒤로가려면 -1을 입력하세요) : ");
 		scanf("%d", &k); // 차량 번호 4자리를 입력합니다.
		while (getchar() != '\n');
		if (k == -1) return;
		else if (k > 999 && k < 10000) break; // 입력받은 숫자가 4자리 숫자인지 확인합니다.
		else printf("잘못된 입력입니다.\n");
	}

	pps[i - 1][(j - 1) / 5][(j - 1) % 5] = 2; // 입력된 자리에 해당하는 배열의 [층], [행], [열]에 2(예약)를 대입합니다.
	pres[((i - 1) * 10) + (j - 1)] = k; // 입력된 자리에 해당하는 열에 차량번호를 대입합니다.

	printf("\n<예약 정보>\n차량번호 : [%d], 층 : [%d], 자리번호 : [%d]\n", pres[((i - 1) * 10) + (j - 1)], i, j);
	printf("\n예약되었습니다.\n");
}

void cancel_book(int(*pps)[2][5], int* pres) // 예약 취소 함수입니다. 포인터를 통해 park_space 배열의 주소를 입력받습니다.
{
	int i, j, k; // [층], [자리번호], [차량번호] 입력값 임시 보관 변수

	while (1)
	{
		printf("\n예약된 자리의 [층], [자리번호]를 입력하세요 (뒤로가려면 -1을 입력하세요) : ");
		scanf("%d", &i); // 예약된 자리의 [층]을 입력합니다.
		if (i == -1)
		{
			while (getchar() != '\n');
			return;
		}
		scanf("%d", &j); // 예약된 자리의 [자리번호]를 입력합니다.
		while (getchar() != '\n');
		if ((i > 0 && i <= 3) && (j > 0 && j <= 10))
		{
			if (pps[i - 1][(j - 1) / 5][(j - 1) % 5] == 2) break;
			else printf("예약 위치가 아닙니다.\n");
		}
		else printf("잘못된 입력입니다.\n");
	}
	printf("\n<선택 위치>\n층 : [%d], 자리번호 : [%d]\n", i, j);

	while (1)
	{
		printf("\n차량 번호 4자리를 입력해주세요 (뒤로가려면 -1을 입력하세요) : ");
		scanf("%d", &k); // 차량 번호 4자리를 입력합니다.
		while (getchar() != '\n');
		if (k == -1) return;
		else
		{
			if (pres[((i - 1) * 10) + (j - 1)] == k) break;
			else printf("잘못된 입력입니다.\n");
		}
	}

	pps[i - 1][(j - 1) / 5][(j - 1) % 5] = 0; // 입력된 자리에 해당하는 배열의 [층], [행], [열]에 0(빈자리)를 대입합니다.

	printf("\n예약이 취소되었습니다.\n");
}

void show_park(int(*pps)[2][5]) // 주차 현황을 보여주는 함수입니다. 포인터를 통해 park_space 배열의 주소를 입력받습니다.
{
	printf("\n");

	int i, j, k; // 주차현황 표시 for문의 순환변수

	for (i = 0; i < 3; i++) // 층(3)
	{
		printf("<%d층>\n", 3 - i); // 3층부터 표시
		for (j = 0; j < 2; j++) // 행(2)
		{
			for (k = 0; k < 5; k++) // 열(5)
			{
				switch (pps[2 - i][j][k]) //  park_space 배열의 각 자리에 들어가 있는 값을 확인합니다.
				{
				case 0: printf("%d. 비어있음\t", (j * 5) + (k + 1)); break; // 0 == 비어있음
				case 1: printf("%d. 사용중\t", (j * 5) + (k + 1)); break; // 1 == 사용중
				case 2: printf("%d. 예약된자리\t", (j * 5) + (k + 1)); break; // 2 == 예약된자리
				}
			}
			printf("\n");
		}
	}
}