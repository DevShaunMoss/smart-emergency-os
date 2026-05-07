#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESSES 50

typedef struct
{
    int pid;
    char name[50];
    int priority;
    int burstTime;
    int memoryRequired;

    int waitingTime;
    int turnaroundTime;

    char state[20];

} Process;

extern Process processes[MAX_PROCESSES];
extern int processCount;

// functions decs
void AddProcess(char name[], int priority, int burstTime, int memoryRequired);
void DisplayProcesses();

#endif