#include<stdio.h>
#include<string.h>
#include"prediction1.h"
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"

int main(){
    middle_predict_structure middletest;

    strcpy(middletest.str, "abcdabcdabcdxxcd");
    middletest.str_len = 16;

    middletest.parts = (char **)malloc(sizeof(char *) * 2);
	for(int i=0;i<2;i++){
		middletest.parts[i] = (char *)malloc(sizeof(char) * 10);
	}

    middletest.parts[0]="abc";
    middletest.parts[1]="cccd";
    middletest.partsNum = 2;

    printf("%s\n",middletest.str);

    prediction1(&middletest);

    printf("%s\n",middletest.str);

    return 0;

}