#include <stdio.h>

#include "process.h"
#include "memory.h"
#include "process.h"
#include "memory.h"

int remainingMemory = TOTAL_MEMORY;

void AllocateMemory()
{
    printf("\n=======================================================\n");
    printf("MEMORY ALLOCATION (FIRST FIT)\n");
    printf("=======================================================\n");

    for (int i = 0; i < processCount; i++)
    {
        if (processes[i].memoryRequired <= remainingMemory)
        {
            remainingMemory -= processes[i].memoryRequired;

            printf("Process %s allocated %dMB memory\n",
                   processes[i].name,
                   processes[i].memoryRequired);

            printf("Remaining Memory: %dMB\n\n",
                   remainingMemory);
        }
        else
        {
            printf("Not enough memory for process %s\n",
                   processes[i].name);
        }
    }

    printf("=======================================================\n");
}