#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define count 4 // 입력 문자열의 개수

struct info // 구조체
{
	int index; // 순번
	int id; // 학번
	char name[50]; // 이름
	char major[50]; // 학과
	char course[50]; // 수강과목
};

void parse(struct info*, char*);
int num_conv(char*);

int main()
{
	// 입력문자열[4]
	char str_in[count][100] =
	{
		"1/2021001/홍길동/컴퓨터공학과/프로그래밍",
		"2/2021002/홍길순/소프트웨어공학과/프로그래밍",
		"3/2021003/홍길은/컴퓨터공학과/프로그래밍",
		"4/2021004/홍길준/전자공학과/프로그래밍"
	};
	struct info student[count]; // 구조체배열[4]
	int i;

	// 입력값 출력
	printf("입력 문자열\n");
	for (i = 0; i < count; i++)
	{
		printf("%s\n", str_in[i]);
	}

	//입력값을 parsing하여 구조체에 저장
	for (i = 0; i < count; i++)
	{
		parse(&student[i], str_in[i]);
	}

	// 구조체 저장값 출력
	printf("\n구조체 저장값\n");
	for (i = 0; i < count; i++)
	{
		printf("%d %d %s %s %s\n", student[i].index, student[i].id, student[i].name, student[i].major, student[i].course);
	}

	return 0;
}

void parse(struct info* a, char* str)
{
	int i = 0;
	char* pch;

	pch = strtok(str, "/");
	while (pch != NULL) // 문자열(str) 내 "/"로 나누어진 항목의 수(5개)만큼 루프가 돕니다.
	{
		switch (i) // 루프횟수마다 다른 구조체 변수에 값을 넣습니다.
		{
		case 0:
			(*a).index = num_conv(pch);
			break;
		case 1:
			(*a).id = num_conv(pch);
			break;
		case 2:
			strcpy((*a).name, pch);
			break;
		case 3:
			strcpy((*a).major, pch);
			break;
		case 4:
			strcpy((*a).course, pch);
			break;
		}
		pch = strtok(NULL, "/");
		i++;
	}
}

int num_conv(char* str_num) // char형의 숫자를 int형으로 변환합니다.
{
	int num = 0;

	while (*str_num != '\0')
	{
		num = (num * 10) + (*str_num - 48); //char형 숫자의 아스키코드값 - 48 = 숫자값
		str_num++;
	}

	return num;
}