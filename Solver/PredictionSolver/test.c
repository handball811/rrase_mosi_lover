#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../DataStructure/InputStructure/input_v1.h"
#include "../../DataStructure/MiddleStructure/middle_predict_v1.h"
#include "../../DataStructure/OutputStructure/output_v1.h"
#include "../ConfirmSolver/CalculateCorrectAnswerRate.h"
#include "./PredictionSolver.h"


int main(void){
  char fileName[] = "Data/dat2_in";
  input_structure inputStructure;
  middle_predict_structure middleStructure;
  output_structure outputStructure;

  GetStructureFromFile(fileName, &inputStructure);
  SolveCertainString(&inputStructure, &middleStructure);
  prediction2(&middleStructure,&outputStructure);
  CalculateCorrectAnswerRate("Data/dat2_ref",outputStructure.ans,outputStructure.ans_len);

  return 0;
}
