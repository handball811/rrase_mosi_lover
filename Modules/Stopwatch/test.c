#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "stopwatch.h"


void test1()
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
}

void test2()
{
	int i,j;

	Stopwatch *_watch = GenerateStopwatch("Timer");
	StopwatchLabel *_label_gen  = GenerateStopwatchLabel(_watch, "Generator");
	StopwatchLabel *_label_conf = GenerateStopwatchLabel(_watch, "Confirm");
	StopwatchLabel *_label_pre  = GenerateStopwatchLabel(_watch, "Prediction");
	StopwatchLabel *_label_ex   = GenerateStopwatchLabel(_watch, "Presenter");


	StopwatchStart(_watch);

	StopwatchLabelStart(_label_gen);
	for(i=0;i<1000000000;++i)
	{
		//10^9
		j++;
	}
	StopwatchLabelStop(_label_gen);

	StopwatchLabelStart(_label_conf);
	for(i=0;i<1000000000;++i)
	{
		//10^9
		j++;
	}
	StopwatchLabelStop(_label_conf);

	StopwatchLabelStart(_label_pre);
	for(i=0;i<1000000000;++i)
	{
		//10^9
		j++;
	}
	StopwatchLabelStop(_label_pre);

	StopwatchLabelStart(_label_ex);
	for(i=0;i<1000000000;++i)
	{
		//10^9
		j++;
	}
	StopwatchLabelStop(_label_ex);

	StopwatchStop(_watch);

	StopwatchShow(_watch);
	/*
出力結果のサンプル
###############################################
Time memory of 'Timer'
Total time :: real:  9.53026 // pro:  9.36566 // sys:  0.02955 
===============================================

-----------------------------------------------
# [ Generator ]
Total time :: real:  2.44081 // pro:  2.35684 // sys:  0.01166 
-----------------------------------------------
# [ Confirm ]
Total time :: real:  2.36553 // pro:  2.33389 // sys:  0.00630 
-----------------------------------------------
# [ Prediction ]
Total time :: real:  2.36104 // pro:  2.33873 // sys:  0.00533 
-----------------------------------------------
# [ Presenter ]
Total time :: real:  2.36287 // pro:  2.33619 // sys:  0.00624 
-----------------------------------------------

###############################################

	*/
	return;
}

int main()
{
	// test1();
	test2();
	return 0;
}


