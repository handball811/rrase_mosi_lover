#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../../DataStructure/OutputStructure/output_v1.h"
#include "judge_answer.h"

void test1()
{
	output_structure ls, rs;
	char l[] = "abcdabcd";
	char r[] = "abcdabcd";
	strcpy(ls.ans, l);
	ls.ans_len = 8;
	strcpy(rs.ans, r);
	rs.ans_len = 8;

	printf("%d\n",get_edit_distance(&ls, &rs));
	assert(get_edit_distance(&ls, &rs) == 0);
	return;
}

void test2()
{
	output_structure ls, rs;
	char l[] = "abcdabcd";
	char r[] = "abcabc";
	strcpy(ls.ans, l);
	ls.ans_len = 8;
	strcpy(rs.ans, r);
	rs.ans_len = 6;
	printf("%d\n",get_edit_distance(&ls, &rs));
	assert(get_edit_distance(&ls, &rs) == 2);
	return;
}


int main()
{
	test1();
	test2();
	return 0;
}



