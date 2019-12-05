#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main()
{
	int num;
	vector v = GenerateVector(sizeof(num));
	num = 100;
	VectorPushBack(&v, &num);
	num = 200;
	VectorPushBack(&v, &num);
	num = 300;
	VectorPushBack(&v, &num);
	num = 400;
	VectorPushBack(&v, &num);
	num = 500;
	VectorPushBack(&v, &num);
	num = 600;
	VectorPushBack(&v, &num);
	DebugVector(&v);
	return 0;
}
