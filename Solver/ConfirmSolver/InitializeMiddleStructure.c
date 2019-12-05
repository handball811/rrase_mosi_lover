#include <stdlib.h>
#include <string.h>
#include "InitializeMiddleStructure.h"
#include "../../Settings/confirm_solver_setting.h"

// 短い文字列をMiddleStructureに移動させる関数。
void InsertShortStringToMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure, int startPositionNum){
    for(int i=startPositionNum;i<inputStructure->partsNum;i++){
        middleStructure->parts[i-startPositionNum] = (char *)malloc(sizeof(char) * (1+strlen(inputStructure->parts[i])));
        strcpy(middleStructure->parts[i-startPositionNum], inputStructure->parts[i]);
    }

    middleStructure->partsNum = inputStructure->partsNum - startPositionNum;
}

// MiddleStructureを初期化し、CertainSolverに不必要な短い文字列は移植しておく。
void InitializeMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure){
    strcpy(middleStructure->str, inputStructure->str);
    middleStructure->str_len = inputStructure->strLen;

    middleStructure->parts = (char **)malloc(inputStructure->partsNum * sizeof(char *));    //まず入力された部分文字列の数だけ配列確保
    
    int i;
    for(i=0;i<inputStructure->partsNum;i++){
        if(strlen(inputStructure->parts[i]) >= MINIMUM_CHARACTER_NUM_TO_FIT) continue;
        InsertShortStringToMiddleStructure(inputStructure, middleStructure, i); // 短い文字列を移動。
        break;
    }

    inputStructure->partsNum -= (inputStructure->partsNum - i); // inputStructureの部分文字列の長さを移動した分だけ短く。
}
