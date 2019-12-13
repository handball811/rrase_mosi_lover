#ifndef SOLVER_CONFIRMSOLVER_SASAKUNA_CONFIRMSOLVER
#define SOLVER_CONFIRMSOLVER_SASAKUNA_CONFIRMSOLVER

typedef struct sasakuna_confirm_node{
	//接続先を記録　ない場合はNULL
	struct sasakuna_confirm_node *next[4];
	//接続されている有効な接続の数
	unsigned int conn_num;
	//そのノードが有効かとかを保存する
	unsigned int flag;
	//そのノードの親ノードのポインタ
	struct sasakuna_confirm_node *parent;
	//サフィックスノードの接続先
	struct sasakuna_confirm_node *suffix;
	// これまでに何回来たかを表す
	unsigned int arrived;
} SCNode;



void SCInitializeNodes(char**, unsigned int);
void SCDebugNodes();
void SCFree();
void SCMatch();
#endif