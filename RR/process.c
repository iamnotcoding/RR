#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print-err.h"
#include "process.h"

// the caller is reponsible for freeing returned memory
Processes GetProcesses(FILE *in)
{
	Processes processes = {NULL, 0};

	if (in == NULL)
	{
		PRINT_ERR("in is NULL");

		return processes;
	}

	for (size_t i = 0;; i++)
	{
		int r;

		// increase size of processList
		if (i % 10 == 0)
		{
			processes.processList =
				realloc(processes.processList,
						sizeof *processes.processList * (i / 10 + 1) *
							100); // default size

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
			in, "%u %u %u %u %u", &(processes.processList[i].time),
			&(processes.processList[i].pid), &(processes.processList[i].run),
			&(processes.processList[i].io), &(processes.processList[i].repeat));

		if ((r != 5 && r != EOF) || ferror(in))
		{
			char tempStr[100];

			sprintf(tempStr,
					"processes.txt invalid format at line(approximately) : %zu",
					i + 1);

			PRINT_ERR(tempStr);

			return processes;
		}
		else if (r == EOF)
		{
			break;
		}

		processes.processesNum++;
	}

	return processes;
}

void CloseProcesses(Processes processes)
{
	free(processes.processList);

	processes.processesNum = 0;
}
