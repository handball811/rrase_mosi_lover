#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "SolveCertainString.h"
#include "MiddleStructureHandler.h"
#include "InsertConfirmParts.h"
#include "InsertPartsRoughly.h"


// inputStructureの部分文字列を降順にソートする。
void SortInputStructureParts(input_structure* inputStructure) {
    quicksort(inputStructure->parts, 0, inputStructure->partsNum - 1);
}

void SolveCertainString(input_structure *inputStructure, middle_predict_structure *middleStructure) {
    int *usedPartsFlg; // 部分文字列が当てはまったかどうかを管理する配列。
    usedPartsFlg = (int *)malloc(sizeof(int) * inputStructure->partsNum);
    for(int i = 0; i < inputStructure->partsNum; i++) {
        usedPartsFlg[i] = 0;
    }

    SortInputStructureParts(inputStructure);   
    InitializeMiddleStructure(inputStructure, middleStructure); // inputStructureの中身を元にmiddleStructureを初期化する。移したinputStructureの短い部分文字列も消す。
    InsertConfirmParts(inputStructure, middleStructure, usedPartsFlg);        // まず確実に当てはまる部分文字列を当てはめる。
    InsertPartsRoughly(inputStructure, middleStructure, usedPartsFlg);        // 残りは一致する文字数が大きいところに挿入。
    PushUnusedPartsToMiddleStructure(inputStructure, middleStructure, usedPartsFlg);
}