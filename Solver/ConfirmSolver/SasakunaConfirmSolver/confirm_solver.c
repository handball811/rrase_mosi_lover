#include <stdio.h>
#include "confirm_solver.h"
#include "../../../Modules/Vector/vector.h"

vector SCNodes;
SCNode *scnode_head;

void SCNodeInit(SCNode *node)
{
	node->conn_num = 0;
	node->flag = 0;
	node->next[0] = NULL;
	node->next[1] = NULL;
	node->next[2] = NULL;
	node->next[3] = NULL;
	node->parent = NULL;
	node->suffix = NULL;
	return;
}

// とらいきに追加する部分
void SCAppendWord(SCNode *head, char* str)
{
	//SCNodeの構造に追加していく
	//printf("\tAppending word: %s// child_size: %d\n", str, head->conn_num);
	int top = str[0];
	if(top == '\0')
	{
		// 終端まで来ている
		return;
	}
	top -= 'a';
	if(head->next[top]==NULL)
	{
		//新たに作成する必要がある
		++head->conn_num;
		SCNode child;
		SCNodeInit(&child);
		// 次のポイントを登録
		head->next[top] = VectorPushBack(&SCNodes, &child);
		// Return Pointerの設定
		head->next[top]->parent = head;
		SCNodeInit(head->next[top]);
		SCAppendWord(head->next[top], &str[1]);
	}
	SCAppendWord(head->next[top], &str[1]);
}
void SCInitializeNodes(char **strs, unsigned int str_len)
{
	printf("Generate Vector\n");
	SCNodes = GenerateVector(sizeof(SCNode));
	SCNode root;

	printf("SCNode Init\n");
	SCNodeInit(&root);
	scnode_head = VectorPushBack(&SCNodes, &root);
	unsigned int i;
	// トライへの追加を行う
	for(i=0;i<str_len; ++i)
	{
		printf("SCNode Appending: %s\n",*strs);
		SCAppendWord(scnode_head, *strs);
		++strs;
	}
	// サフィックス接続の構築
	scnode_head->suffix = scnode_head;
	for(i=0;i<4;++i)
	{
		if(scnode_head->next[i]==NULL)
		{
			scnode_head->next[i] = scnode_head;
		}
		else
		{
			scnode_head->next[i]->suffix = scnode_head;
			//Queue求む
		}
	}
}

int SCDebugDisplay(SCNode *head, int depth, int show_tree)
{
	if(head->conn_num == 0)
		return 1;
	int i = 0;
	char top[128];
	int ret = 0;
	for(i=0;i<depth;++i)
	{
		top[i] = ' ';
	}
	top[depth] = '\0';
	for(i=0;i<4;++i)
	{
		if(head->next[i] != NULL)
		{
			if(show_tree)
				printf("%s%c\n", top, 'a'+i);
			ret += SCDebugDisplay(head->next[i], depth+1, show_tree);
		}
	}
	return ret;
}

void SCDebugNodes(int show_tree)
{
	// トライを表示する
	printf("####################################\n");
	printf("Debug SCSNode Trie\n");
	printf("Node Size: %d\n", VectorSize(&SCNodes));
	printf("------------------------------------\n");
	printf("(root)\n");
	int ret = SCDebugDisplay(scnode_head, 1, show_tree);
	printf("Leaf size: %d\n", ret);
	printf("####################################\n");
}