#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RR/RR.h"
#include "RR/process.h"
#include "print-err.h"

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
	RR(stdout, processes, 3, 0);
	
	free(processes.processList);
}

