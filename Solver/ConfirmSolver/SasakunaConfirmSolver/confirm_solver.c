#include "confirm_solver"
#include "../../../Modules/Vector/vector.h"

Vector SCNodes;

void SCAppendWord(char* str)
{
	//SCNodeの構造に追加していく

}

void SCInitializeNodes(char **strs, unsigned int str_len)
{
	SCNodes = GenerateVector(sizeof(SCNode));
	SCNode root;
	root.conn_num = 0;
	int i;
	for(i=0;i<str_len; ++i)
	{
		SCAppendWord(strs[i]);
	}
}
