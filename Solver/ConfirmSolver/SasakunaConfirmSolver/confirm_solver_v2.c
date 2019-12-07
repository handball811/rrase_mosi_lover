#include <stdio.h>
#include <string.h>
#include "confirm_solver_v2.h"

// 何文字目スタートか、文字列の長さが2^i
const ull sc_size = 10;
const ull sc_mod  = 9765625;
//const ull sc_size = 9;
//const ull sc_mod  = 1953125;
//const ull sc_size = 8;
//const ull sc_mod  = 390625;
//const int sc_size = 4;
//const int sc_mod  = 625;
//
int sc_bef[10000000] = {0};
// hash -> last pos
int sc_hash[10000000] = {0};
// pos -> num(16)(比べるよう)
ull sc_pos[10000000] = {0};



void SCNodeInit(char *str)
{
	int i,j;
	/*
	for(i=0;i<=10000000;++i)
	{
		sc_bef[i] = -1;
		sc_hash[i] = -1;
	}*/
	memset(sc_bef, -1, 40000000);
	memset(sc_hash, -1, 40000000);
	ull k = 0;
	for(i=0;i<sc_size;++i)
	{
		k *= 5;
		k += (str[i]=='x'?4:str[i]-'a');
	}
	j = 0;
	while(str[i] != '\0')
	{
		sc_bef[j] = sc_hash[k];
		sc_hash[k] = j;
		//printf("%d\n",k);
		k *= 5;
		k += (str[i]=='x'?4:str[i]-'a');
		k %= sc_mod;
		++j;
		++i;
	}
	sc_bef[j] = sc_hash[k];
	sc_hash[k] = j;

	k = 0;
	for(i=0;i<16; ++i)
	{
		k <<= 4;
		k += (str[i]=='x'?15:1<<(str[i]-'a'));
	}
	j = 0;
	while(str[i]!='\0')
	{
		sc_pos[j] = k;
		k <<= 4;
		k += (str[i]=='x'?15:1<<(str[i]-'a'));
		++j;
		++i;
	}
	for(i=0;i<16; ++i)
	{
		sc_pos[j] = k;
		k <<= 4;
		k += (str[i]=='x'?15:1<<(str[i]-'a'));
		++j;
	}
	/*
	for(i=0;i<=16;++i)
	{
		printf("%3d ", sc_bef[i]);
	}
	*/
}
int mp[100000] = {0};
int SCMatch(char *str)
{
	int ret = -1;
	int i,j;
	int kp = 0;
	ull k = 0;
	for(i=0;i<sc_size&&str[i] != '\0';++i)
	{
		k *= 5;
		k += str[i]-'a';
	}
	if(i != sc_size)
		return ret;
	// Matchするのを探すのにかかる時間を検証する
	mp[0] = k;
	kp = 1;
	for(i=0;i<sc_size;++i)
	{
		for(j=0;j<(1<<i);++j)
		{
			mp[j+(1<<i)] = mp[j] + (4-(mp[j]/kp)%5)*kp;
		}
		kp *= 5;
	}
	ull sets[8] = {0};
	int p_set=0;
	i = sc_size;
	while(str[i]!='\0')
	{
		for(j=0;j<16;++j)
		{
			sets[p_set] <<= 4;
			if(str[i]!='\0')
			{
				sets[p_set] |= 1<<(str[i]-'a');
				++i;
			}
		}
		++p_set;
	}
	int s_len = i;

	for(i=0;i<(1<<sc_size);++i)
	{
		mp[i] = sc_hash[mp[i]];
		//++ret;
		while(mp[i] != -1)
		{
			// ここで実際に一致しているかを検証する
			for(j=0;j<p_set;++j)
			{
				if((sc_pos[mp[i]+sc_size+(j<<4)]&sets[j]) != sets[j])
					break;
			}
			if(j==p_set)
			{
				if(ret==-1)
				{
					ret = mp[i];
					//ret = s_len;
				}
				else
				{
					return -1;
				}
			}
			mp[i] = sc_bef[mp[i]];
		}
	}
	return ret;
}

