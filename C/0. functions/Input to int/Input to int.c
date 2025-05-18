#include <stdio.h>
#include <stdlib.h>

int getnum();

int main()
{
	int a;

	printf("숫자 입력 : ");

	a = getnum();

	printf("입력한 값 : [%d]", a);

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