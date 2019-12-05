#include "SolveCertainString.h"
#include <stdio.h>
#include <string.h>


void swapStr(char** a, char** b){
    char* tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition (char** array, int left, int right) {
  int i, j, pivot;
  i = left;
  j = right + 1;
  pivot = left;   // 先頭要素をpivotとする

  do {
    do { i++; } while (strlen(array[i]) > strlen(array[pivot]));
    do { j--; } while (strlen(array[pivot]) > strlen(array[j]));

    if (i < j) { swapStr(&array[i], &array[j]); }
  } while (i < j);

  swapStr(&array[pivot], &array[j]);   //pivotを更新

  return j;
}

// クイックソート
void quicksort (char** array, int left, int right) {
  int pivot;

  if (left < right) {
    pivot = partition(array, left, right);
    quicksort(array, left, pivot-1);   // pivotを境に再帰的にクイックソート
    quicksort(array, pivot+1, right);
  }
}

// バブルソート
void BubbleSort(char** parts, int partsNum){
    for(int i = 0; i < partsNum-1; i++) {
        for(int j = i+1; j < partsNum; j++) {
            if(strlen(parts[i]) < strlen(parts[j])) {
                swapStr(&parts[i], &parts[j]);
            }
        }
    }
}

// 部分文字列をソートする。
void SortParts(input_structure* inputStructure){
    quicksort(inputStructure->parts, 0, inputStructure->partsNum-1);
    //BubbleSort(inputStructure->parts, inputStructure->partsNum);
}


void SolveCertainString(input_structure* inputStructure) {
    int minimumCharacterNum = 10; // ここで当てはめる単語の最小の文字数

    SortParts(inputStructure);  //まず文字数でソート

    printf("%s\n", inputStructure->parts[0]);
    printf("%s\n", inputStructure->parts[1]);
    printf("%s\n", inputStructure->parts[2]);
    

    // queueに入れていく

    // 大きいものから順番に当てはめていく

    // 当てはまらなかったらqueueに入れ直し

    // 1周の中で一度も当てはめる操作がなければ終了し、下流工程へ。

}