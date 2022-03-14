#include <stdio.h>
#include <stdlib.h>

#include "print-err.h"
#include "queue.h"

int main(void)
{
	Queue *pQueue = CreateQueue(3U);

	if (pQueue == NULL)
	{
		PRINT_ERR("failed to create a queue");

		return 1;
	}

	EnQueue(pQueue, 10);
	EnQueue(pQueue, 1);
	EnQueue(pQueue, 3);
	EnQueue(pQueue, -29);

	printf("%d\n", DeQueue(pQueue));
	printf("%d\n", DeQueue(pQueue));
	printf("%d\n", DeQueue(pQueue));
	printf("%d\n", Peek(*pQueue));
	printf("%d\n", DeQueue(pQueue));
	printf("%d\n", DeQueue(pQueue));

	DestroyQueue(pQueue);
}
