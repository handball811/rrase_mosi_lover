#include <stdio.h>
#include <stdlib.h>
#include "../../Generator/ReadDataFile.h"

void CalculateCorrectAnswerRate(char* answerFileName, char* answer, int len){
    FILE* fp = OpenFile(answerFileName);
    char *correctStr;
    correctStr = (char*)malloc(sizeof(char)*(1+len));
    fscanf( fp , "%s" , correctStr);

    int correctNum = 0;
    int xNum = 0;
    for(int i=0;i<len;i++){
        if(answer[i] == correctStr[i]){
            correctNum++;
        }else if(answer[i]=='x'){
            xNum++;
        }
    }

    printf("%d/%d\n", correctNum, len);
    printf("x以外㝮数%d\n", len- xNum);
    printf("%f\n", (double)correctNum/len*100);
    printf("\n");
}
