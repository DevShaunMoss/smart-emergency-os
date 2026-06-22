#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "scheduling.h"
#include "memory.h"
#include "log.h"

#define BTN_ADD_PROCESS 1
#define BTN_FCFS 2
#define BTN_PRIORITY 3
#define BTN_MEMORY 4

HWND hName;
HWND hPriority;
HWND hBurst;
HWND hMemory;
HWND hMainWindow = NULL;

char output[10000] = "";
char results[5000] = "Results will appear here.";

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void UpdateOutput()
{
    strcpy(output,
           "SMART EMERGENCY RESPONSE SYSTEM\n\n");

    strcat(output,
           "PID\tNAME\tPRIORITY\tBURST\tMEMORY\tSTATE\n");

    strcat(output,
           "------------------------------------------------------------\n");

    for (int i = 0; i < processCount; i++)
    {
        char buffer[256];

        sprintf(buffer,
                "%d\t%s\t%d\t\t%d\t%dMB\t%s\n",
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
                   int nCmdShow)
{
    WNDCLASS wc = {0};

    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpfnWndProc = WindowProcedure;
    wc.lpszClassName = "MainWindow";

    RegisterClass(&wc);

    CreateWindow(
        "MainWindow",
        "Smart Emergency Response System",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100,
        100,
        1100,
        700,
        NULL,
        NULL,
        hInst,
        NULL);

    MSG msg;

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
    switch (msg)
    {
    case WM_CREATE:

        hMainWindow = hwnd;

        CreateWindow(
            "STATIC",
            "Task Name:",
            WS_VISIBLE | WS_CHILD,
            20, 20, 80, 25,
            hwnd, NULL, NULL, NULL);

        hName = CreateWindow(
            "EDIT",
            "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            110, 20, 150, 25,
            hwnd, NULL, NULL, NULL);

        CreateWindow(
            "STATIC",
            "Priority:",
            WS_VISIBLE | WS_CHILD,
            280, 20, 60, 25,
            hwnd, NULL, NULL, NULL);

        hPriority = CreateWindow(
            "EDIT",
            "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            350, 20, 60, 25,
            hwnd, NULL, NULL, NULL);

        CreateWindow(
            "STATIC",
            "Burst:",
            WS_VISIBLE | WS_CHILD,
            430, 20, 60, 25,
            hwnd, NULL, NULL, NULL);

        hBurst = CreateWindow(
            "EDIT",
            "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            490, 20, 60, 25,
            hwnd, NULL, NULL, NULL);

        CreateWindow(
            "STATIC",
            "Memory:",
            WS_VISIBLE | WS_CHILD,
            570, 20, 60, 25,
            hwnd, NULL, NULL, NULL);

        hMemory = CreateWindow(
            "EDIT",
            "",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            640, 20, 80, 25,
            hwnd, NULL, NULL, NULL);

        CreateWindow(
            "BUTTON",
            "Add Process",
            WS_VISIBLE | WS_CHILD,
            750, 20, 120, 30,
            hwnd,
            (HMENU)BTN_ADD_PROCESS,
            NULL,
            NULL);

        CreateWindow(
            "BUTTON",
            "Run FCFS",
            WS_VISIBLE | WS_CHILD,
            50, 580, 150, 40,
            hwnd,
            (HMENU)BTN_FCFS,
            NULL,
            NULL);

        CreateWindow(
            "BUTTON",
            "Priority Scheduling",
            WS_VISIBLE | WS_CHILD,
            250, 580, 180, 40,
            hwnd,
            (HMENU)BTN_PRIORITY,
            NULL,
            NULL);

        CreateWindow(
            "BUTTON",
            "Allocate Memory",
            WS_VISIBLE | WS_CHILD,
            500, 580, 180, 40,
            hwnd,
            (HMENU)BTN_MEMORY,
            NULL,
            NULL);

        UpdateOutput();

        break;

    case WM_COMMAND:

        switch (LOWORD(wp))
        {
        case BTN_ADD_PROCESS:
        {
            char name[50];
            char priorityStr[20];
            char burstStr[20];
            char memoryStr[20];

            GetWindowText(hName, name, 50);
            GetWindowText(hPriority, priorityStr, 20);
            GetWindowText(hBurst, burstStr, 20);
            GetWindowText(hMemory, memoryStr, 20);

            if (strlen(name) == 0)
            {
                MessageBox(
                    hwnd,
                    "Please enter a task name.",
                    "Input Error",
                    MB_OK);

                break;
            }

            AddProcess(
                name,
                atoi(priorityStr),
                atoi(burstStr),
                atoi(memoryStr));

            UpdateOutput();

            InvalidateRect(hwnd, NULL, TRUE);

            SetWindowText(hName, "");
            SetWindowText(hPriority, "");
            SetWindowText(hBurst, "");
            SetWindowText(hMemory, "");

            break;
        }

        case BTN_FCFS:

            FCFSScheduling();
            InvalidateRect(hwnd, NULL, TRUE);

            MessageBox(
                hwnd,
                "FCFS Scheduling Executed.\nCheck results panel.",
                "Success",
                MB_OK);

            break;

        case BTN_PRIORITY:

            PriorityScheduling();

            UpdateOutput();
            InvalidateRect(hwnd, NULL, TRUE);

            MessageBox(
                hwnd,
                "Priority Scheduling Executed.\nCheck results panel.",
                "Success",
                MB_OK);

            break;

        case BTN_MEMORY:

            AllocateMemory();
            InvalidateRect(hwnd, NULL, TRUE);

            MessageBox(
                hwnd,
                "Memory Allocation Executed.\nCheck results panel.",
                "Success",
                MB_OK);

            break;
        }

        break;

    case WM_PAINT:
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // Title
    TextOut(hdc, 20, 80,
            "SMART EMERGENCY RESPONSE SYSTEM",
            31);

    // Table headers
    TextOut(hdc, 20, 130, "PID", 3);
    TextOut(hdc, 80, 130, "NAME", 4);
    TextOut(hdc, 250, 130, "PRIORITY", 8);
    TextOut(hdc, 380, 130, "BURST", 5);
    TextOut(hdc, 500, 130, "MEMORY", 6);
    TextOut(hdc, 650, 130, "STATE", 5);

    MoveToEx(hdc, 20, 150, NULL);
    LineTo(hdc, 800, 150);

    int y = 180;

    for(int i = 0; i < processCount; i++)
    {
        char buffer[100];

        sprintf(buffer, "%d", processes[i].pid);
        TextOut(hdc, 20, y, buffer, strlen(buffer));

        TextOut(hdc,
                80,
                y,
                processes[i].name,
                strlen(processes[i].name));

        sprintf(buffer, "%d", processes[i].priority);
        TextOut(hdc, 250, y, buffer, strlen(buffer));

        sprintf(buffer, "%d", processes[i].burstTime);
        TextOut(hdc, 380, y, buffer, strlen(buffer));

        sprintf(buffer,
                "%d MB",
                processes[i].memoryRequired);
        TextOut(hdc, 500, y, buffer, strlen(buffer));

        TextOut(hdc,
                650,
                y,
                processes[i].state,
                strlen(processes[i].state));

        y += 30;
    }

    TextOut(hdc, 820, 80, "RESULTS", 7);
    Rectangle(hdc, 810, 110, 1060, 550);

    HFONT resultsFont = CreateFont(
        14,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        FIXED_PITCH | FF_MODERN,
        "Consolas");
    HFONT oldFont = NULL;

    if (resultsFont != NULL)
    {
        oldFont = (HFONT)SelectObject(hdc, resultsFont);
    }

    RECT resultsRect = {820, 120, 1050, 540};
    DrawText(hdc, results, -1, &resultsRect,
             DT_LEFT | DT_TOP | DT_WORDBREAK);

    if (oldFont != NULL)
    {
        SelectObject(hdc, oldFont);
    }

    if (resultsFont != NULL)
    {
        DeleteObject(resultsFont);
    }

    EndPaint(hwnd, &ps);
    break;
}

    case WM_DESTROY:

        PostQuitMessage(0);

        break;
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}
