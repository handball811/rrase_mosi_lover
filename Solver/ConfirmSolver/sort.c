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