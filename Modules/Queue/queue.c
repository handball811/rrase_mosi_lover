#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

queue GenerateQueue(size_t item_size)
{
	queue qu;
	qu.memory = malloc(item_size * 4);
	qu.max_size = 4;
	qu.front = 0;
	qu.bottom = 0;
	qu.size = 0;
	qu.item_size = item_size;
	return qu;
}

void QueuePush(queue *q, void* item)
{
	if(q->size == q->max_size)
	{
		void* tmp;
		if((tmp=realloc(q->memory, q->item_size*q->max_size<<1))==NULL)
		{
			FreeQueue(q);
			exit(1);
		}
		q->memory = tmp;
		memcpy(q->memory + q->max_size * q->item_size, q->memory, q->bottom * q->item_size);
		q->bottom += q->max_size;
		q->max_size <<= 1;
	}
	memcpy(q->memory+(q->bottom++ * q->item_size), item, q->item_size);
	q->bottom %= q->max_size;
	++q->size;
}

void* QueuePop(queue *q)
{
	if(QueueEmpty(q))
		return NULL;
	void* ret = q->memory + (q->front++ * q->item_size);
	q->front %= q->max_size;
	--q->size;
	return ret;
}

unsigned int QueueEmpty(queue *q)
{
	return !q->size;
}

unsigned int QueueSize(queue *q)
{
	return q->size;
}

void FreeQueue(queue *q)
{
	free(q->memory);
}

void DebugQueue(queue *q)
{
	printf("###################################\n");
	printf("Queue Information\n");
	printf("Size:      %d\n", QueueSize(q));
	printf("Mem Size:  %d\n", q->max_size);
	printf("Item Size: %ld\n", q->item_size);
	printf("===================================\n");
	unsigned int i = 0,j;
	for(i=0;i<q->size;++i)
	{
		j = (q->front + i)%q->max_size;
		printf("%3d: %8d\n", j, *((int*)q->memory+j));
	}
	printf("###################################\n");
}