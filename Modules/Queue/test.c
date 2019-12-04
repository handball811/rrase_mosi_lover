#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
	int num;
	queue q = GenerateQueue(sizeof(num));
	printf("is Empty? -> %d\n", QueueEmpty(&q));
	num = 100;
	QueuePush(&q, &num);
	printf("is Empty? -> %d\n", QueueEmpty(&q));
	num = 200;
	QueuePush(&q, &num);
	num = 300;
	QueuePush(&q, &num);
	num = 400;
	QueuePush(&q, &num);
	DebugQueue(&q);
	printf("poped: %d\n", *((int*)QueuePop(&q)));
	printf("poped: %d\n", *((int*)QueuePop(&q)));
	num = 100;
	QueuePush(&q, &num);
	DebugQueue(&q);
	num = 200;
	QueuePush(&q, &num);
	DebugQueue(&q);
	num = 300;
	QueuePush(&q, &num);
	num = 400;
	QueuePush(&q, &num);
	DebugQueue(&q);

	FreeQueue(&q);

	return 0;
}