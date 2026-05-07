#include <stdio.h>
#include <string.h>

#include "process.h"
#include "scheduling.h"

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

    printf("\n=======================================================\n");
    printf("FCFS SCHEDULING\n");
    printf("=======================================================\n");

    printf("PID\tNAME\t\tWAITING\t\tTURNAROUND\n");

    for (int i = 0; i < processCount; i++)
    {
        printf("%d\t%s\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].name,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n",
           (float)totalWaitingTime / processCount);

    printf("Average Turnaround Time: %.2f\n",
           (float)totalTurnaroundTime / processCount);
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

    printf("\n=======================================================\n");
    printf("PRIORITY SCHEDULING\n");
    printf("=======================================================\n");

    printf("PID\tNAME\t\tPRIORITY\tWAIT\tTURNAROUND\n");

    for (int i = 0; i < processCount; i++)
    {
        printf("%d\t%s\t\t%d\t\t%d\t%d\n",
               processes[i].pid,
               processes[i].name,
               processes[i].priority,
               processes[i].waitingTime,
               processes[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n",
           (float)totalWaitingTime / processCount);

    printf("Average Turnaround Time: %.2f\n",
           (float)totalTurnaroundTime / processCount);

    printf("=======================================================\n");
}