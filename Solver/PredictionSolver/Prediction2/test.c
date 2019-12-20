#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prediction2.h"
#include "../../../DataStructure/InputStructure/input_v1.h"
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"
#include "../../../DataStructure/OutputStructure/output_v1.h"
#include "../../../Generator/ReadDataFile.h"
#include "../../ConfirmSolver/SolveCertainString.h"
#include "../../ConfirmSolver/CalculateCorrectAnswerRate.h"

int main(void){
  /*
  middle_predict_structure middle;
  strcpy(middle.str, "abcdabcdabcdxxcd");
  middle.strLen = 16;
  int predict_input[] = {1,4,12,16};
  memcpy(middle.unsettledPlace, predict_input, sizeof(int)*4);
  char*** parts;
  parts = (char***)malloc(sizeof(char***)*3);
  parts[0] = (char**)malloc(sizeof(char**)*0);
  parts[1] = (char**)malloc(sizeof(char**)*1);
  parts[2] = (char**)malloc(sizeof(char**)*3);

  parts[1][0] = "b";
  parts[2][0] = "ab";
  parts[2][1] = "cd";
  parts[2][2] = "cd";

  middle.parts = parts;

  int partsNum[3] = {0,1,3};
  middle.partsNum = partsNum;
  middle.maxPartsLen = 2;

  output_structure output;
  prediction2(&middle,&output);
  printf("%s\n",output.ans);

  return 0;
  */

  char fileName[] = "Data/dat1_in";
  input_structure inputStructure;
  middle_predict_structure middleStructure;
  output_structure outputStructure;

  GetStructureFromFile(fileName, &inputStructure);
  SolveCertainString(&inputStructure, &middleStructure);
  prediction2(&middleStructure,&outputStructure);
  CalculateCorrectAnswerRate("Data/dat1_ref",outputStructure.ans,outputStructure.ans_len);
}
