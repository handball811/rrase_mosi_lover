#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ReadDataFile.h"

// ファイルを開いて返す。
FILE* OpenFile(char* fileName){
    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        fprintf(stderr, "%s\n", "error: can't read file.");
        exit(1);
    }
    return fp;
}

// ファイルを読み込んでデータ構造体に格納していく。
void ReadFile(FILE* fp, input_structure* inputStructure){
    fscanf( fp , "%s" , inputStructure->str);
    inputStructure->strLen = strlen(inputStructure->str);

    inputStructure->parts = (char **)malloc(400010 * sizeof(char *));

    char str[10000];    // 部分文字列を一時的に格納しておくためのもの。
    int i = 0;
    while(fscanf( fp , "%s" , str) != EOF ){
        inputStructure->parts[i] = (char *)malloc((strlen(str)+1) * sizeof(char));  // 部分文字列の長さ分のメモリを確保。
        strcpy(inputStructure->parts[i], str);
        i++;
    }
    
    inputStructure->partsNum = i;
}

// 引数で受け取ったファイル名のファイルの内容をデータ構造体に格納する。
void GetStructureFromFile(char* fileName, input_structure* inputStructure){
    FILE *fp = OpenFile(fileName);
    ReadFile(fp, inputStructure);
    fclose(fp);
}
