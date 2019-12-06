#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SolveCertainString.h"
#include "../../Generator/ReadDataFile.h"


void CalculateCorrectAnswerRate(char* answer, int len){
    FILE* fp = OpenFile("dat1_ref");
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
    printf("x以外は%d\n", len- xNum);
    printf("%f\n", (double)correctNum/len*100);
}

int main(int argc, char const *argv[])
{
    char fileName[] = "dat1_in";
    input_structure inputStructure;
    middle_predict_structure middleStructure;

    GetStructureFromFile(fileName, &inputStructure);
    SolveCertainString(&inputStructure, &middleStructure);
    CalculateCorrectAnswerRate(middleStructure.str,middleStructure.str_len);

    return 0;
}
