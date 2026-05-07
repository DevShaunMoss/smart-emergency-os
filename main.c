#include <windows.h>

#include "process.h"
#include "scheduling.h"
#include "memory.h"
#include "log.h"
#include <stdio.h>
#include <string.h>

#define BTN_FCFS 1
#define BTN_PRIORITY 2
#define BTN_MEMORY 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char output[5000] = "";

void UpdateOutput()
{
    strcpy(output,
    "SMART EMERGENCY RESPONSE SYSTEM\n\n");

    strcat(output,
    "Processes Loaded:\n\n");

    for (int i = 0; i < processCount; i++)
    {
        char buffer[256];

        sprintf(buffer,
        "PID: %d | %s | Priority: %d | Burst: %d | Memory: %dMB | State: %s\n",
        processes[i].pid,
        processes[i].name,
        processes[i].priority,
        processes[i].burstTime,
        processes[i].memoryRequired,
        processes[i].state);

        strcat(output, buffer);
    }
}

int WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPrevInst,
                   LPSTR args,
                   int ncmdshow)
{
    WNDCLASS wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = "MainWindow";
    wc.lpfnWndProc = WindowProcedure;

    RegisterClass(&wc);

    CreateWindow("MainWindow",
                 "Smart Emergency Response System",
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 100,
                 100,
                 900,
                 600,
                 NULL,
                 NULL,
                 NULL,
                 NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd,
                                 UINT msg,
                                 WPARAM wp,
                                 LPARAM lp)
{
    switch(msg)
    {
        case WM_CREATE:

            AddProcess("Fire", 1, 5, 200);
            AddProcess("Ambulance", 2, 3, 150);
            AddProcess("Police", 3, 4, 100);

            UpdateOutput();

            CreateWindow("BUTTON",
                         "Run FCFS",
                         WS_VISIBLE | WS_CHILD,
                         50,
                         450,
                         150,
                         40,
                         hwnd,
                         (HMENU)BTN_FCFS,
                         NULL,
                         NULL);

            CreateWindow("BUTTON",
                         "Priority Scheduling",
                         WS_VISIBLE | WS_CHILD,
                         250,
                         450,
                         180,
                         40,
                         hwnd,
                         (HMENU)BTN_PRIORITY,
                         NULL,
                         NULL);

            CreateWindow("BUTTON",
                         "Allocate Memory",
                         WS_VISIBLE | WS_CHILD,
                         500,
                         450,
                         180,
                         40,
                         hwnd,
                         (HMENU)BTN_MEMORY,
                         NULL,
                         NULL);

            break;

        case WM_COMMAND:

            switch(wp)
            {
                case BTN_FCFS:

                    FCFSScheduling();
                    WriteLog("FCFS Scheduling Executed");

                    MessageBox(hwnd,
                               "FCFS Scheduling Executed.\nCheck terminal for results.",
                               "Success",
                               MB_OK);

                    break;

                case BTN_PRIORITY:

                    PriorityScheduling();
                    WriteLog("Priority Scheduling Executed");

                    MessageBox(hwnd,
                               "Priority Scheduling Executed.\nCheck terminal for results.",
                               "Success",
                               MB_OK);

                    break;

                case BTN_MEMORY:

                    AllocateMemory();
                    WriteLog("Memory Allocation Executed");

                    MessageBox(hwnd,
                               "Memory Allocation Executed.\nCheck terminal for results.",
                               "Success",
                               MB_OK);

                    break;
            }

            break;

        case WM_PAINT:
{
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(hwnd, &ps);

    RECT rect;

    rect.left = 50;
    rect.top = 50;
    rect.right = 800;
    rect.bottom = 400;

    DrawText(hdc,
             output,
             -1,
             &rect,
             DT_LEFT);

    EndPaint(hwnd, &ps);

    break;
}
        case WM_DESTROY:

            PostQuitMessage(0);

            break;
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}