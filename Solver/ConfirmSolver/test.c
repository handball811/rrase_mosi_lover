#include <stdio.h>
#include "SolveCertainString.h"
#include "../../Generator/ReadDataFile.h"

int main(int argc, char const *argv[])
{
    char fileName[] = "dat0_in";
    input_structure inputStructure;
    middle_predict_structure middleStructure;

    GetStructureFromFile(fileName, &inputStructure);
    SolveCertainString(&inputStructure, &middleStructure);
    printf("%s\n", middleStructure.str);

    return 0;
}
