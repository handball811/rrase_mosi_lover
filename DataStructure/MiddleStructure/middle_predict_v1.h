#ifndef DATASTRUCTURE_MIDDLE_PREDICT_V1
#define DATASTRUCTURE_MIDDLE_PREDICT_V1

typedef struct{
	//xが減ったある程度確定した状態
	char str[400010];
	int str_len;

	// 残りのまだ当てはまってないパーツ
	char **parts;
	int  partsNum;

}middle_predict_structure;

#endif