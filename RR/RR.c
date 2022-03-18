#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for sleep function

// if unix (or linux)
#ifdef __unix__

#include <unistd.h>

// if windows
#elif defined(_WIN32) || defined(WIN32)

#include <Windows.h>

// if unkown os
#else

#include <time.h>

#endif

#include "../queue/queue.h"
#include "print-err.h"
#include "process.h"

// the caller is reponsible for freeing returned memory
// returns NULL if failed
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
							10); // default size

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

			sprintf(tempStr, "processes.txt invalid format at line : %zu", i);

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

int RunCmp(const void *pA, const void *pB)
{
	int result;

	if (((Process *)pA)->run > ((Process *)pB)->run)
	{
		result = 1;
	}
	else if (((Process *)pA)->run < ((Process *)pB)->run)
	{
		result = -1;
	}
	else
	{
		result = 0;
	}

	return result;
}

void Delay(double s)
{
	#if 0
#ifdef __unix__

	usleep(s * 100000000);

#elif defined(_WIN32) || defined(_WIN64)

	Sleep(s * 1000);

#else

	// does busy waiting
	time_t start, end;

	start = clock();

	while ((double)(start - clock()) / CLOCKS_PER_SEC <= s)
	{
	}
#endif
#endif
}

void RR(FILE *out, Processes processes, unsigned quantum, double delaySec)
{
	Processes processesCopy;
	Queue *pJobQueue = CreateQueue(processes.processesNum);
	Queue *pReadyQueue = CreateQueue(processes.processesNum);
	unsigned clock = 0;

	if (pJobQueue == NULL)
	{
		PRINT_ERR("CreateQueue() failed");

		return;
	}

	processesCopy.processList =
		malloc(sizeof *(processes.processList) * processes.processesNum);

	if (processesCopy.processList == NULL)
	{
		char tempStr[100];

		sprintf(tempStr, "processesCopy.processList allocation failed : %s",
				strerror(errno));

		PRINT_ERR(tempStr);

		return;
	}

	memcpy(processesCopy.processList, processes.processList,
		   sizeof *processes.processList * processes.processesNum);

	processesCopy.processesNum = processes.processesNum;

	// going to use processesCopy instead of processes from now on

	qsort(processes.processList, processes.processesNum,
		  sizeof *(processes.processList), RunCmp);

	for (size_t i = 0; i < processesCopy.processesNum; i++)
	{
		EnQueue(pJobQueue, processesCopy.processList[i]);
	}

	puts("hi");

	if (processesCopy.processesNum > 0)
	{
		Process curProcess;

		do
		{
			clock++;

			if (!IsQueueEmpty(*pJobQueue) && clock >= Peek(*pJobQueue).time)
			{
				curProcess = DeQueue(pJobQueue);
			}
			else
			{
				if (!IsQueueEmpty(*pReadyQueue))
				{
					curProcess = DeQueue(pReadyQueue);
				}
				else
				{
					continue;
				}
			}

			if (IsQueueEmpty(*pReadyQueue) && IsQueueEmpty(*pJobQueue))
			{
				break;
			}

			if (curProcess.repeat > 0)
			{
				for (unsigned i = 0; i < curProcess.run; i++)
				{
					fprintf(out, "clock : %u process : %u compute\n", clock,
							curProcess.pid);

					clock++;

					Delay(delaySec);
				}

				for (unsigned i = 0; i < curProcess.io; i++)
				{
					fprintf(out, "clock : %u process : %u I/O\n", clock,
							curProcess.pid);

					clock++;

					Delay(delaySec);
				}

				curProcess.repeat--;
				// puts in the queue because the process hasn't been fnished yet
				EnQueue(pReadyQueue, curProcess);
			}
			else
			{
				// this is the last phase

				for (unsigned i = 0; i < curProcess.run; i++)
				{
					fprintf(out, "clock : %u process : %u compute\n", clock,
							curProcess.pid);
				
					clock++;

					Delay(delaySec);
				}
			}

		} while (true);
	}
}
