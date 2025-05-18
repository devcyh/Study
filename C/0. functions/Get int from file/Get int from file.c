#include <stdio.h>
#include <stdlib.h>

int getnum(FILE *pfile);

int main()
{
    FILE *pfile = fopen("input.txt", "r");
    if (pfile == NULL)
    {
        printf("파일이 없습니다.");
        return 0;
    }

    int temp;
    while (1)
    {
        temp = getnum(pfile);
        if (temp == EOF)
            break;
        printf("%d ", temp);
    }

    return 0;
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
        return EOF; // 한번도 안돌았으면 EOF밖에 없다는 것이므로 EOF 리턴함.
    return atoi(str);
}