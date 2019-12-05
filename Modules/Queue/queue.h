#ifndef MODULES_QUEUE_QUEUE
#define MODULES_QUEUE_QUEUE

typedef struct {
	void *memory;
	unsigned int front;
	unsigned int bottom;
	unsigned int size;
	unsigned int max_size;
	size_t item_size;
} queue;

queue GenerateQueue();
void QueuePush(queue*, void*);
void* QueuePop(queue*);
unsigned int QueueEmpty(queue*);
unsigned int QueueSize(queue*);
void FreeQueue(queue*);
void DebugQueue(queue*);

#endif