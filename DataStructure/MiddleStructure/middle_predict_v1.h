#ifndef DATASTRUCTURE_MIDDLE_PREDICT_V1
#define DATASTRUCTURE_MIDDLE_PREDICT_V1

typedef struct{
	char str[400010];					// 元々の虫食いに部分文字列を当てはめたもの(inputStructure.strのxを置きかえたもの)
	char strConsistOfParts[400010];		// 当てはめた部分文字列だけで構成された文字列
	int strLen;

	int unsettledPlace[400010];			// xの場所を示す。

	// 残りのまだ当てはまってないパーツ
	char **parts;		// まだ当てはまっていない部分文字列。
	int  partsNum;		// 部分文字列の個数。
}middle_predict_structure;

#endif