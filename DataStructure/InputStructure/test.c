#include <stdio.h>
#include <string.h>
#include "input_v1.h"

int main()
{
	input_structure input;
	strcpy(input.str, "abcdabcdabcdxxxx");
	input.strLen = 16;

	// メモリ確保
	input.parts = (char **)malloc(sizeof(char *) * 2);
	for(int i=0;i<2;i++){
		input.parts[i] = (char *)malloc(sizeof(char) * 10);
	}

	input.parts[0] = "aabc";
	input.parts[1] = "bcd";
	input.partsNum = 2;

	printf("%s\n", input.str);
	return 0;
}