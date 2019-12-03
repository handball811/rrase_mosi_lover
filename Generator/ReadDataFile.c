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

void ReadFile(FILE *fp, input_structure* inputInfo){
    fscanf( fp , "%s" , inputInfo->str);
    inputInfo->strLen = strlen(inputInfo->str);

    inputInfo->parts = (char **)malloc(400010 * sizeof(char *));

    char str[10000];
    int i = 0;
    while(fscanf( fp , "%s" , str) != EOF ){
        inputInfo->parts[i] = (char *)malloc((strlen(str)+1) * sizeof(char));
        strcpy(inputInfo->parts[i], str);
        i++;
    }
    
    inputInfo->partsNum = i;
}


// 引数で受け取ったファイル名のファイルを開き、データ構造体を返す。
input_structure GetStructureFromFile(char *fileName)
{
    input_structure inputInfo;
    FILE *fp = OpenFile(fileName);
    ReadFile(fp, &inputInfo);
    fclose(fp);

    return inputInfo;
}
