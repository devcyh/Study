#include <stdio.h>
#include <stdlib.h>
#define cachesize 4 // 캐시사이즈 설정

typedef struct _line // 캐시라인 구조체 생성
{
    int bnum;        // 주기억장치 블록번호
    struct _line *l; // double linked list의 left
    struct _line *r; // double linked list의 right
} line;

line *search(line *parr, int size, int num);
void delete (line *pline);
void insert(line *pline, line *node, int num);
void printc(line *parr, int size);

int main()
{
    line cache[cachesize]; // 캐시라인배열 생성
    line node;             // linked list의 head와 tail을 저장하는 노드
    line *pline;           // 캐시라인배열의 주소를 임시로 담기 위한 변수
    int num;               // 다용도 변수
    int count = 0;         // 총 캐시 접근 횟수
    int hit = 0;           // 히트 수

    for (num = 0; num < cachesize; num++) // 배열의 값과 link를 초기화
    {
        cache[num].bnum = -1;             // -1로 초기화
        cache[num].l = cache + (num - 1); // arr[0] <-> arr[1] <-> arr[2] <-> arr[3] 이 되도록 link
        cache[num].r = cache + (num + 1);
    }
    num--;
    cache[0].l = &node; // 배열의 양 끝을 node와 연결
    cache[num].r = &node;
    node.l = cache + num; // node의 left를 arr[3]과 연결
    node.r = cache;       // node의 right를 arr[0]과 연결

    FILE *pfile = fopen("input.txt", "r"); // 파일 포인터 담음
    if (pfile == NULL)
    {
        printf("file not found\n");
        system("pause"); // 콘솔창 자동 종료 방지
        return 0;
    }

    fscanf(pfile, "%d", &num); // 텍스트파일의 텍스트를 int형 숫자로 num에 넣음
    while (num != 99)          // 99가 나오면 루프 종료
    {
        pline = search(cache, cachesize, num); // 원하는 블록이 있는지 검색
        count++;
        if (pline == NULL) // 원하는 블록이 없으면 tail(= node.r)값, 있으면 검색해 나온 주소가 pline에 담김
        {
            pline = node.r;
            printf("miss ");
        }
        else
        {
            hit++;
            printf(" hit ");
        }
        delete (pline);            // 주소 pline에 해당하는 배열노드를 삭제
        insert(pline, &node, num); // 주소 pline에 해당하는 배열노드를 head 부분에 link하고 블럭 값을 넣음

        printf("[%d] ", num);
        printc(cache, cachesize); // 캐시 라인에 들어있는 블록번호를 출력
        printf("\n");

        fscanf(pfile, "%d", &num);
    }
    fclose(pfile);

    printf("\n<result> ");
    printc(cache, cachesize);
    printf("/ hit rate : %d/%d\n", hit, count);
    system("pause");

    return 0;
}

line *search(line *parr, int size, int num) // 원하는 블록이 있는지 검색
{
    int i;
    for (i = 0; i < size; i++)
        if (parr[i].bnum == num)
            return parr + i;
    return NULL;
}

void delete (line *pline) // 주소 pline에 해당하는 배열노드를 삭제
{
    pline->l->r = pline->r; // pline의 왼쪽노드의 right이 pline의 오른쪽노드를 가리키게 함
    pline->r->l = pline->l; // pline의 오른쪽노드의 left가 pline의 왼쪽노드를 가리키게 함
}

void insert(line *pline, line *node, int num) // 주소 pline에 해당하는 배열노드를 head 부분에 link하고 블럭 값을 넣음
{
    pline->l = node->l; // pline의 left가 원래 head인 놈을 가리키게 함
    pline->r = node;    // pline의 right가 node를 가리키게 함
    node->l->r = pline; // 원래 head인 놈의 right가 pline을 가리키게 함
    node->l = pline;    // head로 pline을 지목
    pline->bnum = num;  // 블럭 값을 넣음
}

void printc(line *parr, int size) // 캐시 라인에 들어있는 블록번호를 출력
{
    int i;
    for (i = 0; i < size; i++)
        if (parr[i].bnum != -1)
            printf("%d ", parr[i].bnum);
}