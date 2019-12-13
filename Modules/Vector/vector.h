#ifndef MODULES_VECTOR_VECTOR
#define MODULES_VECTOR_VECTOR

typedef struct {
	void *memory;
	unsigned int size;
	unsigned int max_size;
	size_t item_size;
} vector;

// 実体として保存していく
vector GenerateVector();
void* VectorPushBack(vector *, void*);
void VectorPopBuck(vector *);
void* VectorAt(vector*, unsigned int num);
unsigned int VectorSize(vector*);
void FreeVector(vector*);
void DebugVector(vector*);
#endif