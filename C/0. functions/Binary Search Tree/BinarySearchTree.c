#include <stdio.h>
#include <stdlib.h>

typedef struct _tnode
{
    int key;
    struct _tnode *left;
    struct _tnode *right;
} tnode;

typedef struct _qnode
{
    tnode *tnptr;
    struct _qnode *next;
} qnode;

tnode *i_search(tnode *root, int target);
tnode *r_search(tnode *ptr, int target);
tnode *i_insert(tnode **root, int target);
tnode *r_insert(tnode *currptr, int target);
tnode *r_delete(tnode *currptr, int target);
tnode *findMin(tnode *ptr);
int DFS(tnode *ptr);
int BFS(tnode *root);
void free_by_DFS(tnode *ptr);

int main()
{
    tnode *root = NULL;
    int num = -1;
    while (num != 0)
    {
        printf("<이진탐색트리>\n1. 값 탐색\n2. 값 삽입\n3. 값 삭제\n4. 모든 값 출력\n0. 종료\n");
        printf("사용하실 기능의 번호를 입력해주세요 : ");
        scanf("%d", &num);
        while (getchar() != '\n')
            ;
        printf("\n");
        switch (num)
        {
        case 0:
            free_by_DFS(root);
            return 0;
            break;

        case 1:
            printf("[값 탐색]\n1. 순환 탐색\n2. 재귀 탐색\n");
            printf("탐색 방법을 선택해주세요 : ");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                printf("탐색할 값을 입력해주세요 : ");
                scanf("%d", &num);
                while (getchar() != '\n')
                    ;
                if (i_search(root, num) != NULL)
                    printf("-탐색 완료-");
                else
                    printf("-탐색 실패(값 없음)-");
                break;

            case 2:
                printf("탐색할 값을 입력해주세요 : ");
                scanf("%d", &num);
                while (getchar() != '\n')
                    ;
                if (r_search(root, num) != NULL)
                    printf("-탐색 완료-");
                else
                    printf("-탐색 실패(값 없음)-");
                break;

            default:
                printf("잘못된 입력입니다.");
            }
            break;

        case 2:
            printf("[값 삽입]\n1. 순환 삽입\n2. 재귀 삽입\n");
            printf("삽입 방법을 선택해주세요 : ");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                printf("삽입할 값을 입력해주세요 : ");
                scanf("%d", &num);
                while (getchar() != '\n')
                    ;
                if (i_insert(&root, num) != NULL)
                    printf("-삽입 완료-");
                else
                    printf("-삽입 실패(중복된 값 존재)-");
                break;

            case 2:
                printf("삽입할 값을 입력해주세요 : ");
                scanf("%d", &num);
                while (getchar() != '\n')
                    ;
                if (r_search(root, num) == NULL)
                {
                    root = r_insert(root, num);
                    printf("-삽입 완료-");
                }
                else
                    printf("-삽입 실패(중복된 값 존재)-");
                break;

            default:
                printf("잘못된 입력입니다.");
            }
            break;

        case 3:
            printf("[값 삭제]\n2. 재귀 삭제\n");
            printf("삭제 방법을 선택해주세요 : ");
            scanf("%d", &num);
            switch (num)
            {
            case 2:
                printf("삭제할 값을 입력해주세요 : ");
                scanf("%d", &num);
                while (getchar() != '\n')
                    ;
                if (r_search(root, num) != NULL)
                {
                    root = r_delete(root, num);
                    printf("-삭제 완료-");
                }
                else
                    printf("-삭제 실패(값 없음)-");
                break;

            default:
                printf("잘못된 입력입니다.");
            }
            break;

        case 4:
            printf("[모든 값 출력]\n1. DFS\n2. BFS\n");
            printf("탐색 방법을 선택해주세요 : ");
            scanf("%d", &num);
            switch (num)
            {
            case 1:
                if (DFS(root) == 0)
                    printf("-값 없음-");
                break;

            case 2:
                if (BFS(root) == 0)
                    printf("-값 없음-");
                break;

            default:
                printf("잘못된 입력입니다.");
            }
            break;

        default:
            printf("잘못된 입력입니다.");
        }
        printf("\n\n");
        num = -1;
    }
}

tnode *i_search(tnode *ptr, int target) // 탐색하는 값이 있으면 해당 노드의 주소를, 없으면 NULL을 반환
{
    while (ptr != NULL)
    {
        if (target < ptr->key)
            ptr = ptr->left;
        else if (target > ptr->key)
            ptr = ptr->right;
        else // 탐색 값 발견
            break;
    }
    return ptr;
}

tnode *r_search(tnode *ptr, int target) // 탐색하는 값이 있으면 해당 노드의 주소를, 없으면 NULL을 반환
{
    if (ptr == NULL)
        ;
    else if (target < ptr->key)
        return r_search(ptr->left, target);
    else if (target > ptr->key)
        return r_search(ptr->right, target);
    return ptr;
}

tnode *i_insert(tnode **root, int target) // 삽입 성공 시 해당 노드의 주소를, 실패 시 NULL을 반환
{
    tnode *currptr = NULL;
    tnode *nextptr = *root;

    while (nextptr != NULL)
    {
        currptr = nextptr;
        if (target < currptr->key)
            nextptr = currptr->left;
        else if (target > currptr->key)
            nextptr = currptr->right;
        else
            return NULL; // 이미 같은 값이 존재하면 NULL을 반환
    }

    nextptr = (tnode *)malloc(sizeof(tnode));
    nextptr->key = target;
    nextptr->left = NULL;
    nextptr->right = NULL;

    if (*root == NULL)
        *root = nextptr; // root 노드가 없을 때(아예 트리가 없을때) root 노드를 생성
    else if (target < currptr->key)
        currptr->left = nextptr;
    else if (target > currptr->key)
        currptr->right = nextptr;

    return nextptr;
}

tnode *r_insert(tnode *currptr, int target) // 삽입 함수. 삽입 노드 주소 값 반환 불가능. 삽입 실패 시(중복 값 있을때) NULL값 반환이 안됨. root가 NULL일 경우를 위해 main 함수에서 root에 함수 반환 값 받아줘야함
{
    tnode *tempptr;
    if (currptr == NULL)
    {
        tempptr = (tnode *)malloc(sizeof(tnode));
        tempptr->key = target;
        tempptr->left = NULL;
        tempptr->right = NULL;
        currptr = tempptr;
    }
    else if (target < currptr->key)
        currptr->left = r_insert(currptr->left, target);
    else if (target > currptr->key)
        currptr->right = r_insert(currptr->right, target);
    return currptr;
}

tnode *r_delete(tnode *currptr, int target)
{
    tnode *tempptr;
    if (currptr == NULL)
        ;
    else if (target < currptr->key)
        currptr->left = r_delete(currptr->left, target);
    else if (target > currptr->key)
        currptr->right = r_delete(currptr->right, target);
    else // 현재 노드의 key값이 target값과 같음
    {
        if (currptr->left == NULL && currptr->right == NULL) // 삭제할 노드가 자식이 없음
        {
            free(currptr);
            currptr = NULL;
        }
        else if (currptr->left == NULL) // 삭제할 노드는 right에 자식을 가짐
        {
            tempptr = currptr;
            currptr = currptr->right;
            free(tempptr);
        }
        else if (currptr->right == NULL) // 삭제할 노드는 left에 자식을 가짐
        {
            tempptr = currptr;
            currptr = currptr->left;
            free(tempptr);
        }
        else // 삭제할 노드의 자식이 둘
        {
            tempptr = findMin(currptr->right);                       // 현재 노드의 right에서 min값을 보유한 노드의 주소를 반환
            currptr->key = tempptr->key;                             // right에 있는 min값을 현재 노드(삭제 대상 키값 가짐)에 넣어줌. 따라서 현재 노드의 target값은 삭제됨
            currptr->right = r_delete(currptr->right, tempptr->key); // 원래 min값을 가지고 있던 노드를 삭제. min값을 가진 노드는 if (currptr->left == NULL && currptr->right == NULL) 혹은 else if (currptr->left == NULL)에 걸림
        }
    }
    return currptr;
}

tnode *findMin(tnode *ptr)
{
    if (ptr->left == NULL)
        return ptr;
    else
        return findMin(ptr->left);
}

int DFS(tnode *ptr)
{
    if (ptr == NULL)
        return 0;
    DFS(ptr->left);
    printf("%d ", ptr->key);
    DFS(ptr->right);
    return 1;
}

int BFS(tnode *root)
{
    qnode *head, *tail, *temp;

    if (root == NULL)
        return 0;
    tail = (qnode *)malloc(sizeof(qnode));
    tail->tnptr = root;
    tail->next = NULL;
    head = tail;

    while (head != NULL)
    {
        if (head->tnptr->left != NULL)
        {
            tail->next = (qnode *)malloc(sizeof(qnode));
            tail = tail->next;
            tail->tnptr = head->tnptr->left;
            tail->next = NULL;
        }
        if (head->tnptr->right != NULL)
        {
            tail->next = (qnode *)malloc(sizeof(qnode));
            tail = tail->next;
            tail->tnptr = head->tnptr->right;
            tail->next = NULL;
        }
        printf("%d ", head->tnptr->key);
        temp = head;
        head = head->next;
        free(temp);
    }
    return 1;
}

void free_by_DFS(tnode *ptr)
{
    if (ptr == NULL)
        return;
    free_by_DFS(ptr->left);
    free_by_DFS(ptr->right);
    free(ptr);
}