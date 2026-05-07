#include <stdio.h>
#include <string.h>
#include "process.h"
#include "log.h"

Process processes[MAX_PROCESSES];
int processCount = 0;

void AddProcess(char name[], int priority, int burstTime, int memoryRequired)
{
    if (processCount >= MAX_PROCESSES)
    {
        printf("Process list full!\n");
        return;
    }

    Process newProcess;

    newProcess.pid = processCount + 1;

    strcpy(newProcess.name, name);

    newProcess.priority = priority;
    newProcess.burstTime = burstTime;
    newProcess.memoryRequired = memoryRequired;

    newProcess.waitingTime = 0;
    newProcess.turnaroundTime = 0;

    strcpy(newProcess.state, "Ready");

    processes[processCount] = newProcess;

    processCount++;

    WriteLog("Process Created");
    printf("Process added successfully!\n");
}

void DisplayProcesses()
{
    if (processCount == 0)
    {
        printf("No processes available.\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("PID\tNAME\t\tPRIORITY\tBURST\tMEMORY\tSTATE\n");
    printf("===============================================================\n");

    for (int i = 0; i < processCount; i++)
    {
        printf("%d\t%s\t\t%d\t\t%d\t%d\t%s\n",
               processes[i].pid,
               processes[i].name,
               processes[i].priority,
               processes[i].burstTime,
               processes[i].memoryRequired,
               processes[i].state);
    }

    printf("===============================================================\n");
}