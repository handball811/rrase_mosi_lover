#include "confirm_solver_setting.h"

int MINIMUM_CHARACTER_NUM_TO_FIT = 5;   // ConfirmSolverで当てはめる最小の文字数。
int PHASE_NUM = 1;//8;                      // 下の配列の要素数。パラメータを何回変更して繰り返すかを示す。

// 何文字が完全に一致していたらそこに当てはまると確定させるか。例：abcxxdとabcdddは4文字完全一致なので当てはめる。
int MATCH_CHARACTER_NUM[] = {16};//, 14, 13, 12, 11, 10, 10, 10};
int FIT_MINIMUM_MATCH_NUM[] = {15};//, 13, 12, 11, 10, 9, 8, 7};