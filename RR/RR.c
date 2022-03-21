#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "../queue/queue.h"
#include "print-err.h"
#include "process.h"

int RunCmp(const void *pA, const void *pB)
{
	int result;

	if (((Process *)pA)->time > ((Process *)pB)->time)
	{
		result = 1;
	}
	else if (((Process *)pA)->time < ((Process *)pB)->time)
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
#if 1
	usleep(s * 1000000);
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

	qsort(processesCopy.processList, processesCopy.processesNum,
		  sizeof *(processesCopy.processList), RunCmp);

	for (size_t i = 0; i < processesCopy.processesNum; i++)
	{
		EnQueue(pJobQueue, processesCopy.processList[i]);
	}

	if (processesCopy.processesNum > 0)
	{
		Process curProcess;

		do
		{
			clock++;

			// if there are no processes to execute
			if (IsQueueEmpty(*pReadyQueue) && IsQueueEmpty(*pJobQueue))
			{
				break;
			}
			// gets a process form the jobqueue if it's time to execute
			else if (!IsQueueEmpty(*pJobQueue) &&
					 clock >= Peek(*pJobQueue).time)
			{
				curProcess = DeQueue(pJobQueue);
			}
			else
			{
				// gets a process from the readyqueue
				if (!IsQueueEmpty(*pReadyQueue))
				{
					curProcess = DeQueue(pReadyQueue);
				}
				else
				{
					// waits for a new process which is in the jobqueue
					continue;
				}
			}

			if (curProcess.repeat > 0)
			{
				unsigned i = 0;

				// if quantum is samller than or equal to repeat, runs quantum
				// times if qunatum is bigger than repeat, runs repeat times
				for (; i < (quantum <= curProcess.repeat ? quantum
														 : curProcess.repeat);
					 i++)
				{
					for (unsigned j = 0; j < curProcess.run; j++)
					{
						fprintf(out, "clock : %u process : %u compute\n", clock,
								curProcess.pid);

						clock++;

						Delay(delaySec);
					}

					for (unsigned j = 0; j < curProcess.io; j++)
					{
						fprintf(out, "clock : %u process : %u IO\n", clock,
								curProcess.pid);

						clock++;

						Delay(delaySec);
					}
				}

				if (quantum <= curProcess.repeat)
				{
					curProcess.repeat -= quantum; // decrease quantum
				}
				else
				{
					curProcess.repeat = 0;
				}

				EnQueue(pJobQueue, curProcess);
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

				fprintf(out, "clock : %u process : %u ended\n", clock,
						curProcess.pid);
			}

		} while (true);
	}

	CloseProcesses(processesCopy);
	DestroyQueue(pJobQueue);
	DestroyQueue(pReadyQueue);
}
