#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"prediction1.h"
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"

int main(){
    middle_predict_structure middletest;

    strcpy(middletest.str, "abcdabcdabcdxxcd");
    middletest.strLen = 16;
    middletest.unsettledPlace[0]=0;
    middletest.unsettledPlace[1]=3;
    middletest.unsettledPlace[2]=12;
    middletest.unsettledPlace[3]=16;

    int i=0,j=0;

    middletest.parts = (int ***)malloc(20 * sizeof(int **));
        for (i = 0; i < 5; i++) {
            middletest.parts[i] = (int **)malloc(20 * sizeof(int *));
            for (j = 0; j < 5; j++)
                middletest.parts[i][j] = (int*)malloc(20 * sizeof(int));
    }

    middletest.parts[3][0]="abc";
    middletest.parts[4][0]="cccd";
    middletest.partsNum[3] = 1;
    middletest.partsNum[4] = 1;
    middletest.maxPartsLen=4;

    printf("%s\n",middletest.str);

    prediction1(&middletest);

    printf("%s\n",middletest.str);


    return 0;

}