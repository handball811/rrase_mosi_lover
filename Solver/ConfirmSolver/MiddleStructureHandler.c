#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MiddleStructureHandler.h"
#include "sort.h"
#include "../../Settings/confirm_solver_setting.h"

// MiddleStructureを初期化し、CertainSolverに不必要な短い文字列は移植しておく。
void InitializeMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure){
    strcpy(middleStructure->str, inputStructure->str);  // まずはstrとstrLenの代入。
    middleStructure->strLen = inputStructure->strLen;

    for(int i=0;i<inputStructure->strLen;i++){
        middleStructure->strConsistOfParts[i] = 'x';    // strConsistOfPartsはxを全てに代入しておく。
    }
}


// partsをMiddleStructureに挿入する。
void PushPartsToMiddleStructure(middle_predict_structure* middleStructure, char** parts, int partsNum){
    middleStructure->parts = (char***)malloc(sizeof(char**) * strlen(parts[0])+1);
    middleStructure->partsNum = (int*)malloc(sizeof(int) * strlen(parts[0])+1);
    middleStructure->maxPartsLen = strlen(parts[0]);
    
    // まずはそれぞれの文字数の文字が何個あるのかを確認する。
    int charaNum = 0;   // 今確認中の文字の文字数
    int count = 0;      // 今確認中の文字数の文字が何個あるか。
    for(int i=0;i<partsNum;i++){
        if(charaNum != strlen(parts[i])){   // 文字数が切り替わったら
            middleStructure->partsNum[charaNum] = count;
            count = 1;
            charaNum = strlen(parts[i]);
        }else{
            count++;
        }
    }
    middleStructure->partsNum[charaNum] = count;

    int tmp = 1;
    for(int i=0;i<=middleStructure->maxPartsLen;i++){
        middleStructure->parts[i] = (char**)malloc(sizeof(char*) * middleStructure->partsNum[i]+1);
        for(int j=0;j<middleStructure->partsNum[i];j++){
            middleStructure->parts[i][j] = (char*)malloc(sizeof(char)*strlen(parts[partsNum-tmp]+1));
            strcpy(middleStructure->parts[i][j], parts[partsNum-tmp]);
            tmp++;
        }
    }
}

 // まだ使われていない部分文字列をmiddleStructureに移す。
void PushUnusedPartsToMiddleStructure(input_structure* inputStructure, middle_predict_structure* middleStructure, int* flg){
    int addPartsNum = 0;    // この関数内で追加した部分文字列数。

    char** parts;
    int partsNum = 0;

    parts = (char**)malloc(sizeof(char*) * inputStructure->partsNum);

    for(int i=0;i<inputStructure->partsNum;i++){
        if(!flg[i]){    // もしまだ当てはまっていないなら
            parts[partsNum] = (char *)malloc(sizeof(char) * (1+strlen(inputStructure->parts[i])));
            strcpy(parts[partsNum], inputStructure->parts[i]);   
            partsNum++;
        }
    }

    PushPartsToMiddleStructure(middleStructure, parts, partsNum);   // partsをMiddleStructureに挿入する。
}


void UpdateUnsettledPlace(middle_predict_structure* middleStructure){
    // middleStructure->unsettledPlaceを更新せよ。
    int tmp = 0;
    int flg = 0;    // 直前がxかどうか。
    for(int i=0;i<middleStructure->strLen;i++){
        if(!flg && middleStructure->strConsistOfParts[i]=='x'){
            middleStructure->unsettledPlace[tmp] = i;
            flg = 1;
        }else if(flg && middleStructure->strConsistOfParts[i]!='x'){
            middleStructure->unsettledPlace[tmp] = i;
            flg = 0;
        }
    }
}