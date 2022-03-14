#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print-err.h"
#include "queue.h"

/* ####### miniemum c version >= c99 ####### */

// functions defeinitieon

// the caller is reponsible for freeing memory
Queue *CreateQueue(size_t size)
{
	Queue *pQueue = malloc(sizeof *pQueue);

	if (pQueue == NULL)
	{
		char tempStr[100];

		sprintf(tempStr, "pQueue allocation failed : %s", strerror(errno));

		PRINT_ERR(tempStr);

		return NULL;
	}

	pQueue->arr = malloc(sizeof(QData) * size);

	if (pQueue->arr == NULL)
	{
		char tempStr[100];

		sprintf(tempStr, "arr allocation failed : %s", strerror(errno));

		PRINT_ERR(tempStr);

		free(pQueue);

		return NULL;
	}

	pQueue->elementNum = 0;
	pQueue->maxSize = size;

	return pQueue;
}

void DestroyQueue(Queue *pQueue)
{
	// exception handling
	if (pQueue == NULL)
	{
		PRINT_ERR("pQueue is NULL");

		return;
	}

	if (pQueue->arr == NULL)
	{
		PRINT_ERR("arr is NULL");

		return;
	}

	free(pQueue->arr);
	free(pQueue);
}

bool IsQueueEmpty(Queue queue)
{
	bool result = false;

	if (queue.elementNum == 0)
	{
		result = true;
	}

	return result;
}

bool IsQueueFull(Queue queue)
{
	bool result = false;

	if (queue.elementNum == queue.maxSize)
	{
		result = true;
	}

	return result;
}

void AssignQData(QData *dest, QData orign)
{
	// exception handling
	if (dest == NULL)
	{
		PRINT_ERR("dest is NULL");

		return;
	}

	*dest = orign;
}

// returns first element's data
QData Peek(Queue queue)
{
	QData returnQData;

	// initalize returnQData
	memset(&returnQData, -1, sizeof returnQData);

	if (IsQueueEmpty(queue))
	{
		PRINT_ERR("queue is empty");

		return returnQData;
	}

	AssignQData(&returnQData, queue.arr[0]);

	return returnQData;
}

void EnQueue(Queue *pQueue, QData data)
{
	// exception handling
	if (pQueue == NULL)
	{
		PRINT_ERR("pQueue is NULL");

		return;
	}

	if (pQueue->arr == NULL)
	{
		PRINT_ERR("arr is NULL");

		return;
	}

	if (IsQueueFull(*pQueue))
	{
		PRINT_ERR("queue is full");

		return;
	}

	AssignQData(&(pQueue->arr[pQueue->elementNum++]), data);
}

// returns first element's data
QData DeQueue(Queue *pQueue)
{
	QData returnQData;

	// initalize returnQData
	memset(&returnQData, -1, sizeof returnQData);

	// exception handling
	if (pQueue == NULL)
	{
		PRINT_ERR("pQueue is NULL");

		return returnQData;
	}

	if (pQueue->arr == NULL)
	{
		PRINT_ERR("arr is NULL");

		return returnQData;
	}

	if (IsQueueEmpty(*pQueue))
	{
		PRINT_ERR("queue is empty");

		return returnQData;
	}

	AssignQData(&returnQData, Peek(*pQueue));

	for (size_t i = 0; i < pQueue->elementNum - 1; i++)
	{
		AssignQData(&(pQueue->arr[i]), pQueue->arr[i + 1]);
	}

	pQueue->elementNum--;

	return returnQData;
}
 
