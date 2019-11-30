#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "stopwatch.h"

int main()
{
	int i,j;
	// ストップヲッチの作成
	Stopwatch *sasakuna_watch = GenerateStopwatch("sasakuna");
	assert(strcmp(sasakuna_watch->name, "sasakuna")==0);
	printf("%s\n", sasakuna_watch->name);

	//同じ名前なら同じものが帰ってくるはず
	Stopwatch *sasakuna_copy  = GenerateStopwatch("sasakuna");
	assert(sasakuna_watch == sasakuna_copy);
	printf("copy check done\n");

	// サブのラベルを生成する。
	StopwatchLabel *label = GenerateStopwatchLabel(sasakuna_watch, "sub1");
	assert(strcmp(label->name, "sub1")==0);
	printf("%s\n", label->name);

	// こちらも同じ名前なら、同じポインタが帰ってくるはず
	StopwatchLabel *label_copy = GenerateStopwatchLabel(sasakuna_watch, "sub1");
	assert(label == label_copy);
	printf("copy check done\n");

	//メイン計測のみを行ってみる
	// ビジータイプの場合
	StopwatchStart(sasakuna_watch);
	for(i=0;i<1000000000;++i)
	{
		//10^9
		j++;
	}
	StopwatchPause(sasakuna_watch);
	StopwatchShow(sasakuna_watch);
	StopwatchStart(sasakuna_watch);
	//もう一回
	for(i=0;i<1000000000;++i)
	{
		//10^9
		++j;
	}
	StopwatchStop(sasakuna_watch);
	StopwatchShow(sasakuna_watch);

	// スリープ
	StopwatchStart(sasakuna_watch);
	sleep(2);
	StopwatchPause(sasakuna_watch);
	StopwatchStart(sasakuna_watch);
	//もう一回
	//printf("input number! \n");
	//scanf("%d",&i);
	StopwatchStop(sasakuna_watch);
	StopwatchShow(sasakuna_watch);

	return 0;
}


