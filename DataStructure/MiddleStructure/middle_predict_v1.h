#ifndef DATASTRUCTURE_MIDDLE_PREDICT_V1
#define DATASTRUCTURE_MIDDLE_PREDICT_V1

typedef struct{
	char str[400010];					// 元々の虫食いに部分文字列を当てはめたもの(inputStructure.strのxを置きかえたもの)
	char strConsistOfParts[400010];		// 当てはめた部分文字列だけで構成された文字列
	int strLen;

	int unsettledPlace[400010];			// xの場所を示す。

	// 残りのまだ当てはまってないパーツ
	char*** parts;		// まだ当てはまっていない部分文字列。　例:parts[4][2] これは4文字の部分文字列の中で3番目のもの。
	int* partsNum;		// 部分文字列の個数。	例:partsNum[4]　これは4文字の文字列がいくつあるか。
	int maxPartsLen;	// 部分文字列の中で最も長い文字数
}middle_predict_structure;

#endif