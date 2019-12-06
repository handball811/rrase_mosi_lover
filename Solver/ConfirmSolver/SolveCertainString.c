#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "SolveCertainString.h"
#include "InitializeMiddleStructure.h"
#include "InsertConfirmParts.h"
#include "../../Settings/confirm_solver_setting.h"


// inputStructureの部分文字列を降順にソートする。
void SortParts(input_structure* inputStructure) {
    quicksort(inputStructure->parts, 0, inputStructure->partsNum - 1);
    // BubbleSort(inputStructure->parts, inputStructure->partsNum);
}


void SolveCertainString(input_structure *inputStructure, middle_predict_structure *middleStructure) {
    SortParts(inputStructure);                                  //まず文字数でソート
    InitializeMiddleStructure(inputStructure, middleStructure); // inputStructureの中身を元にmiddleStructureを初期化する。移したinputStructureの短い部分文字列も消す。
    InsertConfirmParts(inputStructure, middleStructure);        // まず確実に当てはまる部分文字列を当てはめる。
    InsertPartsRoughly(inputStructure, middleStructure);        // 残りは一致する文字数が大きいところに挿入。
}