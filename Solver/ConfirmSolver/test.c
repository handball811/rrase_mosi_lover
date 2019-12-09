#include <stdio.h>
#include "SolveCertainString.h"
#include "../../Generator/ReadDataFile.h"

int main(int argc, char const *argv[])
{
    char fileName[] = "Data/dat1_in";
    input_structure inputStructure;
    middle_predict_structure middleStructure;

    GetStructureFromFile(fileName, &inputStructure);
    SolveCertainString(&inputStructure, &middleStructure);

    return 0;
}
