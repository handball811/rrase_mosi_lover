#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "InsertPartsRoughly.h"
#include "CalculateCorrectAnswerRate.h"
#include "../../Settings/confirm_solver_setting.h"

// strにtargetが当てはまる場所を探す
int InsertWord2(middle_predict_structure* middleStructure, int strLen, char* target, int targetLen, int phase) {
    int i = targetLen - 1;
    char *str = middleStructure->str;

    while(i < strLen) { // 1文字ずつずらしていく。
        int matchCharaNum = 0;

        for(int j = 0; j < targetLen;j++) { // 部分文字列全体を見て、何文字完全一致しているかの確認。
            if(middleStructure->strConsistOfParts[i-j] != 'x'){ // まずそこが空いてなければ問答無用で当てはめない。
                matchCharaNum = 0;
                break;
            }

            if(target[targetLen - j - 1] == str[i - j]) // 完全一致。
                matchCharaNum++;
            else if(str[i - j] != 'x' || middleStructure->strConsistOfParts[i-j] != 'x') { // 完全一致でもxでもない、又はすでに部分文字列が入っているなら100%当てはまらない。
                matchCharaNum = 0;
                break;
            }
        }

        if(matchCharaNum >= FIT_MINIMUM_MATCH_NUM[phase]) { // 当てはめる。
            for(int j = 0; j < targetLen; j++) {
                middleStructure->strConsistOfParts[i-j] = target[targetLen - j - 1];
                if(str[i - j] == 'x') {
                    str[i - j] = target[targetLen - j - 1];
                }
            }
            // printf("insert!\n");
            return 1;
        }

        i++;
    }

    // printf("not insert.\n");
    return 0; // 当てはまらなかった。
}

// 部分文字列をパラメータを元に当てはめていく。
void InsertPartsRoughly(input_structure *inputStructure, middle_predict_structure *middleStructure, int* flg) {
    for(int phase = 0; phase < PHASE_NUM; phase++) {    // フェーズ単位

        while(1) {  // 1度も入らなくなるまで
            int insertNum = 0; //この周回で何個の単語が入ったかを記録。

            for(int i = 0; i < inputStructure->partsNum; i++) { // パーツ単位
                if(flg[i] || strlen(inputStructure->parts[i]) < MATCH_CHARACTER_NUM[phase])
                    continue; // すでにその部分文字列が当てはまってた時かこのフェーズで当てはめる文字数以下のとき

                if(InsertWord2(middleStructure, inputStructure->strLen, inputStructure->parts[i], strlen(inputStructure->parts[i]), phase)) { // 入れてみる
                    flg[i] = 1; // 入ったらフラグを立てる。
                    insertNum++;
                }
            }

            // 一つも挿入出来なかったら終わり。　
            if(insertNum == 0)
                break;
        }

        printf("Phase%d Finished\n", phase);
        CalculateCorrectAnswerRate("Data/dat2_ref", middleStructure->str,middleStructure->strLen);
    }
}