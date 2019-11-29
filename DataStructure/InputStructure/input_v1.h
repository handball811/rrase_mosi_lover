#ifndef DATASTRUCTURE_INPUT_INPUT_V1
#define DATASTRUCTURE_INPUT_INPUT_V1

typedef struct{
	// 入力
	char str[400010];
	int  str_len;
	// パーツ
	char parts[400010];
	int  range[400010];
	int  range_len;

}input_structure;

#endif