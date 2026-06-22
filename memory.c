#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "memory.h"

extern char results[5000];
extern HWND hMainWindow;

int remainingMemory = TOTAL_MEMORY;

void AllocateMemory()
{
    strcpy(results, "MEMORY ALLOCATION (FIRST FIT)\n\n");
    sprintf(results + strlen(results),
            "%-10s %-6s %-9s %-6s\n",
            "PROCESS",
            "REQ",
            "STATUS",
            "LEFT");

    for (int i = 0; i < processCount; i++)
    {
        if (processes[i].memoryRequired <= remainingMemory)
        {
            remainingMemory -= processes[i].memoryRequired;

            sprintf(results + strlen(results),
                    "%-10.10s %-6d %-9s %-6d\n",
                    processes[i].name,
                    processes[i].memoryRequired,
                    "Allocated",
                    remainingMemory);
        }
        else
        {
            sprintf(results + strlen(results),
                    "%-10.10s %-6d %-9s %-6d\n",
                    processes[i].name,
                    processes[i].memoryRequired,
                    "Denied",
                    remainingMemory);
        }
    }

    if (hMainWindow != NULL)
    {
        InvalidateRect(hMainWindow, NULL, TRUE);
    }
}
