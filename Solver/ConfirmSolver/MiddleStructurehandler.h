#ifndef MIDDLE_STRUCTURE_HANDLER
#define MIDDLE_STRUCTURE_HANDLER

#include "../../DataStructure/InputStructure/input_v1.h"
#include "../../DataStructure/MiddleStructure/middle_predict_v1.h"

// inputStructureの中身を元にmiddleStructureを初期化する。
void InitializeMiddleStructure(input_structure*, middle_predict_structure*);

// まだ使われていない部分文字列をmiddleStructureに移す。
void PushUnusedPartsToMiddleStructure(input_structure*, middle_predict_structure*, int*);

void UpdateUnsettledPlace(middle_predict_structure*);

#endif