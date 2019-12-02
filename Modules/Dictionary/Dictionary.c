#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"


DictionaryUnitManager *RehashDictionary(DictionaryUnitManager *pre, unsigned int bin_size)
{
	//printf("Refashing\n");
	//ShowDictionary(pre);
	DictionaryUnitManager *post = (DictionaryUnitManager*)malloc(sizeof(DictionaryUnitManager));
	post->bin = (DictionaryUnit*)malloc(sizeof(DictionaryUnit)*bin_size);
	post->bin_size = bin_size;
	post->total_size = 0;

	unsigned int i, j;
	for(i=0;i<pre->bin_size; ++i)
	{
		for(j = 0; j < pre->bin[i].unit_size; ++j)
		{
			SetDictionaryManager(post, pre->bin[i].str[j], pre->bin[i].units[j]);
		}
	}
	//ShowDictionary(post);
	return post;
}

Dictionary *GenerateDictionary()
{
	DictionaryUnitManager zero;
	zero.bin_size = 0;
	Dictionary *post = (Dictionary*)malloc(sizeof(DictionaryUnitManager));
	post->manager = RehashDictionary(&zero, 4);
	return post;
}
void SetDictionary(Dictionary *dict, char *key, void* value)
{
	unsigned int hash = HashString(key);
	//printf("Set Hash Num %d\n", hash);
	hash %= dict->manager->bin_size;
	unsigned int next = dict->manager->bin[hash].unit_size;
	// すでに存在しているかを確認する
	unsigned int i;
	for(i=0; i<next; ++i)
	{
		if(strcmp(dict->manager->bin[hash].str[i], key)==0)
			break;
	}
	dict->manager->bin[hash].str[i] = key;
	dict->manager->bin[hash].units[i] = value;
	if(i==next)
	{
		//printf("append new key, value\n");
		++dict->manager->bin[hash].unit_size;
		++dict->manager->total_size;
	}
	if(i>=8 || dict->manager->total_size > dict->manager->bin_size * 4)
	{
		DictionaryUnitManager *d = dict->manager;

		dict->manager = RehashDictionary(dict->manager, dict->manager->bin_size * 2);
		FreeDictionaryManager(d);
	}
}
void SetDictionaryManager(DictionaryUnitManager *dict, char *key, void* value)
{
	unsigned int hash = HashString(key);
	//printf("Set Hash Num %d\n", hash);
	hash %= dict->bin_size;
	unsigned int next = dict->bin[hash].unit_size;
	// すでに存在しているかを確認する
	unsigned int i;
	for(i=0; i<next; ++i)
	{
		if(strcmp(dict->bin[hash].str[i], key)==0)
			break;
	}
	dict->bin[hash].str[i] = key;
	dict->bin[hash].units[i] = value;
	if(i==next)
	{
		//printf("append new key, value\n");
		++dict->bin[hash].unit_size;
		++dict->total_size;
	}
}
void* GetDictionary(Dictionary *dict, char *key)
{
	return GetDictionaryManager(dict->manager, key);
}
void* GetDictionaryManager(DictionaryUnitManager *dict, char *key)
{
	unsigned int hash = HashString(key);
	//printf("Get Hash Num %d\n", hash);
	hash %= dict->bin_size;
	unsigned int next = dict->bin[hash].unit_size;
	// すでに存在しているかを確認する
	unsigned int i;
	//printf("gunit size is %d\n", next);
	for(i=0; i<next; ++i)
	{
		if(strcmp(dict->bin[hash].str[i], key)==0)
			break;
	}
	if(i==next)
	{
		printf("Found no answer\n");
		return NULL;
	}
	return dict->bin[hash].units[i];
}

void FreeDictionary(Dictionary *dict)
{
	FreeDictionaryManager(dict->manager);
	free(dict);
}
void FreeDictionaryManager(DictionaryUnitManager *dict)
{
	free(dict->bin);
	free(dict);
}

unsigned int HashString(char *str)
{
	unsigned int ret = 0;
	int i=0;
	while(str[i] != '\0')
	{
		ret += (unsigned int)str[i];
		++i;
	}
	return ret;
}

void ShowDictionary(DictionaryUnitManager *dict)
{
	printf("---------- Dictionary Information ----------\n");
	printf("total_size: %d\n", dict->total_size);
	printf("bin_size  : %d\n\n", dict->bin_size);

	unsigned int i, j;
	unsigned int bin_size = dict->bin_size;
	for(i=0;i<bin_size;++i)
	{
		unsigned int unit_len = dict->bin[i].unit_size;
		printf("\tunit_size: %d\n", unit_len);
		for(j=0;j<unit_len;++j)
		{
			printf("\t\t%s\n", dict->bin[i].str[j]);
		}
	}
}
unsigned int GetDictionarySize(Dictionary *dict)
{
	return dict->manager->total_size;
}

