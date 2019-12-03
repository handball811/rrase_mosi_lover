#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"


int main()
{

	// この辞書型は、Valueが実体を持っていないと、値が消えてしまう(ポインタ管理)
	Dictionary *dict = GenerateDictionary();
	printf("current size %d\n", dict->manager->total_size);
	assert(dict->manager->total_size == 0);

	char key1[] = "hello";
	int val1    = 52;

	// 値の設定が可能なのかを検証
	SetDictionary(dict, key1, &val1);
	printf("current size %d\n", dict->manager->total_size);
	assert(dict->manager->total_size == 1);
	// printf("val %ls\n",((int*)GetDictionary(dict, key1)));
	assert(*((int*)GetDictionary(dict, key1)) == val1);

	// 上書きできるかの確認
	int val2    = 153;
	SetDictionary(dict, key1, &val2);
	assert(GetDictionarySize(dict) == 1);
	assert(*((int*)GetDictionary(dict, key1)) == val2);

	// 複数追加されても、取得できるのか
	char* keys[] = {
		"key1",
		"key2",
		"key3"
	};
	int vals[16];
	int i;
	for(i=0;i<3;++i)
	{
		vals[i] = i*10000;
		SetDictionary(dict, keys[i], &vals[i]);
	}
	assert(*((int*)GetDictionary(dict, keys[0])) == vals[0]);
	assert(*((int*)GetDictionary(dict, keys[1])) == vals[1]);
	assert(*((int*)GetDictionary(dict, keys[2])) == vals[2]);
	assert(GetDictionarySize(dict) == 4);

	int v[32];
	char key[32][16];
	for (i=0;i<32;++i)
	{
		strcpy(key[i], "00000");
		key[i][0] += i/10;
		key[i][1] += i%10;
		v[i] = i*10;
		SetDictionary(dict, key[i], &v[i]);
		printf("%s -> %d (%d)\n", key[i], v[i], GetDictionarySize(dict));
	}

	FreeDictionary(dict);
	return 0;
}