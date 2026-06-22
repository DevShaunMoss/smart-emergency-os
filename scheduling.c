#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "scheduling.h"

extern char results[5000];
extern HWND hMainWindow;

void FCFSScheduling()
{
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < processCount; i++)
    {
        if (i == 0)
        {
            processes[i].waitingTime = 0;
        }
        else
        {
            processes[i].waitingTime =
                processes[i - 1].waitingTime +
                processes[i - 1].burstTime;
        }

        processes[i].turnaroundTime =
            processes[i].waitingTime +
            processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    strcpy(results, "FCFS SCHEDULING\n\n");
    sprintf(results + strlen(results),
            "%-4s %-10s %-5s %-5s\n",
            "PID",
            "NAME",
            "WAIT",
            "TURN");

    for (int i = 0; i < processCount; i++)
    {
        sprintf(results + strlen(results),
                "%-4d %-10.10s %-5d %-5d\n",
                processes[i].pid,
                processes[i].name,
                processes[i].waitingTime,
                processes[i].turnaroundTime);
    }

    sprintf(results + strlen(results),
            "\nAverage Waiting: %.2f\nAverage Turnaround: %.2f",
            (float)totalWaitingTime / processCount,
            (float)totalTurnaroundTime / processCount);

    if (hMainWindow != NULL)
    {
        InvalidateRect(hMainWindow, NULL, TRUE);
    }
}

void PriorityScheduling()
{
    Process temp;

    // sort by importance
    for (int i = 0; i < processCount - 1; i++)
    {
        for (int j = i + 1; j < processCount; j++)
        {
            if (processes[i].priority > processes[j].priority)
            {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < processCount; i++)
    {
        if (i == 0)
        {
            processes[i].waitingTime = 0;
        }
        else
        {
            processes[i].waitingTime =
                processes[i - 1].waitingTime +
                processes[i - 1].burstTime;
        }

        processes[i].turnaroundTime =
            processes[i].waitingTime +
            processes[i].burstTime;

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    strcpy(results, "PRIORITY SCHEDULING\n\n");
    sprintf(results + strlen(results),
            "%-4s %-10s %-5s %-5s %-5s\n",
            "PID",
            "NAME",
            "PRIO",
            "WAIT",
            "TURN");

    for (int i = 0; i < processCount; i++)
    {
        sprintf(results + strlen(results),
                "%-4d %-10.10s %-5d %-5d %-5d\n",
                processes[i].pid,
                processes[i].name,
                processes[i].priority,
                processes[i].waitingTime,
                processes[i].turnaroundTime);
    }

    sprintf(results + strlen(results),
            "\nAverage Waiting: %.2f\nAverage Turnaround: %.2f",
            (float)totalWaitingTime / processCount,
            (float)totalTurnaroundTime / processCount);

    if (hMainWindow != NULL)
    {
        InvalidateRect(hMainWindow, NULL, TRUE);
    }
}
