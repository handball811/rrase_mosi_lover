#ifndef MODULES_STOPWATCH_V1
#define MODULES_STOPWATCH_V1

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

enum StopwatchStatus {
	STOP,
	START,
	PAUSE
};

typedef struct {
	char name[128];
	enum StopwatchStatus status;

	// Pause, Stopの時点で値が格納される
	double total_process_time;
	double total_system_time;
	double total_real_time;

	struct rusage start_time;
	struct timespec spec_start_time;
}StopwatchLabel;

typedef struct {
	char name[128];
	StopwatchLabel main_label;
	StopwatchLabel sub_labels[32];
	int sub_label_size;
} Stopwatch;

// 計測器のインスタンス返却　シングルトンであることを期待する
// 後々、並列処理にも対応
// 同じ名前であれば、保管しておく
Stopwatch *GenerateStopwatch(char *);
StopwatchLabel *GenerateStopwatchLabel(Stopwatch*, char*);

// 全体のスタート　ポーズ後もここから
void StopwatchStart(Stopwatch*);
void StopwatchLabelStart(StopwatchLabel*);

// 計測時間の一時的な停止
void StopwatchPause(Stopwatch*);
void StopwatchLabelPause(StopwatchLabel*);

// 計測の終了
void StopwatchStop(Stopwatch*);
void StopwatchLabelStop(StopwatchLabel*);

// 計測結果の出力
void StopwatchShow(Stopwatch*);

#endif