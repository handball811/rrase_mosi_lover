#include "DataStructure/InputStructure/input_v1.h"
#include "DataStructure/MiddleStructure/middle_predict_v1.h"
#include "DataStructure/OutputStructure/output_v1.h"

int main(int argc, char const *argv[])
{
    char fileName[] = "dat1_in";
    input_structure inputStructure;
    middle_predict_structure middleStructure;
    output_structure outputStructure;

    GetStructureFromFile(fileName, &inputStructure);
    SolveCertainString(&inputStructure, &middleStructure);
    CalculateCorrectAnswerRate(middleStructure.str,middleStructure.str_len);

    return 0;
}