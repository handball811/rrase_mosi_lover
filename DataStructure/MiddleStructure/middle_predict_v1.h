#ifndef DATASTRUCTURE_MIDDLE_PREDICT_V1
#define DATASTRUCTURE_MIDDLE_PREDICT_V1

typedef struct{
	//ある程度確定した状態
	char str[400010];
	int str_len;
	//確定していないところを伝える
	int predict[400010];
	int predict_len;// 必ず2の倍数

	//この部分は input_structure と同じ
	// ただし確定している部分もあると思うので、減ってはいるはず
	char parts[400010];
	int  range[400010];
	int  range_len;

}middle_predict_structure;

#endif