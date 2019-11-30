#include <stdio.h>
#include <string.h>
#include "input_v1.h"

int main()
{
	//
	input_structure input;
	strcpy(input.str, "abcdabcdabcdxxxx");
	input.str_len = 16;
	/*
	パーツが以下の時,,,
	0   4 5   9   
	abcda dcbaa bc d abc
	の時,,,
	*/
	strcpy(input.parts, "abcdadcbaabcdabc");
	int range_input[] = {0,5,10,12,13,16};
	memcpy(input.range, range_input, sizeof(int)*6);

	input.range_len = 6;

	printf("%s\n", input.str);
	return 0;
}