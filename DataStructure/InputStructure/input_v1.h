#ifndef DATASTRUCTURE_INPUT_INPUT_V1
#define DATASTRUCTURE_INPUT_INPUT_V1

typedef struct{
	// 入力
	char str[400010];
	int  strLen;
	
	// パーツ
	char **parts;
	int  partsNum;

}input_structure;

#endif