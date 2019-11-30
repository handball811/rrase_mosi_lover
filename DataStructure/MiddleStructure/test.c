#include <stdio.h>
#include <string.h>
#include "middle_predict_v1.h"

int main()
{
	middle_predict_structure middle;

	strcpy(middle.str, "abcdabcdabcdxxcd");
	middle.str_len = 16;
	/*
	nを偶数とした時、
	range[n] <= x < range[n+1] の範囲が
	まだ確定していないところ
	*/
	int predict_input[] = {1,4,12,16};
	memcpy(middle.predict, predict_input, sizeof(int)*4);
	input.predict_len = 4;
	/*
	上の場合
	1~4文字目(４文字目そのものは含まない)   bcd
	と
	12〜16文字目の　　　　　　　　　　　　　 xxcd
	が確定していない
	*/

	strcpy(input.parts, "babcdcd");
	int range_input[] = {0,1,3,5,7};
	memcpy(input.range, range_input, sizeof(int)*5);

	input.range_len = 5;
	/*
	上の部分はinput_structureと一緒！
	*/
	return 0;
}