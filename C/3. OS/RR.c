// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define quantum 1

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
void insertProcess(PROCESS *target, PROCESS **head, PROCESS **tail);
PROCESS *deleteHead(PROCESS **head, PROCESS **tail);

int main()
{
    FILE *pfile;
    PROCESS program;
    PROCESS *head, *tail, *temp, *timeout;
    int duration, elpsTime; // duration of process, elapsed time

    pfile = fopen("input.txt", "r");
    if (pfile == NULL)
    {
        printf("file not found\n");
        system("pause");
        return 0;
    }
    head = NULL;
    tail = NULL;
    timeout = NULL;
    duration = 0;
    elpsTime = 0;

    program = readFileData(pfile); // read program from .txt file
    while (program.id >= 0 || head != NULL || timeout != NULL)
    {
        while (program.id >= 0 && program.arvTime <= elpsTime)
        {
            temp = createProcess(program); // create new process
            if (temp != NULL)
            {
                insertProcess(temp, &head, &tail); // insert new process in tail of queue
                program = readFileData(pfile);     // read program from .txt file
            }
        }

        if (timeout != NULL)
        {
            insertProcess(timeout, &head, &tail); // insert timeout process in tail of queue
            timeout = NULL;
        }

        if (head != NULL)
        {
            (head->remainSrv)--; // processing
            duration++;
            elpsTime++;

            if (head->remainSrv <= 0 || duration >= quantum) // check 'remain service time, duration' of head process(current working process)
            {
                temp = deleteHead(&head, &tail); // delete head process from queue
                duration = 0;

                if (temp->remainSrv > 0) // check 'remain service time' of deleted process
                    timeout = temp;      // point out timeout process
                else
                {
                    printf("process end > ID : %d, arrive time : %d, service time : %d, end time : %d, return time : %d, normalized return time : %.2lf\n", temp->id, temp->arvTime, temp->srvTime, elpsTime, elpsTime - temp->arvTime, (double)(elpsTime - temp->arvTime) / temp->srvTime);
                    free(temp);
                }
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

void insertProcess(PROCESS *target, PROCESS **head, PROCESS **tail)
{
    if (*head != NULL)
    {
        (*tail)->next = target;
        *tail = target;
    }
    else
    {
        *head = target;
        *tail = target;
    }
}

PROCESS *deleteHead(PROCESS **head, PROCESS **tail)
{
    PROCESS *deleted;

    deleted = *head;
    *head = (*head)->next;
    deleted->next = NULL;
    if (*head == NULL)
        *tail = NULL;

    return deleted;
}