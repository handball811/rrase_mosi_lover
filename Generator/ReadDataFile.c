#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ReadDataFile.h"

FILE* OpenFile(char* fileName){
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "%s\n", "error: can't read file.");
        exit(1);
    }
    return fp;
}

void ReadFile(FILE* fp, input_structure* inputStructure){
    fscanf( fp , "%s" , inputStructure->str);
    inputStructure->strLen = strlen(inputStructure->str);

    inputStructure->parts = (char **)malloc(400010 * sizeof(char *));

    char str[10000];
    int i = 0;
    while(fscanf( fp , "%s" , str) != EOF ){
        inputStructure->parts[i] = (char *)malloc((strlen(str)+1) * sizeof(char));
        strcpy(inputStructure->parts[i], str);
        i++;
    }
    
    inputStructure->partsNum = i;
}


// 引数で受け取ったファイル名のファイルを開き、データ構造体に格納
void GetStructureFromFile(char* fileName, input_structure* inputStructure)
{
    FILE *fp = OpenFile(fileName);
    ReadFile(fp, inputStructure);
    fclose(fp);
}
