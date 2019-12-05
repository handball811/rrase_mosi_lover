#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "confirm_solver.h"


#include "../../../DataStructure/InputStructure/input_v1.h"
#include "../../../Generator/ReadDataFile.h"

int main()
{
	//char filename[] = "../../../Generator/dat0_in";
	char filename[] = "../../../../data/dat1_in";
	input_structure inp = GetStructureFromFile(filename);
	
	char *sample_parts[] = {
		"abcdd",
		"acb",
		"abc",
		"abccd",
		"bcdda",
		"bacbd",
		"caacd",
		"dbacc"
	};
	char *input_str = "abcxxxdbcabxcdba";
	
	SCInitializeNodes(inp.parts, (unsigned int)inp.partsNum);
	//SCInitializeNodes(sample_parts, (unsigned int)8);
	SCDebugNodes(0);
	SCMatch(inp.str);
	//SCMatch(input_str);
	SCDebugNodes(1);
	printf("Init done \n");
	SCFree();
	return 0;
}