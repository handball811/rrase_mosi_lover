#include "confirm_solver_setting.h"

int MINIMUM_CHARACTER_NUM_TO_FIT = 5;   // ConfirmSolverで当てはめる最小の文字数。
int PHASE_NUM = 6;                      // 下の配列の要素数。パラメータを何回変更して繰り返すかを示す。
int MATCH_CHARACTER_NUM[] = {25, 24, 23, 22, 21, 20}; 
int FIT_MINIMUM_MATCH_NUM[] = {17, 16, 16, 16, 16, 16};
// 何文字が完全に一致していたらそこに当てはまると確定させるか。例：abcxxdとabcdddは4文字完全一致なので当てはめる。
