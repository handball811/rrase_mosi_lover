#include <string.h>
#include <stdlib.h>
#include "InsertConfirmParts.h"

// strにtargetが当てはまる場所が1箇所に定まればそこに入れる。
int InsertWord(char* str, int strLen, char* target, int targetLen) {
    int i = targetLen - 1;
    int AlreadyInsertable = 0;
    int insertPosition = 0;

    while(i < strLen) { // 1文字ずつずらしていく。
        int matchCharaNum = 0;
        int insertable = 1;    // 当てはまるかどうかのフラグ

        for(int j = 0; j < targetLen;j++) { // 部分文字列全体を見て当てはめることが可能か判断。
            if(target[targetLen - j - 1] != str[i - j] && (str[i - j] !='x')){   // 完全一致でもなくxでもない時は絶対に当てはまらない。
                insertable = 0;
                break;
            }
        }

        if(insertable) { // 当てはめることができる
            if(AlreadyInsertable) return 0;
            AlreadyInsertable = 1;
            insertPosition = i;
        }
        i++;
    }

    if(AlreadyInsertable){  // 挿入箇所が1箇所に絞れた時
        for(int j = 0; j < targetLen; j++) {
            if(str[insertPosition - j] == 'x') {
                str[insertPosition - j] = target[targetLen - j - 1];
            }
        }
        return 1;
    }

    return 0; // 挿入箇所が1つもなかった時。
}

// 確実に1つに定まる部分文字列を当てはめる。
void InsertConfirmParts(input_structure *inputStructure, middle_predict_structure *middleStructure) {
    int *flg; // 部分文字列が当てはまったかどうかを管理する配列。
    flg = (int *)malloc(sizeof(int) * inputStructure->partsNum);
    for(int i = 0; i < inputStructure->partsNum; i++) {
        flg[i] = 0;
    }

    // 大きいものから順番に当てはめていく
    while(1) {
        int insertNum = 0; //この周回で何個の単語が入ったかを記録。

        for(int i = 0; i < inputStructure->partsNum; i++) {
            if(flg[i])
                continue; // すでにその部分文字列が当てはまってた時かこのフェーズで当てはめる文字数以下のとき

            if(InsertWord(middleStructure->str, inputStructure->strLen, inputStructure->parts[i], strlen(inputStructure->parts[i]))) { // 入れてみる
                flg[i] = 1; // 入ったらフラグを立てる。
                insertNum++;
            }
        }

        // 一つも挿入出来なかったら終わり。　
        if(insertNum == 0)
            break;
    }

    // 最後にflg[i]==0の部分文字列をmiddleStructure->parts[]に加える。partsNumの更新も忘れずに。降順に出来れば理想だが、昇順でもいいかもね。
}