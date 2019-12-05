#include <stdio.h>
#include "SolveCertainString.h"
#include "../../Generator/ReadDataFile.h"

int main(int argc, char const *argv[])
{
    char fileName[] = "dat0_in";
    input_structure dataStructure;
    GetStructureFromFile(fileName, &dataStructure);
    SolveCertainString(&dataStructure);

    return 0;
}
