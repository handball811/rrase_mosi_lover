#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiddleStructureHandler.h"
#include "sort.h"
#include "../../Settings/confirm_solver_setting.h"

// 短い文字列をMiddleStructureに移動させる関数。移動させた文字数を返す。
void InsertShortStringToMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure, int startPositionNum){
    for(int i=startPositionNum;i<inputStructure->partsNum;i++){
        middleStructure->parts[i-startPositionNum] = (char *)malloc(sizeof(char) * (1+strlen(inputStructure->parts[i])));
        strcpy(middleStructure->parts[i - startPositionNum], inputStructure->parts[i]);
    }

    middleStructure->partsNum = inputStructure->partsNum - startPositionNum;
}

// MiddleStructureを初期化し、CertainSolverに不必要な短い文字列は移植しておく。
void InitializeMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure){
    strcpy(middleStructure->str, inputStructure->str);  // まずはstrとstrLenの代入。
    middleStructure->strLen = inputStructure->strLen;

    for(int i=0;i<inputStructure->strLen;i++){
        middleStructure->strConsistOfParts[i] = 'x';    // strConsistOfPartsはxを全てに代入しておく。
    }
    
    middleStructure->parts = (char**)malloc(sizeof(char*) * inputStructure->partsNum);
    int i;
    for(i=0;i<inputStructure->partsNum;i++){
        if(strlen(inputStructure->parts[i]) >= MINIMUM_CHARACTER_NUM_TO_FIT) continue;
        InsertShortStringToMiddleStructure(inputStructure, middleStructure, i); // 短い文字列を移動。
        break;
    }

    inputStructure->partsNum -= (inputStructure->partsNum - i); // inputStructureの部分文字列の長さを移動した分だけ短く。
}

 // まだ使われていない部分文字列をmiddleStructureに移す。
void PushUnusedPartsToMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure, int* flg){
    int addPartsNum = 0;    // この関数内で追加した部分文字列数。

    for(int i=0;i<inputStructure->partsNum;i++){
        if(!flg[i]){    // もしまだ当てはまっていないなら
            middleStructure->parts[middleStructure->partsNum+addPartsNum] = (char *)malloc(sizeof(char) * (1+strlen(inputStructure->parts[i])));
            strcpy(middleStructure->parts[middleStructure->partsNum+addPartsNum], inputStructure->parts[i]);   
            addPartsNum++;
        }
    }

    middleStructure->partsNum += addPartsNum;



    // partsのソートをせよ。
    quicksort(middleStructure->parts, 0, middleStructure->partsNum-1);
    // 構造体内に便利な3次元配列を追加するのもここでやる。
    for(int i=0;i<middleStructure->partsNum;i++)
        printf("%s\n", middleStructure->parts[i]);
}