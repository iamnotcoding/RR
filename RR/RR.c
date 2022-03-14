#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../queue/queue.h"
#include "print-err.h"
#include "process.h"

// the caller is reponsible for freeing returned memory
// returns NULL if failed
Processes GetProcesses(FILE *fp)
{
	Processes processes = {NULL, 0};

	if (fp == NULL)
	{
		PRINT_ERR("fp is NULL");

		return processes;
	}

	for (size_t i = 0;; i++)
	{
		int r;

		// increase size of processList
		if (i % 10 == 0)
		{
			processes.processList = realloc(processes.processList,
											sizeof *processes.processList *
												(i / 10 + 1) * 10); // default size

			if (processes.processList == NULL)
			{
				char tempStr[100];

				sprintf(tempStr, "processList allocation failed : %s",
						strerror(errno));

				PRINT_ERR(tempStr);

				return processes;
			}
		}

		r = fscanf(
			fp, "%u %u %u %u %u", &(processes.processList[i].time),
			&(processes.processList[i].pid), &(processes.processList[i].run),
			&(processes.processList[i].io), &(processes.processList[i].repeat));

		if ((r != 5 && r != EOF) || ferror(fp))
		{
			char tempStr[100];

			sprintf(tempStr, "processes.txt invalid format at line : %zu", i);

			PRINT_ERR(tempStr);

			return processes;
		}
		else if (r == EOF)
		{
			break;
		}
	}

	return processes;
}