#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "confirm_solver.h"


#include "../../../DataStructure/InputStructure/input_v1.h"
#include "../../../Generator/ReadDataFile.h"

int main()
{
	char filename[] = "../../../Generator/dat0_in";
	input_structure inp = GetStructureFromFile(filename);
	SCInitializeNodes(inp.parts, inp.partsNum);
	SCDebugNodes(0);
	printf("Init done \n");
	return 0;
}