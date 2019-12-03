#include "input_v1.h"
#include "middle_predict_v1.h"
#include <string.h>

middle_predict_structure FitCertainString(input_structure);

// テスト用
int main(){
    input_structure input;

    strcpy(input.str, "abcdabcdabcdxxxx");
    input.str_len = 16;
  	strcpy(input.parts, "abcdadcbaabcdabc");
    int range_input[] = {0,5,10,12,13,16};
    memcpy(input.range, range_input, sizeof(int)*6);
    input.range_len = 6;

    middle_predict_structure result = FitCertainString(input);
    return 0;
}

middle_predict_structure FitCertainString(input_structure input){
    int minimumCharacterNum = 10;   // ここで当てはめる単語の最小の文字数

    // まず文字数でソート

    // queueに入れていく

    // 大きいものから順番に当てはめていく

    // 当てはまらなかったらqueueに入れ直し

    // 1周の中で一度も当てはめる操作がなければ終了し、下流工程へ。

    middle_predict_structure middle;
    return middle;
}