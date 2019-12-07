#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "confirm_solver.h"
#include "confirm_solver_v2.h"


#include "../../../DataStructure/InputStructure/input_v1.h"
#include "../../../Generator/ReadDataFile.h"
#include "../../../Modules/Stopwatch/stopwatch.h"
/*
void test_v1()
{
	//char filename[] = "../../../Generator/dat0_in";
	char filename[] = "../../../../data/dat1_in";
	input_structure inp;
	GetStructureFromFile(filename, &inp);
	
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
	
	//SCInitializeNodes(inp.parts, (unsigned int)inp.partsNum);
	SCInitializeNodes(sample_parts, (unsigned int)8);
	SCDebugNodes(0);
	//SCMatch(inp.str);
	SCMatch(input_str);
	SCDebugNodes(1);
	printf("Init done \n");
	SCFree();
}*/

void test_v2()
{
	//char *str = "abcdabcdxxxxabcdxxxx";
	//Stopwatch Generate
	Stopwatch *st = GenerateStopwatch("SasakunaConfirm");
	StopwatchLabel *st_init = GenerateStopwatchLabel(st, "init");
	StopwatchLabel *st_main = GenerateStopwatchLabel(st, "main");

	char filename[] = "../../../../data/dat0_in";
	input_structure inp;
	GetStructureFromFile(filename, &inp);

	StopwatchStart(st);
	StopwatchLabelStart(st_init);

	SCNodeInit(inp.str);

	StopwatchLabelStop(st_init);
	StopwatchLabelStart(st_main);

	int i,j;
	int ans = 0;
	int t_num=0,s_num=0;
	for(i=0;i<inp.partsNum;++i)
	{
		ans = SCMatch(inp.parts[i]);
		if(ans >= 0)
		{
			++t_num;
			//printf("%d %s\n",ans,inp.parts[i]);
			//getchar();
			int p_len = 0;
			while(inp.parts[i][p_len] != '\0')
			{
				++p_len;
			}
			//printf("%s\n",inp.parts[i]);
			//printf("%.*s\n", p_len, &inp.str[ans]);
			//getchar();
			for(j=0;j<p_len;++j)
			{
				if(inp.str[ans+j] == 'x')
					++s_num;
			}
		}
	}
	
	StopwatchLabelStop(st_init);
	StopwatchStop(st);

	printf("%d %d\n",t_num,s_num);
	StopwatchShow(st);
	return;
}

int main()
{
	//test_v1();
	test_v2();
	return 0;
}