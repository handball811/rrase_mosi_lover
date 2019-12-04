#ifndef SOLVER_CONFIRMSOLVER_SASAKUNA_CONFIRMSOLVER
#define SOLVER_CONFIRMSOLVER_SASAKUNA_CONFIRMSOLVER

typedef struct sasakuna_confirm_node{
	//接続先を記録　ない場合はNULL
	sasakuna_confirm_node *next[4];
	//接続されている有効な接続の数
	unsigned int conn_num;
	//そのノードが有効かとかを保存する
	unsigned int flag;
	//そのノードの親ノードのポインタ
	sasakuna_confirm_node *parent;
	//サフィックスノードの接続先
	sasakuna_confirm_node *suffix;
} SCNode;


#endif