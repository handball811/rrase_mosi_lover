#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "confirm_solver_v3.h"
#include "../../../Modules/Stopwatch/stopwatch.h"

double sc_ex[400100][4] = {0};
double l2r[4][4] = {0};


void SCSolverInitV3(input_structure *input)
{
	//
	int i,j,k,a,b;
	int max_x_len = 0;
	int cur_x_len = 0;
	char *str = input->str;	//
	double mp[32][4][4]={0};
	double perc[32][4]={0};
	double pp[32][4][4][32][4]={0};
	for(i=0;i<4;++i)
		for(j=0;j<4;++j)
			l2r[i][j] = 0.0;
	int x;
	while(str[i] != '\0')
	{
		if(str[i]=='x')
			cur_x_len ++;
		else
		{
			if(max_x_len < cur_x_len)
			{
				max_x_len = cur_x_len;
			}
			cur_x_len = 0;
		}
		if(str[i+1] != '\0' && str[i] != 'x' && str[i+1] !='x')
		{
			l2r[str[i]-'a'][str[i+1]-'a'] += 1;
		}
		++i;
	}
	if(max_x_len < cur_x_len)
	{
		max_x_len = cur_x_len;
	}
	printf("%d\n", max_x_len);
	for(i=0;i<4;++i)
	{
		k = (l2r[i][0]+l2r[i][1]+l2r[i][2]+l2r[i][3]);
		for(j=0;j<4;++j)
			l2r[i][j]/=k;
	}
	
	for(i=0;i<4;++i)
	{
		for(j=0;j<4;++j)
		{
			printf("%lf ", l2r[i][j]);
		}
		printf("\n");
	}
	//
	for(x=1;x<=max_x_len;++x)
	{
		for(i=0;i<4;++i)
		{
			
			for(j=0;j<4;++j)
				perc[0][j]=l2r[i][j];
			
			for(j=0;j<x;++j)
			{
				for(a=0;a<4;++a)
				{
					perc[j+1][a] = 0;
				}
				for(k=0;k<4;++k)
				{
					for(a=0;a<4;++a)
					{
						mp[j][k][a] = perc[j][k] * l2r[k][a];
						perc[j+1][a] += mp[j][k][a];
					}
				}
			}
			/*
			for(a=0;a<4;++a)
			{
				printf("      ");
				for(k=0;k<=x;++k)
				{
					printf(" %.3lf", perc[k][a]);
				}
				printf("\n");
			}*/
			
			for(j=0;j<4;++j)
			{

				for(k=0;k<4;++k)
				{
					if(j==k)
						pp[x][i][j][x][k] = 1.0;
					else
						pp[x][i][j][x][k] = 0.0;
				}
				for(k=x-1;k>=0;--k)
				{
					for(a=0;a<4;++a)
					{
						pp[x][i][j][k][a] = 0.0;
						for(b=0;b<4;++b)
						{
							if(perc[k+1][b] > 0.00000001)
								pp[x][i][j][k][a] += pp[x][i][j][k+1][b]/perc[k+1][b]*mp[k][a][b];
						}
					}
				}
				
				for(k=0;k<x;++k)
				{
					for(a=0;a<4;++a)
					{
						if(pp[x][i][j][k][a] > 0.00000001)
							pp[x][i][j][k][a] = log(pp[x][i][j][k][a]);
						else
							pp[x][i][j][k][a] = -10000;
					}
				}
				/* ここまで */
				/*
				printf("     %c",'a'+i);
				for(k=0;k<x;++k)
				{
					printf("     x");
				}
				printf("     %c\n",'a'+j);
				for(a=0;a<4;++a)
				{
					printf("      ");
					for(k=0;k<=x;++k)
					{
						printf(" %.3lf", pp[x][i][j][k][a]);
					}
					printf("\n");
				}*/
			}
		}
		//getchar();
	}
	
	printf("Input Pre\n");
	a = 0;
	cur_x_len = 0;
	while(str[i] != '\0')
	{
		if(str[i]=='x')
		{
			cur_x_len ++;
		}
		else
		{
			if(cur_x_len)
			{
				if(a)
				{
					for(j=0;j<cur_x_len;++j)
					{
						for(k=0;k<4;++k)
						{
							sc_ex[a+j+1][k] = pp[cur_x_len][str[a]-'a'][str[i]-'a'][j][k];
						}
					}
					//printf("%d %d %d %c %c\n", cur_x_len, a, i, str[a], str[i]);
				}
				cur_x_len = 0;
			}
			a = i;// スタート地点(セーフポイント)
		}
		++i;
	}
	printf("End Init\n");
	return;
}

void SCProcessV3(input_structure *input, int *used, double first, double constant)
{
	// ここのはのちの調査ように行われる
	int i,j,k,a;
	int m;
	int str_l;
	char *str = input->str;
	char *part;

	int x_cor;
	double cor;
	int x_size;
	ull filter[5] = {0};
	for(i=0;i<input->partsNum;++i)
	{
		// 文字列の長さ確認とフィルターの作成
		j = 0;
		part = input->parts[i];
		filter[0] = filter[1] = filter[2] = filter[3] = filter[4] = 0;
		k = 1;
		while(part[j] != '\0')
		{
			filter[part[j]-'a'] |= k;
			filter[4] |= k;
			k <<= 1;
			++j;
		}
		k >>= 1;
		if(j < 12)
			continue;
		str_l = j;
		// kの位置までビットがきたら終了
		// sc_usedは使い回す
		// よって、V2が完了済み前提
		m = 0;
		j = 0;
		while(str[j] != '\0')
		{
			if(used[j])
			{
				m <<= 1;
				m |= 1;
				if(str[j] != 'x')
					m &= filter[str[j]-'a'];
				if(m&k)
				{
					// 候補のひとつ！
					/*
					printf("%s\n", part);
					printf("%.*s\n", str_l, &str[j-str_l]);
					getchar();*/
					cor = 0.0;
					for(a = 0; a < str_l; ++a)
					{
						if(str[j+a-str_l+1] == 'x')
						{
							cor += sc_ex[j+a-str_l+1][part[a]-'a'];
						}
					}
					/*
					printf("%s\n",part);
					printf("%.*s\n", str_l, &str[j-str_l+1]);
					printf("%.*s\n", str_l, &ans[j-str_l+1]);
					printf("%d %lf %d %s\n", x_cor, cor, x_size, part);
					getchar();*/
					// ここで指定された計算式を満たすなら埋める
					if(cor >= str_l*first+constant)
					{
						strncpy(&str[j-str_l+1], part, (long unsigned)str_l);
						memset(&used[j-str_l+1], 0, (long unsigned)str_l<<2);
					}
				}
			}
			else
			{
				m = 0;
				while(!used[j])
					++j;
				continue;
			}
			++j;
		}
	}
	return;
}

void SCAnalysis(input_structure *input, int *used, char *ans)
{
	// ここのはのちの調査ように行われる
	int i,j,k,a;
	int m;
	int str_l;
	char *str = input->str;
	char *part;

	int x_cor;
	double cor;
	int x_size;
	double born_rate;
	ull filter[5] = {0};
	FILE *fp = fopen("./history/analysis.txt", "w");
	for(i=0;i<input->partsNum;++i)
	{
		// 文字列の長さ確認とフィルターの作成
		j = 0;
		part = input->parts[i];
		filter[0] = filter[1] = filter[2] = filter[3] = filter[4] = 0;
		k = 1;
		// この文字列自体が生じる確率も算出する。
		while(part[j] != '\0')
		{
			filter[part[j]-'a'] |= k;
			filter[4] |= k;
			k <<= 1;
			++j;
		}
		k >>= 1;
		if(j < 12)
			continue;
		str_l = j;
		if(part[0]=='a')
			born_rate = log(.4);
		else if(part[0]=='b')
			born_rate = log(.3);
		else if(part[0]=='b')
			born_rate = log(.1);
		else
			born_rate = log(.2);
		for(j=1;j<str_l;++j)
		{
			born_rate += log(l2r[part[j-1]-'a'][part[j]-'a']);
		}
		// kの位置までビットがきたら終了
		// sc_usedは使い回す
		// よって、V2が完了済み前提
		m = 0;
		j = 0;
		while(str[j] != '\0')
		{
			if(used[j])
			{
				m <<= 1;
				m |= 1;
				if(str[j] != 'x')
					m &= filter[str[j]-'a'];
				if(m&k)
				{
					// 候補のひとつ！
					/*
					printf("%s\n", part);
					printf("%.*s\n", str_l, &str[j-str_l]);
					getchar();*/
					x_cor = 0;
					cor = 0.0;
					x_size = 0;
					for(a = 0; a < str_l; ++a)
					{
						if(str[j+a-str_l+1] == 'x')
						{
							++x_size;
							cor += sc_ex[j+a-str_l+1][part[a]-'a'];
							if(ans[j+a-str_l+1] == part[a])
								++x_cor;
						}
					}
					/*
					printf("%s\n",part);
					printf("%.*s\n", str_l, &str[j-str_l+1]);
					printf("%.*s\n", str_l, &ans[j-str_l+1]);
					printf("%d %lf %d %s\n", x_cor, cor, x_size, part);
					getchar();*/
					fprintf(fp, "%d %lf %d %s %lf\n", x_cor, cor, x_size, part, born_rate);
				}
			}
			else
			{
				m = 0;
				while(!used[j])
					++j;
				continue;
			}
			++j;
		}
	}
	fclose(fp);
	return;
}

void SCSolverV3(input_structure *input, int *used, char *ans)
{
	// まずXの部分の各文字になる確率をLogにして表示
	SCSolverInitV3(input);
	//SCAnalysis(input, used, ans);
	//95%精度のものを埋めてみる
	//SCProcessV3(input, used, -1.2862323, 15.34873);
	//SCSolverInitV3(input);
	SCAnalysis(input, used, ans);
	printf("Solver V3 End\n");
	return;
}

