#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "print-err.h"
#include "RR/process.h"
#include "RR/RR.h"

#define INPUT_FILE "processes.txt"

int main(void)
{
    FILE *input = fopen(INPUT_FILE, "r");
    Processes processes;

    if (input == NULL)
    {
        char tempStr[100];

        sprintf(tempStr, "cannot open : %s %s", INPUT_FILE, strerror(errno));
        PRINT_ERR(tempStr);
    }

    processes = GetProcesses(input);
} 
