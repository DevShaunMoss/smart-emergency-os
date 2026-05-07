#include <stdio.h>

#include "log.h"

void WriteLog(char message[])
{
    FILE *file;

    file = fopen("logs.txt", "a");

    if (file == NULL)
    {
        printf("Error opening log file.\n");
        return;
    }

    fprintf(file, "%s\n", message);

    fclose(file);
}