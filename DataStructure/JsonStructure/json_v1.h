#ifndef DATASTRUCTURE_JSON_V1
#define DATASTRUCTURE_JSON_V1


// Jsonのノードはこれにといつされる
typedef struct {

} IntegerJsonNode;

typedef struct {

} FloatJsonNode;

typedef struct {

} StringJsonNode;

typedef struct {

} ListJsonNode;

typedef struct {

} DictionaryJsonNode;

IntegerJsonNode    *GenerateIntegerJsonNode(int v);
FloatJsonNode      *GenerateFloatJsonNode(double v);
StringJsonNode     *GenerateStringJsonNode(char *v);
ListJsonNode       *GenerateListJsonNode(int len);
DictionaryJsonNode *GenerateDictionaryJsonNode(int len);

void AppendJsonNode(
	ListJsonNode *,
	void*);
void SetJsonNode(DictionaryJsonNode *, 
	StringJsonNode*,
	void*);



#endif