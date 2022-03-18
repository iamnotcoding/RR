#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RR/RR.h"
#include "RR/process.h"
#include "print-err.h"

#define INPUT_FILE "processes.txt"
#define OUTPUT_FILE "result.txt"
int main(void)
{
	FILE *input = fopen(INPUT_FILE, "r");
	FILE *output = fopen(OUTPUT_FILE, "w+");

	Processes processes;

	if (input == NULL)
	{
		char tempStr[100];

		sprintf(tempStr, "cannot open : %s %s", INPUT_FILE, strerror(errno));

		PRINT_ERR(tempStr);
	}

	processes = GetProcesses(input);

	RR(output, processes, 3, 0);

	//free(output.processList);
}
