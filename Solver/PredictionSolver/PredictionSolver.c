#include "../../DataStructure/MiddleStructure/middle_predict_v1.h"
#include "../../DataStructure/OutputStructure/output_v1.h"
#include "./Prediction1/prediction1.h"
#include "./Prediction2/prediction2.h"

void SolvePredictString(middle_predict_structure* middle, output_structure* output){
  *middle =  prediction1(middle);
  prediction2(middle,output);
}
