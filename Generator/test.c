#include "ReadDataFile.h"
#include <stdio.h>

int main()
{
    char fileName[] = "dat0_in";
    input_structure inputData;
    inputData = GetStructureFromFile(fileName);
    printf("%s\n", inputData.str);

    return 0;
}
