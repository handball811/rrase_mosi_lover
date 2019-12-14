#include <stdio.h>
#include "confirm_solver.h"
#include "../../../Modules/Vector/vector.h"
#include "../../../Modules/Queue/queue.h"

// 7までは正確に出る
// 8を超えると８以上になり続ける
#define BORDER_SYSTEM(x) (((x)&7)+((!!((x)>>3))<<3))

SCNode SCNodes[400000];
unsigned int SCNodeCurPos = 0;
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
	node->arrived = 0;
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
		SCNode *child = &SCNodes[SCNodeCurPos++];
		SCNodeInit(child);
		// 次のポイントを登録
		head->next[top] = child;
		// Return Pointerの設定
		head->next[top]->parent = head;
		SCAppendWord(head->next[top], &str[1]);
	}
	SCAppendWord(head->next[top], &str[1]);
}
// 指定のノードより上流にあり、かつ分岐が存在するところまで
// Nodeを無効にする。切断だけでいいかな？
void SCNodeEliminate(SCNode *node)
{
	unsigned int i;
	while(
		node->parent != NULL &&
		node->parent!=scnode_head &&
		node->parent->parent!=scnode_head &&
		node->parent->conn_num == 1)
	{
		node = node->parent;
		//printf("Flag %d Eliminated\n", node->flag);
		node->conn_num = 0;
		node->next[0] = NULL;
		node->next[1] = NULL;
		node->next[2] = NULL;
		node->next[3] = NULL;
	}
	if(node->parent->conn_num > 0)
		--node->parent->conn_num;
	for(i=0;i<4;++i)
	{
		if(node->parent->next[i] == node)
		{
			node->parent->next[i] = NULL;
		}
	}
}

void SCInitializeNodes(char **strs, unsigned int str_len)
{
	printf("SCNode Init\n");
	scnode_head = &SCNodes[SCNodeCurPos++];//VectorPushBack(&SCNodes, &root);
	SCNodeInit(scnode_head);
	unsigned int i;
	// トライへの追加を行う
	for(i=0;i<str_len; ++i)
	{
		//printf("SCNode Appending: %s\n",*strs);
		SCAppendWord(scnode_head, *strs);
		++strs;
	}
	// サフィックス接続の構築
	printf("SCNode generate init suffix node\n");
	scnode_head->suffix = scnode_head;

	queue q = GenerateQueue(sizeof(SCNode*));
	queue delq = GenerateQueue(sizeof(SCNode*));
	for(i=0;i<4;++i)
	{
		if(scnode_head->next[i]==NULL)
		{
			scnode_head->next[i] = scnode_head;
		}
		else
		{
			scnode_head->next[i]->suffix = scnode_head;
			QueuePush(&q, &scnode_head->next[i]);
		}
	}
	// Suffixの行く先が葉要素の場合、
	// その要素はすでに内包されていることになるので
	// 候補から消して良い
	printf("SCNode generate suffix node\n");
	SCNode *now, *nxt;
	while(!QueueEmpty(&q))
	{
		//printf("gofor\n");
		now = *((SCNode**)QueuePop(&q));
		// DebugQueue(&q);
		for(i=0;i<4;++i)
		{
			if(now->next[i] != NULL)
			{
				nxt = now->suffix;
				while(nxt->next[i] == NULL)
					nxt = nxt->suffix;

				now->next[i]->suffix = nxt->next[i];
				// もし登録先が末端なら削除
				if(nxt->next[i]->conn_num == 0)
					QueuePush(&delq, &nxt->next[i]);
				QueuePush(&q, &now->next[i]);
			}
		}
	}
	printf("delete unneeded Node\n");
	// 最後にまとめて削除
	while(!QueueEmpty(&delq))
	{
		SCNodeEliminate(*((SCNode**)QueuePop(&delq)));
	}
	FreeQueue(&q);
	FreeQueue(&delq);
}

void SCFree()
{
	//FreeVector(&SCNodes);
}


int SCDebugDisplay(SCNode *head, int depth, int show_tree)
{
	if(head->conn_num == 0)
	{
		if(show_tree)
			printf(" %d\n", head->arrived);
		//return head->arrived==1;
		return (head->parent != scnode_head);
	}
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
			{
				if(head->next[i]->conn_num)
					printf("%s%c(%d -> %d)\n", top, 'a'+i, head->next[i]->flag, head->next[i]->suffix->flag);
				else
					printf("%s%c(%d -> %d)", top, 'a'+i, head->next[i]->flag, head->next[i]->suffix->flag);
			}
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
	printf("Node Size: %d\n", SCNodeCurPos);
	printf("------------------------------------\n");
	printf("(root)\n");
	int ret = SCDebugDisplay(scnode_head, 1, show_tree);
	printf("Leaf size: %d\n", ret);
	printf("####################################\n");
}

void SCMatch(char *str)
{
	// ここからが本番
	// 不要なノードを停止していき、どれくらいになるかを検証する。
	unsigned int t;
	unsigned int str_pos = 0,i;
	// Flagに配列のインデックスを持たせる（あんましいい方法じゃないかも）
	for(i=0; i<SCNodeCurPos; ++i)
	{
		SCNodes[i].flag = i;
	}
	// 位置の候補
	queue q = GenerateQueue(sizeof(SCNode*));
	// 位置と値の大きさ
	unsigned int _cur_pos[400000] = {0};
	unsigned int _next_pos[400000] = {0};
	unsigned int *cur_pos, *next_pos, *switch_bridge;
	cur_pos = &_cur_pos[0];
	next_pos = &_next_pos[0];

	QueuePush(&q, &scnode_head);

	unsigned int cands, flag, pos_flag;
	SCNode *pos, *next, *shot;
	cur_pos[scnode_head->flag] = 1;
	while('\0'!=(t=(unsigned int)str[str_pos]) && !QueueEmpty(&q))
	{
		cands = QueueSize(&q);
		if(str_pos%1 == 0)
		{
			printf("***********************************\n");
			printf("Index     : %d\n", str_pos);
			printf("Next word : %c\n", t);
			printf("Cand Size : %d\n", cands);
		}
		if(t == 'x')
		{
			for(i=0; i<cands; ++i)
			{
				pos = *((SCNode**)QueuePop(&q));
				pos_flag = pos->flag;
				if(!cur_pos[pos_flag])
					continue;
				//printf("Arrived : %d\n", pos_flag);
				//全てのパターンで試す
				for(t=0;t<4;++t)
				{
					//printf("\t(%d)\n", t);
					if(pos->next[t] != NULL)
					{
						next = pos->next[t];
						flag = next->flag;
						if(!next->conn_num)
						{
							//末端の場合の特殊な処理
							next->arrived += cur_pos[pos_flag];
							if(next->arrived > 1)
							{
								// もし2回目以降になっているなら削除
								SCNodeEliminate(next);
								// 消した以上候補から消す。
								// 通常ルートでもう来ることはない
								//continue;
							}
						}
						if(!next_pos[flag])
							QueuePush(&q, &next);
						next_pos[flag] += cur_pos[pos_flag];
						//値を4以上にはしない
						next_pos[flag] = BORDER_SYSTEM(next_pos[flag]);
					}
					else
					{
						//次がないのでSuffixをたどる。
						//Suffixで末端に移動することはなく
						//仮にそう判断できるなら、そこは無効になってる
						shot = pos;
						next = pos->suffix;
						while(next->next[t]==NULL && next != scnode_head)
						{
							if(next->conn_num)
							{
								//ショートカットを作成
								shot->suffix = next;
								shot = next;
							}
							next = next->suffix;
							//printf("\tsuffix: %d\n", next->flag);
						}
						next = next->next[t];
						//printf("\tsuffix: %d\n", next->flag);
						flag = next->flag;
						if(!next_pos[flag])
							QueuePush(&q, &next);
						next_pos[flag] += cur_pos[pos_flag];
						//値を4以上にはしない
						next_pos[flag] = BORDER_SYSTEM(next_pos[flag]);
					}
					//printf("\tgoto : %d\n",flag);
				}
				// cur_posからいた記録をなくす
				cur_pos[pos_flag] = 0;
			}
		}
		else
		{
			t -= 'a';
			for(i=0; i<cands; ++i)
			{
				pos = *((SCNode**)QueuePop(&q));
				pos_flag = pos->flag;
				if(!cur_pos[pos_flag])
					continue;
				//printf("Arrived : %d\n", pos_flag);
				// 次があるならそこに移動
				if(pos->next[t] != NULL)
				{
					next = pos->next[t];
					flag = next->flag;
					if(!next->conn_num)
					{
						//末端の場合の特殊な処理
						next->arrived += cur_pos[pos_flag];
						if(next->arrived > 1)
						{
							// もし2回目以降になっているなら削除
							SCNodeEliminate(next);
							// 消した以上候補から消す。
							// 通常ルートでもう来ることはない
							//continue;
						}
					}
					if(!next_pos[flag])
						QueuePush(&q, &next);
					next_pos[flag] += cur_pos[pos_flag];
					//値を4以上にはしない
					next_pos[flag] = BORDER_SYSTEM(next_pos[flag]);
				}
				else
				{
					//次がないのでSuffixをたどる。
					//Suffixで末端に移動することはなく
					//仮にそう判断できるなら、そこは無効になってる
					shot = pos;
					next = pos->suffix;
					while(next->next[t]==NULL && next != scnode_head)
					{
						/*
						if(next->conn_num)
						{
							//ショートカットを作成
							//printf("shortcut made\n");
							shot->suffix = next;
							shot = next;
						}*/
						next = next->suffix;
						//printf("\tsuffix: %d\n", next->flag);
					}
					/*
					if(next->conn_num)
					{
						//ショートカットを作成
						//printf("shortcut made\n");
						shot->suffix = next;
						shot = next;
					}*/
					next = next->next[t];
					//printf("\tsuffix: %d\n", next->flag);
					flag = next->flag;
					if(!next_pos[flag])
						QueuePush(&q, &next);
					next_pos[flag] += cur_pos[pos_flag];
					//値を4以上にはしない
					next_pos[flag] = BORDER_SYSTEM(next_pos[flag]);
				}
				// cur_posからいた記録をなくす
				cur_pos[pos_flag] = 0;
				//printf("\tgoto : %d\n",flag);
			}
		}
		if(str_pos%1 == 0)
		{
			SCDebugNodes(0);
			// 今の位置とか諸々を交換
			for(i=0; i<30; ++i)
			{
				printf("%2d ", i);
			}
			printf("\n");
			for(i=0; i<30; ++i)
			{
				printf("%2d ", next_pos[i]);
			}
			printf("\n");
			for(i=0; i<30; ++i)
			{
				printf("%2d ", SCNodes[i].conn_num);
			}
			printf("\n");
			getchar();
		}
		switch_bridge = cur_pos;
		cur_pos = next_pos;
		next_pos = switch_bridge;
		++str_pos;
	}
	printf("len %d\n", str_pos);
	FreeQueue(&q);
}

















