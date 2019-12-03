#ifndef MODULES_DICTIONARY_DICTIONARY
#define MODULES_DICTIONARY_DICTIONARY

typedef struct {
	char* str[32];
	void* units[32];
	unsigned int unit_size;
} DictionaryUnit;
typedef struct {
	DictionaryUnit *bin;
	unsigned int bin_size;
	unsigned int total_size;
} DictionaryUnitManager;
typedef struct {
	DictionaryUnitManager *manager;
} Dictionary;


Dictionary *GenerateDictionary();

void SetDictionary(Dictionary*, char*, void*);
void SetDictionaryManager(DictionaryUnitManager*, char*, void*);
void* GetDictionary(Dictionary*, char*);
void* GetDictionaryManager(DictionaryUnitManager*, char*);

DictionaryUnitManager *RehashDictionary(DictionaryUnitManager*, unsigned int bin_size);

unsigned int HashString(char*);

void FreeDictionaryManager(DictionaryUnitManager*);
void FreeDictionary(Dictionary*);

void ShowDictionary(DictionaryUnitManager*);

unsigned int GetDictionarySize(Dictionary*);

#endif