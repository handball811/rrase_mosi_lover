#ifndef PRESENTER_TESTING_JUDGE_ANSWER
#define PRESENTER_TESTING_JUDGE_ANSWER

#include "../../DataStructure/OutputStructure/output_v1.h"
// 二つのOutputを比較して
// その編集距離を出力する

int _snake(int k, int y, char *l, char *r, int l_len, int r_len);     //  対角線が存在する場合は、移動する
int get_edit_distance(output_structure *l, output_structure *r);

#endif