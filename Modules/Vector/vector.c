#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

vector GenerateVector(size_t item_size)
{
	vector vec;
	vec.memory = malloc(item_size * 4);
	vec.size = 0;
	vec.max_size = 4;
	vec.item_size = item_size;
	return vec;
}

void VectorPushBack(vector *vec, void* item)
{
	if(vec->size >= vec->max_size)
	{
		void* tmp;
		if((tmp=realloc(vec->memory, vec->item_size*vec->max_size<<1))==NULL)
		{
			FreeVector(vec);
			exit(1);
		}
		vec->memory = tmp;
		vec->max_size <<= 1;
	}
	memcpy(vec->memory+(vec->size++ * vec->item_size), item, vec->item_size);
}

void VectorPopBack(vector *vec)
{
	--vec->size;
}

void* VectorAt(vector *vec, unsigned int num)
{
	if(num < vec->size)
		return vec->memory+num*vec->item_size;
	return NULL;
}

unsigned int VectorSize(vector *vec)
{
	return vec->size;
}

void FreeVector(vector *vec)
{
	free(vec->memory);
}

void DebugVector(vector *vec)
{
	printf("###################################\n");
	printf("Vector Information\n");
	printf("Size:      %d\n", vec->size);
	printf("Mem Size:  %d\n", vec->max_size);
	printf("Item Size: %ld\n", vec->item_size);
	printf("===================================\n");
	unsigned int i = 0;
	unsigned int size = vec->size;
	for(i=0;i<size;++i)
	{
		printf("%3d: %8d\n", i, *(int*)VectorAt(vec, i));
	}
	printf("###################################\n");
}