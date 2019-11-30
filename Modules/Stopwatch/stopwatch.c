#include <stdio.h>
#include <string.h>
#include "stopwatch.h"

Stopwatch *GenerateStopwatch(char *name)
{
	static const int MAX_WATCH_LENGTH = 32;
	static Stopwatch _watches[32];
	static int _watch_size = 0;

	if(_watch_size >= MAX_WATCH_LENGTH)
	{
		fprintf(stderr, "we cannot not afford making new stopwatch(name: %s)\n", name);
		return NULL;
	}

	// すでに同じ名前のストップヲッチが生成されていないかを確認する
	int i;
	for(i=0; i<_watch_size; ++i)
	{
		if(strcmp(name, _watches[i].name) == 0)
		{
			return &_watches[i];
		}
	}
	// ここまでくるということは,新しく作ろうとしている。
	// _watches[_watch_size] = Stopwatch();
	strcpy(_watches[_watch_size].name, name);
	//_watches[_watch_size].main_label = StopwatchLabel();
	strcpy(_watches[_watch_size].main_label.name, "main");
	_watches[_watch_size].main_label.status = STOP;
	_watches[_watch_size].sub_label_size = 0;

	return &_watches[_watch_size++];
}

StopwatchLabel *GenerateStopwatchLabel(Stopwatch *watch, char *name)
{
	const int MAX_SUB_LENGTH = 32;
	if(watch->sub_label_size >= MAX_SUB_LENGTH)
	{
		fprintf(stderr, "we cannot not afford making new stopwatch label(name: %s)\n", name);
		return NULL;
	}
	// すでにある名前であればそれを返却する
	int i;
	int label_len = watch->sub_label_size;
	for(i=0;i<label_len;++i)
	{
		if(strcmp(name, watch->sub_labels[i].name) == 0)
		{
			return &watch->sub_labels[i];
		}
	}
	// 新しくラベルを作成
	//watch->sub_labels[label_len] = StopwatchLabel();
	strcpy(watch->sub_labels[label_len].name, name);
	watch->sub_labels[label_len].status = STOP;

	return &watch->sub_labels[label_len++];
}

// main label が対象
void StopwatchStart(Stopwatch *watch)
{
	// もし前回の動作が停止なら、合計時間は0にする。
	StopwatchLabel *label = &(watch->main_label);
	switch(label->status)
	{
	case STOP:
		label->total_process_time = 0;
		label->total_system_time  = 0;
		label->total_real_time    = 0;
		break;
	case START:
		return;
	default:
		break;
	}
	// 現在の時間をラベルに保存する
	getrusage(RUSAGE_SELF, &label->start_time);
	clock_gettime(CLOCK_REALTIME, &label->spec_start_time);
	label->status = START;
}

void StopwatchPause(Stopwatch *watch)
{
	// もし前回の動作が停止なら、合計時間は0にする。
	StopwatchLabel *label = &(watch->main_label);
	if(label->status != START)
		return;

	// ここまでの時間を計上する。
	struct rusage cur_time;
	struct timespec spec_cur_time;
	getrusage(RUSAGE_SELF, &cur_time);
	clock_gettime(CLOCK_REALTIME, &spec_cur_time);

	label->total_process_time += (double)(cur_time.ru_utime.tv_sec - label->start_time.ru_utime.tv_sec)+(cur_time.ru_utime.tv_usec - label->start_time.ru_utime.tv_usec)*1.0E-6;
	label->total_system_time  += (double)(cur_time.ru_stime.tv_sec - label->start_time.ru_stime.tv_sec)+(cur_time.ru_stime.tv_usec - label->start_time.ru_stime.tv_usec)*1.0E-6;
	label->total_real_time    += (double)(spec_cur_time.tv_sec - label->spec_start_time.tv_sec)+(spec_cur_time.tv_nsec - label->spec_start_time.tv_nsec)*1.0E-9;
	label->status = PAUSE;
}

void StopwatchStop(Stopwatch *watch)
{
	StopwatchLabel *label = &(watch->main_label);
	if(label->status != START)
	{
		label->status = STOP;
		return;
	}

	// ここまでの時間を計上する。
	struct rusage cur_time;
	struct timespec spec_cur_time;
	getrusage(RUSAGE_SELF, &cur_time);
	clock_gettime(CLOCK_REALTIME, &spec_cur_time);

	label->total_process_time += (double)(cur_time.ru_utime.tv_sec - label->start_time.ru_utime.tv_sec)+(cur_time.ru_utime.tv_usec - label->start_time.ru_utime.tv_usec)*1.0E-6;
	label->total_system_time  += (double)(cur_time.ru_stime.tv_sec - label->start_time.ru_stime.tv_sec)+(cur_time.ru_stime.tv_usec - label->start_time.ru_stime.tv_usec)*1.0E-6;
	label->total_real_time    += (double)(spec_cur_time.tv_sec - label->spec_start_time.tv_sec)+(spec_cur_time.tv_nsec - label->spec_start_time.tv_nsec)*1.0E-9;
	label->status = STOP;
}

void StopwatchShow(Stopwatch *watch)
{
	printf("###############################################\n");
	printf("Time memory of '%s'\n", watch->name);

	StopwatchLabel *label = &(watch->main_label);
	printf("Total time :: real: %8.5lf // pro: %8.5lf // sys: %8.5lf \n", label->total_real_time, label->total_process_time, label->total_system_time);
	printf("-----------------------------------------------\n");
	printf("// sub memory\n");
	printf("// \n");
	printf("###############################################\n");
}







