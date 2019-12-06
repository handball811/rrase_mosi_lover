#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "SolveCertainString.h"
#include "InitializeMiddleStructure.h"
#include "../../Settings/confirm_solver_setting.h"


// inputStructureの部分文字列を降順にソートする。
void SortParts(input_structure* inputStructure){
    quicksort(inputStructure->parts, 0, inputStructure->partsNum-1);
    //BubbleSort(inputStructure->parts, inputStructure->partsNum);
}

// strにtargetが当てはまる場所を探す
int InsertWord(char* str, int strLen, char* target, int targetLen){
    int i = targetLen - 1;

    while (i < strLen){     // 1文字ずつずらしていく。
        int matchCharaNum = 0;

        for(int j=0;j<targetLen;j++){   // 部分文字列全体を見て、何文字完全一致しているかの確認。
            if(target[targetLen-j-1] == str[i-j])   // 完全一致。
                matchCharaNum++;
            else if(str[i-j]!='x'){                 // 完全一致でもxでもないなら100%当てはまらない。
                matchCharaNum = 0;
                break;
            }
        }

        if(matchCharaNum >= FIT_MINIMUM_MATCH_NUM){ // 当てはめる。
            for(int j=0;j<targetLen;j++){
                if(str[i-j] == 'x'){
                    str[i-j] = target[targetLen-j-1];
                }
            }
            //printf("insert!\n");
            return 1;
        }

        i++;
    }

    //printf("not insert.\n");
    return 0;   // 当てはまらなかった。
}

// inputStructureにある部分文字列をmiddleStructureのstrに当てはめていく。
void FitWords(input_structure* inputStructure, middle_predict_structure* middleStructure){
    int* flg;   // 部分文字列が当てはまったかどうかを管理する配列。
    flg = (int *)malloc(sizeof(int) * inputStructure->partsNum);
    for(int i=0;i<inputStructure->partsNum;i++){
        flg[i] = 0;
    }
    
    // 大きいものから順番に当てはめていく
    while(1){
        int insertNum = 0;  //この周回で何個の単語が入ったかを記録。

        for(int i=0;i<inputStructure->partsNum;i++){
            if(flg[i]) continue;    // すでにその部分文字列が当てはまってた時

            if(InsertWord(middleStructure->str, inputStructure->strLen, inputStructure->parts[i], strlen(inputStructure->parts[i]))){ // 入れてみる
                flg[i] = 1; // 入ったらフラグを立てる。
                insertNum++;
            }

            printf("%d\n", i);
        }

        // 一つも挿入出来なかったら終わり。　
        if(insertNum==0) break;
    }

  
    // 最後にflg[i]==0の部分文字列をmiddleStructure->parts[]に加える。partsNumの更新も忘れずに。降順に出来れば理想だが、昇順でもいいかもね。


}

void SolveCertainString(input_structure* inputStructure, middle_predict_structure* middleStructure) {
    SortParts(inputStructure);                                  //まず文字数でソート
    InitializeMiddleStructure(inputStructure, middleStructure); // inputStructureの中身を元にmiddleStructureを初期化する。移したinputStructureの短い部分文字列も消す。
    FitWords(inputStructure, middleStructure);                  // 大きいもの順に当てはまる部分文字列を当てはめる。
}