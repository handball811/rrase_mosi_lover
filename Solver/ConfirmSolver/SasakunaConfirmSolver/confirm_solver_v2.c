#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "confirm_solver_v2.h"
#include "../../../Modules/Stopwatch/stopwatch.h"

// 何文字目スタートか、文字列の長さが2^i

//
char sc_str[400100];
int sc_bef[400100] = {0};
// hash -> last pos
int sc_hash[10000000] = {0};
// pos -> num(16)(比べるよう)
ull sc_pos[400100] = {0};
int sc_used[400100] = {0};
// その地点を含めないxのその地点前までの合計
int sc_xsize[400100] = {0};
int sc_str_len = 0;

void _merge_sort(int *index, int *nums, int *work, int size)
{
	if(size==1)
		return;
	int half = size/2;
	_merge_sort(index, nums, work, half);
	_merge_sort(index+half, nums+half, work+half, size-half);
	int top = 0;
	int bot = half;
	int pos = 0;
	while(top != half || bot != size)
	{
		if(top==half || (bot < size && nums[top] < nums[bot]))
		{
			work[pos] = nums[bot]*100000+index[bot];
			++bot;
		}
		else
		{
			work[pos] = nums[top]*100000+index[top];
			++top;
		}
		++pos;
	}
	for(top=0;top<size;++top)
	{
		index[top] = work[top]%100000;
		nums[top] = work[top]/100000;
	}
}

void merge_sort(char **strs, int str_len)
{
	int i,j,k;
	char *ret[100010] = {0};
	int index[100010] = {0};
	int nums[100010] = {0};
	int work[100010] = {0};
	printf("wariate\n");
	for(i=0;i<str_len;++i)
	{
		index[i] = i;
		j = 0;
		k=0;
		while(strs[i][j] != '\0')
		{
			//if(strs[i][j]=='c')
			++k;
			++j;
		}
		nums[i] = k;
	}
	printf("merge start\n");
	_merge_sort(&index[0], &nums[0], &work[0], str_len);
	for(i=0;i<str_len;++i)
	{
		ret[i] = strs[index[i]];
	}
	for(i=0;i<str_len;++i)
	{
		strs[i] = ret[i];
		//printf("%d %s\n",nums[i], ret[i]);
	}
}

void SCNodeInit(char *, const int, const int);
void SCMatches(input_structure*,const int);

void SCSolver(input_structure *input, const int do_merge_sort, const int show_debug)
{
	// input の値を変更する方針で変更していく。
	// show_debugが付いて入れば時間を表示する。
	// マージソートは適当絵そんなに早くないので市内設定も可能なようにしておく。
	const int sc_size = 10;
	Stopwatch *st = GenerateStopwatch("SasakunaConfirm");
	StopwatchLabel *st_init = GenerateStopwatchLabel(st, "init");
	StopwatchLabel *st_main = GenerateStopwatchLabel(st, "main");

	// 計測スタート
	StopwatchStart(st);
	StopwatchLabelStart(st_init);
	if(do_merge_sort)
		merge_sort(input->parts, input->partsNum);
	SCNodeInit(input->str, sc_size, 1);
	StopwatchLabelStop(st_init);
	StopwatchLabelStart(st_main);
	SCMatches( input, sc_size);
	StopwatchLabelStop(st_main);
	StopwatchStop(st);
	if(show_debug)
		StopwatchShow(st);
}

void SCNodeInit(char *str, const int sc_size, const int sc_used_init)
{
	int i,j;
	ull init_index;
	// xの数がこの値以上なら遷移先の候補に入れない
	const ull XBORDER = 12;
	ull x_num = 0;

	ull sc_mod = 1;
	for(i=0;i<sc_size;++i)
		sc_mod *= 5;
	const ull sc_init_len = sc_mod + 1000;
	for(init_index=0;init_index<=sc_init_len;++init_index)
	{
		sc_hash[init_index] = -1;
	}
	for(i=0;i<=400100;++i)
	{
		sc_bef[i] = -1;
		sc_xsize[i] = 0;
	}
	if(sc_used_init)
		for(i=0;i<=400100;++i)
			sc_used[i] = 1;
	/*
	memset(sc_bef, -1, 400050*4);
	memset(sc_used, 0, 400050*4);
	memset(sc_hash, -1, 10000000*4);
	*/
	ull k = 0;
	sc_str_len = 0;
	for(i=0;i<sc_size;++i)
	{
		k *= 5;
		sc_xsize[i+1] = sc_xsize[i];
		if(str[i] == 'x')
		{
			++x_num;
			++sc_xsize[i+1];
		}
		k += (str[i]=='x'?4:(ull)str[i]-'a');
		++sc_str_len;
	}
	j = 0;
	while(str[i] != '\0')
	{
		sc_xsize[i+1] = sc_xsize[i];
		// もしXBORDER以上のxが出現しているなら、候補に追加しない
		// また、sc_usedですでに使われているなら、これも追加しない
		if(x_num < XBORDER && sc_used[i])
		{
			sc_bef[j] = sc_hash[k];
			sc_hash[k] = (int)j;
		}
		//printf("%d\n",k);
		k *= 5;
		if(str[i]=='x')
		{
			++x_num;
			++sc_xsize[i+1];
		}
		k += (str[i]=='x'?4:(ull)str[i]-'a');
		if(k/sc_mod == 4)
			--x_num;
		k %= sc_mod;
		++j;
		++i;
		++sc_str_len;
	}
	strcpy(&sc_str[0], str);
	sc_bef[j] = sc_hash[k];
	sc_hash[k] = (int)j;

	k = 0;
	for(i=0;i<16; ++i)
	{
		k <<= 4;
		k += (ull)(str[i]=='x'?15:1<<(int)(str[i]-'a'));
	}
	j = 0;
	while(str[i]!='\0')
	{
		sc_pos[j] = k;
		k <<= 4;
		k += (ull)(str[i]=='x'?15:1<<(int)(str[i]-'a'));
		++j;
		++i;
	}
	for(i=0;i<16; ++i)
	{
		sc_pos[j] = k;
		k <<= 4;
		k += (ull)(str[i]=='x'?15:1<<(int)(str[i]-'a'));
		++j;
	}
	/*
	for(i=0;i<=16;++i)
	{
		printf("%3d ", sc_bef[i]);
	}
	*/
}
//int mp[100000] = {0};

void SCMatches(
	input_structure *input,
	const int sc_size)
{
	/*
	時間計測を行うための部分
	本番では絶対に削除！
	*/
	Stopwatch *st = GenerateStopwatch("conf");
	StopwatchLabel *st_init = GenerateStopwatchLabel(st, "init");
	StopwatchStart(st);
	StopwatchLabelStart(st_init);
	/*
	*/
	const int mp_size = 1 << (sc_size);
	const int STR_LEN_BORDER = 18;
	char **strs = input->parts;
	int strs_len = input->partsNum;
	input->partsNum = 0;


	ull set_once;

	int i,j,k,a,b,c,d,e,f,ans;
	int *pos_pointer;
	int s_len;

	int mp[mp_size];
	char *str;
	ull *set;
	int hash;
	int p_set;
	int lasts_len = 0;

	char *curs[40000];
	int hash_hist[40000];
	int str_len[40000] = {0};
	// 0個目に長さ、1〜Nに圧縮文字
	ull sets[40000][8]={0};
	int cur_len = 0;
	int step=0;
	// 初期化、長さの満たないものはパスする
	//printf("Init\n");
	// 当てはまる相対確率の高いところを決めるための確率分布
	printf("Init\n");
	int sc_mod = 1;
	for(i=0;i<sc_size;++i)
		sc_mod *= 5;

	for(i=0; i<strs_len; ++i)
	{
		hash = 0;
		str = strs[i];
		//printf("%s\n", str);
		for(j=0;j<sc_size && str[j] != '\0'; ++j)
		{
			hash *= 5;
			hash += (str[j]-'a');
		}
		if(j == sc_size)
		{
			p_set = 1;
			// ハッシュ以降の文字の圧縮
			while(str[j] != '\0')
			{
				set_once = 0;
				for(k=0;k<16;++k)
				{
					set_once <<= 4;
					if(str[j] != '\0')
					{
						set_once |= (ull)1<<(str[j]-'a');
						++ j;
					}
				}
				sets[cur_len][p_set++] = set_once;
			}
			if(j < STR_LEN_BORDER)
			{
				input->parts[input->partsNum++] = str;
				continue;
			}
			hash_hist[cur_len] = hash;
			curs[cur_len]   = str;
			str_len[cur_len] = j;
			sets[cur_len][0] = (ull)p_set;
			++cur_len;
		}
		else
		{
			input->parts[input->partsNum++] = str;
		}
	}
	/**/

	StopwatchLabelStop(st_init);

	/**/
	int first_d;
	while(cur_len)
	{
		first_d = 0;

		printf("Cur Len %d\n", cur_len);
		lasts_len = 0;
		char title[] = "step0";
		title[4] += (char)step;
		StopwatchLabel *st_step = GenerateStopwatchLabel(st, title);
		StopwatchLabelStart(st_step);
		// 唯一のところが見つかったら当てはめる
		// 当てはまらなかったら、lastsに追加
		// Hashの構成を構築
		for(i=0;i<cur_len;++i)
		{
			// ハッシュ構成の作成(余り多くなかったら記録するべきかな？)
			// sc_size >= 10 あたりから、このハッシュ作成が重荷になってるかも？
			ans = -1;
			mp[0] = hash_hist[i];
			a = 1;
			b = 1;
			c = mp[0];
			// mp[n]のnの1フラグの個数だけXがある。
			// 簡単にxがある一定上ならやらないとかできないかなー
			for(j=0;j<sc_size;++j)
			{
				hash = (4-c%5)*b;
				f = a;
				for(k=0;k<a;++k)
				{
					mp[f++] = mp[k]+hash;
				}
				a <<= 1;
				b *= 5;
				c /= 5;
			}
			// ハッシュ以降の値の圧縮
			set = sets[i];
			// 一致する場所を検索する。2個目が見つかった時点で終了
			b = (int)set[0];
			s_len = str_len[i];
			e = s_len-1;
			
			// 1024回＝＞2000回 * 6000~8000 = 1.6*10^7
			//--a;
			for(j=0;j<a;++j)
			{
				pos_pointer = sc_hash+mp[j];
				d = *pos_pointer;

				//最初から-1のものが半分から1/3
				if(d==-1)
					++first_d;
				while(d+1)
				{
					if(sc_used[d])
					{
						if(sc_used[d+e])
						{
							c = d + sc_size;
							for(k=1;k<b;++k)
							{
								if((sc_pos[c]&set[k]) != set[k])
									break;
								c += 16;
							}
							if(k == b)
							{
								if(ans+1)
								{
									ans = -2;
									break;
								}
								else
									ans = d;
							}
						}
						*pos_pointer = d;
						pos_pointer = &sc_bef[d];
					}
					d = sc_bef[d];
				}
				if(!(ans+2))
				{
					break;
				}
				*pos_pointer = d;
			}
			// ans == -1 なら、複数候補があるので次に回す
			if(ans+2)
			{
				b = ans;
				strncpy(&sc_str[b], curs[i], (long unsigned)s_len);
				memset(&sc_used[b], 0, (long unsigned)s_len<<2);
			}
			else
			{
				curs[lasts_len] = curs[i];
				hash_hist[lasts_len] = hash_hist[i];
				str_len[lasts_len] = str_len[i];
				p_set = (int)sets[i][0];
				for(j=0;j<p_set;++j)
					sets[lasts_len][j] = sets[i][j];
				++lasts_len;
			}
		}
		printf("DSIZE %d\n", first_d);
		if(lasts_len == cur_len)
			break;
		cur_len = lasts_len;
		step++;
		StopwatchLabelStop(st_step);
	}
	for(i=0;i<cur_len;++i)
	{
		input->parts[input->partsNum++] = curs[i];
	}
	strcpy(input->str, sc_str);
	//memcpy(result.open, sc_used, (long unsigned)sc_str_len*4);
	/**/

	StopwatchStop(st);
	StopwatchShow(st);

	/**/
}
