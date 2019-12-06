#include <stdio.h>
#include <string.h>
#include "prediction2.h"
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"
#include "../../../DataStructure/OutputStructure/output_v1.h"

int main(){
  middle_predict_structure middle;
  strcpy(middle.str, "abcdabcdabcdxxcd");
  middle.str_len = 16;
  int predict_input[] = {1,4,12,16};
	memcpy(middle.predict, predict_input, sizeof(int)*4);
	middle.predict_len = 4;
  strcpy(middle.parts, "babcdcd");
	int range_input[] = {0,1,3,5,7};
	memcpy(middle.range, range_input, sizeof(int)*5);
	middle.range_len = 5;
  output_structure output = prediction2(&middle);
  printf("%s\n",output.ans);
}
