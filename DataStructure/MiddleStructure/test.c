#include <stdio.h>
#include <string.h>
#include "middle_predict_v1.h"

int main()
{
	middle_predict_structure middle;

	strcpy(middle.str, "abcdabcdabcdxxcd");
	middle.str_len = 16;
	
	// メモリ確保
	middle.parts = (char **)malloc(sizeof(char *) * 2);
	for(int i=0;i<2;i++){
		middle.parts[i] = (char *)malloc(sizeof(char) * 10);
	}

	middle.parts[0] = "aabc";
	middle.parts[1] = "bcd";
	middle.partsNum = 2;

	printf("%s\n", middle.str);
	return 0;
}