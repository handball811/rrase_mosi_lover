#include "SolveCertainString.h"
#include <stdio.h>
#include <string.h>

// 部分文字列をソートする。
void SortParts(input_structure* inputStructure){
    int i, j;
    char tmp[10000];

    for(i = 0; i < inputStructure->partsNum-1; i++) {
        for(j = i+1; j < inputStructure->partsNum; j++) {
            if(strlen(inputStructure->parts[i]) < strlen(inputStructure->parts[j])) {
                strcpy(tmp, inputStructure->parts[i]);
                strcpy(inputStructure->parts[i], inputStructure->parts[j]);
                strcpy(inputStructure->parts[j], tmp);
            }
        }
    }
}


void SolveCertainString(input_structure* inputStructure) {
    int minimumCharacterNum = 10; // ここで当てはめる単語の最小の文字数

    SortParts(inputStructure);  //まず文字数でソート

    printf("%s\n", inputStructure->parts[0]);
    printf("%s\n", inputStructure->parts[1]);
    printf("%s\n", inputStructure->parts[2]);
    

    // queueに入れていく

    // 大きいものから順番に当てはめていく

    // 当てはまらなかったらqueueに入れ直し

    // 1周の中で一度も当てはめる操作がなければ終了し、下流工程へ。

}