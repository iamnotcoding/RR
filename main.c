#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RR/RR.h"
#include "RR/process.h"
#include "print-err.h"

#define INPUT_FILE "processes.txt"
#define OUTPUT_FILE "result.txt"

//#define DELAY 0.1
#define DELAY 0

int main(void)
{
	unsigned quantum;
	FILE *input, *output;

	input = fopen(INPUT_FILE, "r");

	Processes processes;

	if (input == NULL)
	{
		char tempStr[100];

		sprintf(tempStr, "cannot open : %s %s", INPUT_FILE, strerror(errno));

		PRINT_ERR(tempStr);
	}

	output = fopen(OUTPUT_FILE, "w+");

	if (output == NULL)
	{
		char tempStr[100];

		sprintf(tempStr, "cannot open : %s %s", OUTPUT_FILE, strerror(errno));

		PRINT_ERR(tempStr);
	}

	processes = GetProcesses(input);

	printf("quantum : ");

	scanf("%u", &quantum);

	// RR(stdout, processes, quantum, DELAY);
	RR(output, processes, quantum, DELAY);

	CloseProcesses(processes);

	fclose(input);
	fclose(output);
}
