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



void show_result(input_structure *result, char *r_ans)
{
	int i=0;
	char *ret = &(result->str[0]);
	double ans=0.0;
	double wrong=0.0;
	double missing = 0.0;
	double open    = 0.0;
	while(r_ans[i] != '\0')
	{
		if(ret[i] == r_ans[i])
			++ans;
		if(ret[i] != r_ans[i] && ret[i] != 'x')
			++wrong;

		++i;
	}
	printf("Result: %lf %%(Wrong: %lf %%, Ex: %lf Wper: %lf)\n",
		ans*100/400001,
		wrong*100/400001,
		(ans+(400001-ans-wrong)*.412)*100/400001,
		wrong/(ans+wrong-240000)*100);
}
void test_v2()
{
	const int sc_size = 10;
	const int sc_size2 = 9;
	//char *str = "abcdabcdxxxxabcdxxxx";
	//Stopwatch Generate

	char r_ans[400010];

	char filename[] = "../../../../data/dat1_in";
	input_structure inp;
	GetStructureFromFile(filename, &inp);


	char ans_file[] = "../../../../data/dat1_ref";
	FILE * fp = fopen(ans_file, "r");
	fscanf(fp, "%s", r_ans);

	// この関数を呼ぶだけで良い
	SCSolver(&inp, 1, 1);
	show_result(&inp, r_ans);
	return;
}

void test_v3()
{
	int i,j,k,a,b;
	Stopwatch *st = GenerateStopwatch("SasakunaConfirm");
	StopwatchStart(st);
	int mp[1024] = {0};
	int hash;
	const int sc_size = 10;
	// 2.2秒　10^6    10^4 -> 0.022sec
	for(i=0;i<1000000; ++i)
	{
		mp[0] = 1239875;
		a = 1;
		b = 1;
		for(j=0;j<sc_size;++j)
		{
			hash = (4-(mp[0]/b)%5)*b;
			for(k=0;k<a;++k)
			{
				mp[k+a] = mp[k]+hash;
			}
			a <<= 1;
			b *= 5;
		}
	}
	StopwatchStop(st);
	StopwatchShow(st);
}

int main()
{
	//test_v1();
	test_v2();
	//test_v3();
	return 0;
}