// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int id;
    int arvTime;   // arrive time
    int srvTime;   // service time
    int remainSrv; // remain service time
    struct process *next;
} PROCESS;

PROCESS readFileData(FILE *pfile);
PROCESS *createProcess(PROCESS program);
PROCESS *searchPosition(PROCESS *target, PROCESS *head);
void insertProcess(PROCESS *target, PROCESS *position, PROCESS **head);

int main()
{
    FILE *pfile;
    PROCESS program;
    PROCESS *head, *temp, *pos;
    int elpsTime; // elapsed time

    pfile = fopen("input.txt", "r");
    if (pfile == NULL)
    {
        printf("file not found\n");
        system("pause");
        return 0;
    }
    head = NULL;
    elpsTime = 0;

    program = readFileData(pfile); // read program from .txt file
    while (program.id >= 0 || head != NULL)
    {
        while (program.id >= 0 && program.arvTime <= elpsTime)
        {
            temp = createProcess(program); // create new process
            if (temp != NULL)
            {
                pos = searchPosition(temp, head); // search insert position
                insertProcess(temp, pos, &head);  // insert new process in array
                program = readFileData(pfile);    // read program from .txt file
            }
        }

        if (head != NULL)
        {
            (head->remainSrv)--; // processing
            elpsTime++;

            if (head->remainSrv <= 0) // check 'remain service time' of head process(current working process)
            {
                // delete head process from array
                temp = head;
                head = head->next;

                printf("process end > ID : %d, arrive time : %d, service time : %d, end time : %d, return time : %d, normalized return time : %.2lf\n", temp->id, temp->arvTime, temp->srvTime, elpsTime, elpsTime - temp->arvTime, (double)(elpsTime - temp->arvTime) / temp->srvTime);
                free(temp);
            }
        }
        else
            elpsTime++;
    }

    fclose(pfile);
    system("PAUSE");
    return 0;
}

PROCESS readFileData(FILE *pfile)
{
    PROCESS program;

    program.id = -1;
    program.arvTime = -1;
    program.srvTime = -1;

    fscanf(pfile, "%d,%d,%d\n", &program.id, &program.arvTime, &program.srvTime);
    if (program.id < 0 || program.arvTime < 0 || program.srvTime <= 0)
        program.id = -1;

    return program;
}

PROCESS *createProcess(PROCESS program)
{
    PROCESS *newPrcs;

    newPrcs = (PROCESS *)malloc(sizeof(PROCESS));
    if (newPrcs != NULL)
    {
        newPrcs->id = program.id;
        newPrcs->arvTime = program.arvTime;
        newPrcs->srvTime = program.srvTime;
        newPrcs->remainSrv = program.srvTime;
        newPrcs->next = NULL;
    }

    return newPrcs;
}

PROCESS *searchPosition(PROCESS *target, PROCESS *head)
{
    PROCESS *prePtr = NULL;
    PROCESS *currPtr = head;

    while (currPtr != NULL)
    {
        if (target->remainSrv < currPtr->remainSrv)
            break;
        prePtr = currPtr;
        currPtr = currPtr->next;
    }

    return prePtr;
}

void insertProcess(PROCESS *target, PROCESS *position, PROCESS **head)
{
    if (position != NULL)
    {
        target->next = position->next;
        position->next = target;
    }
    else if (*head != NULL)
    {
        target->next = *head;
        *head = target;
    }
    else
        *head = target;
}