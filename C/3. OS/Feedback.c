// #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define qNum 5
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
void insertProcess(PROCESS *target, PROCESS **head, PROCESS **tail, int qLevel);
PROCESS *deleteHead(PROCESS **head, PROCESS **tail, int qLevel);
bool checkNumOfPrscToRun(PROCESS program, int elpsTime, PROCESS **head, int qLevel);

int main()
{
    FILE *pfile;
    PROCESS program;
    PROCESS *temp;
    PROCESS *head[qNum], *tail[qNum];
    int qLevel, duration, elpsTime; // level of queue, duration of process, elapsed time

    pfile = fopen("input.txt", "r");
    if (pfile == NULL)
    {
        printf("file not found\n");
        system("pause");
        return 0;
    }
    for (qLevel = 0; qLevel < qNum; qLevel++)
    {
        head[qLevel] = NULL;
        tail[qLevel] = NULL;
    }
    duration = 0;
    elpsTime = 0;

    program = readFileData(pfile); // read program from .txt file
    while (1)
    {
        while (head[qLevel] == NULL && qLevel < qNum) // Check the highest level queue with processes
            qLevel++;

        if (program.id < 0 && qLevel >= qNum) // if there is no process to run
            break;

        while (program.id >= 0 && program.arvTime <= elpsTime)
        {
            temp = createProcess(program); // create new process
            if (temp != NULL)
            {
                insertProcess(temp, head, tail, 0); // insert new process in tail of 0th queue
                qLevel = 0;                         // point out 0th queue
                program = readFileData(pfile);      // read program from .txt file
            }
        }

        if (qLevel < qNum)
        {
            (head[qLevel]->remainSrv)--; // processing
            duration++;
            elpsTime++;

            if (head[qLevel]->remainSrv <= 0 || duration >= quantum) // check 'remain service time, duration' of head[qLevel] process(current working process)
            {
                temp = deleteHead(head, tail, qLevel); // delete head[qLevel] process from qLevel queue
                duration = 0;

                if (temp->remainSrv > 0) // check 'remain service time' of deleted process
                {
                    if (qLevel < qNum - 1 && checkNumOfPrscToRun(program, elpsTime, head, qLevel)) // Check if there is a queue level to go down && check number of processes to run in next iteration. 0 -> timeout process only  /  1 -> 2 or more
                        insertProcess(temp, head, tail, qLevel + 1);                               // insert timeout process in tail of qLevel + 1 queue
                    else
                        insertProcess(temp, head, tail, qLevel); // insert timeout process in tail of qLevel queue
                }
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

void insertProcess(PROCESS *target, PROCESS **head, PROCESS **tail, int qLevel)
{
    if (head[qLevel] != NULL)
    {
        tail[qLevel]->next = target;
        tail[qLevel] = target;
    }
    else
    {
        head[qLevel] = target;
        tail[qLevel] = target;
    }
}

PROCESS *deleteHead(PROCESS **head, PROCESS **tail, int qLevel)
{
    PROCESS *deleted;

    deleted = head[qLevel];
    head[qLevel] = head[qLevel]->next;
    deleted->next = NULL;
    if (head[qLevel] == NULL)
        tail[qLevel] = NULL;

    return deleted;
}

bool checkNumOfPrscToRun(PROCESS program, int elpsTime, PROCESS **head, int qLevel)
{
    bool isMany;

    if (program.id >= 0 && program.arvTime <= elpsTime)
        isMany = 1;
    else
    {
        isMany = 0;
        for (int i = qLevel; i < qNum; i++)
        {
            if (head[i] != NULL)
            {
                isMany = 1;
                break;
            }
        }
    }

    return isMany;
}