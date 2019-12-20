#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"
#include "../../../DataStructure/OutputStructure/output_v1.h"
#include "../../ConfirmSolver/SolveCertainString.h"
#include "../../ConfirmSolver/CalculateCorrectAnswerRate.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void q_sort(int** numbers, int left, int right)
{
    int pivot, l_hold, r_hold;

    l_hold = left;
    r_hold = right;
    pivot = numbers[left][0];
    while (left < right)
    {
        while ((numbers[right][0] >= pivot) && (left < right))
            right--;
        if (left != right)
        {
            numbers[left][0] = numbers[right][0];
            numbers[left][1] = numbers[right][1];
            left++;
        }
        while ((numbers[left][0] <= pivot) && (left < right))
            left++;
        if (left != right)
        {
            numbers[right][0] = numbers[left][0];
            numbers[right][1] = numbers[left][1];
            right--;
        }
    }
    numbers[left][0] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        q_sort(numbers, left, pivot-1);
    if (right > pivot)
        q_sort(numbers, pivot+1, right);
}


int** placeSort(int* unsettledPlace,int* len){
  //配列確保
  int i  = 0;
  while(1){
    if(unsettledPlace[i] == 0){
      break;
    }
    i++;
  }
  int parts_len = i/2;
  *len = parts_len;

  int** parts = (int**)malloc(sizeof(int**)*(unsigned long)(parts_len));

  //空白の場所・大きさを代入
  for(i = 0; i < parts_len ; i++){
    parts[i] = (int*)malloc(sizeof(int*)*2);
    parts[i][0] = unsettledPlace[i*2+1] - unsettledPlace[i*2];
    parts[i][1] = unsettledPlace[i*2];
  }

  //並び替え
  q_sort(parts,0,parts_len-1);

  return parts;
}

void prediction2(middle_predict_structure* predict, output_structure* output){
  int distribution[4][4] = {{3,0,2,1},{3,0,1,2},{1,1,0,1},{2,1,-1,0}};
  int len = 0;
  int answer[2] = {1,0},answer_part_len=1;

  int** unsettledParts = placeSort(predict->unsettledPlace,&len);

  //未確定の各場所を走査
  for (int i = 0; i < len; i++){
    //j文字の部分文字列を探索
    for(int j = 1;j < predict->maxPartsLen+1;j++){

      //対象の部分文字列が未確定部分より大きければ終了
      if(j > unsettledParts[i][0]){
        break;
      }

      //j文字の各部分文字列を探索
      for(int k = 0;k < predict->partsNum[j];k++){
          int flag = 0;
          for(int l = 0;l < j;l++){
            if( (predict->str[unsettledParts[i][1]+l] != 'x' && predict->str[unsettledParts[i][1]+l] != predict->parts[j][k][l] )  ||  predict->parts[j][k][l] == 'x' ){
              flag = 1;
              break;
            }
          }
          if(flag == 1){continue;}

          //もし答えよりも最初の文字が当てはまる確率が高いなら
          if(( (distribution[predict->str[unsettledParts[i][1]-1]-97][predict->parts[j][k][0]-97] >
              distribution[predict->str[unsettledParts[i][1]-1]-97][predict->parts[answer[0]][answer[1]][0]-97] ) && unsettledParts[i][1] != 0 )
            || predict->parts[answer[0]][answer[1]][0] == 'x'){
              answer[0] = j,answer[1] = k,answer_part_len=j;
          //もし最初の文字が当てはまる確率が一緒で
          }else if(distribution[predict->str[unsettledParts[i][1]-1]-97][predict->parts[j][k][0]-97] ==
              distribution[predict->str[unsettledParts[i][1]-1]-97][predict->parts[answer[0]][answer[1]][0]-97]){
              //現在参照している文字列がanswerより大きければ
              if(j > answer[0]){
                answer[0] = j,answer[1] = k,answer_part_len=j;
              //文字列の長さが同じで次の文字がxでないなら
            }else if(predict->str[unsettledParts[i][1]+j] != 'x' && j == unsettledParts[i][0]){
                //最後の文字とその次の文字を比較
                if(distribution[predict->parts[j][k][j-1]-97][predict->str[unsettledParts[i][1]]-97] >
                    distribution[predict->parts[answer[0]][answer[1]][j-1]-97][predict->str[unsettledParts[i][1]]-97]){
                      answer[0] = j,answer[1] = k,answer_part_len=j; printf("!");
                }
              }
          }

      }
    }

    if( strncmp(predict->parts[answer[0]][answer[1]],"x",1)){
      //答えの挿入、partsの更新
      memcpy(predict->str + unsettledParts[i][1] ,predict->parts[answer[0]][answer[1]],(int)sizeof(char)*answer_part_len);
      //埋まった場所と使ったパーツの更新
      predict->parts[answer[0]][answer[1]] = "x";
      if(unsettledParts[i][0] > answer_part_len){
        unsettledParts[i][0] -= answer_part_len;
        unsettledParts[i][1] += answer_part_len;
        i--;
      }
    }
  }

  CalculateCorrectAnswerRate("Data/dat1_ref",predict->str,predict->strLen);

  for(int i=0;i<predict->strLen;i++){
      if(predict->str[i] == 'x'){
          predict->str[i] = 'a';
      }
  }

  strcpy(output->ans,predict->str);
  output->ans_len = predict->strLen;
}

//a->a,d,c,b
//b->a,d,b,c
//c->c以外は一定
//d->cはナシ,a,b,d
//a:0,b:1,c:2,d:3
/*
00 ('aa', [('a', 26460), ('b', 12936), ('c', 13225), ('d', 13305)]),
01 ('ab', [('a', 12999), ('b', 6530), ('c', 3250), ('d', 9757)]),
02 ('ac', [('a', 9839), ('b', 9989), ('c', 3258), ('d', 9745)]),
03 ('ad', [('a', 16365), ('b', 13251), ('d', 3179)]),
10 ('ba', [('a', 16326), ('b', 8207), ('c', 8119), ('d', 8181)]),
11 ('bb', [('a', 8209), ('b', 4029), ('c', 2006), ('d', 6072)]),
12 ('bc', [('a', 3054), ('b', 2985), ('c', 1019), ('d', 3029)]),
13 ('bd', [('a', 15213), ('b', 12410), ('d', 3103)]),
20 ('ca', [('a', 5804), ('b', 2838), ('c', 2832), ('d', 2868)]),
21 ('cb', [('a', 5764), ('b', 2841), ('c', 1404), ('d', 4362)]),
22 ('cc', [('a', 1449), ('b', 1397), ('c', 496), ('d', 1431)]),
23 ('cd', [('a', 7076), ('b', 5701), ('d', 1428)]),
30 ('da', [('a', 17335), ('b', 8555), ('c', 8656), ('d', 8441)]),
31 ('db', [('a', 13861), ('b', 6916), ('c', 3427), ('d', 10535)]),
33 ('dd', [('a', 4333), ('b', 3377), ('d', 822)])]
*/

/*[('aa', [('a', 26460), ('b', 12936), ('c', 13225), ('d', 13305)]), ('ab', [('a', 12999), ('b', 6530), ('c', 3250), ('d', 9757)]), ('ac', [('a', 9839), ('b', 9989), ('c', 3258), ('d', 9745)]), ('ad', [('a', 16365), ('b', 13251), ('d', 3179)]), ('ba', [('a', 16326), ('b', 8207), ('c', 8119), ('d', 8181)]), ('bb', [('a', 8209), ('b', 4029), ('c', 2006), ('d', 6072)]), ('bc', [('a', 3054), ('b', 2985), ('c', 1019), ('d', 3029)]), ('bd', [('a', 15213), ('b', 12410), ('d', 3103)]), ('ca', [('a', 5804), ('b', 2838), ('c', 2832), ('d', 2868)]), ('cb', [('a', 5764), ('b', 2841), ('c', 1404), ('d', 4362)]), ('cc', [('a', 1449), ('b', 1397), ('c', 496), ('d', 1431)]), ('cd', [('a', 7076), ('b', 5701), ('d', 1428)]), ('da', [('a', 17335), ('b', 8555), ('c', 8656), ('d', 8441)]), ('db', [('a', 13861), ('b', 6916), ('c', 3427), ('d', 10535)]), ('dd', [('a', 4333), ('b', 3377), ('d', 822)])]
[('aa', [('a', 26231), ('b', 12987), ('c', 13038), ('d', 13111)]), ('ab', [('a', 12945), ('b', 6623), ('c', 3252), ('d', 9734)]), ('ac', [('a', 9855), ('b', 9873), ('c', 3315), ('d', 9787)]), ('ad', [('a', 16233), ('b', 13183), ('d', 3275)]), ('ba', [('a', 16336), ('b', 8096), ('c', 8130), ('d', 8134)]), ('bb', [('a', 8184), ('b', 4087), ('c', 2081), ('d', 6222)]), ('bc', [('a', 3087), ('b', 3141), ('c', 1046), ('d', 3127)]), ('bd', [('a', 15277), ('b', 12312), ('d', 3047)]), ('ca', [('a', 5702), ('b', 2831), ('c', 2940), ('d', 2916)]), ('cb', [('a', 5698), ('b', 2978), ('c', 1482), ('d', 4343)]), ('cc', [('a', 1447), ('b', 1487), ('c', 487), ('d', 1427)]), ('cd', [('a', 7243), ('b', 5732), ('d', 1366)]), ('da', [('a', 17099), ('b', 8640), ('c', 8722), ('d', 8530)]), ('db', [('a', 13869), ('b', 6886), ('c', 3586), ('d', 10337)]), ('dd', [('a', 4238), ('b', 3451), ('d', 813)])]
[('aa', [('a', 26160), ('b', 13174), ('c', 12987), ('d', 12942)]), ('ab', [('a', 13295), ('b', 6540), ('c', 3191), ('d', 9909)]), ('ac', [('a', 9697), ('b', 9806), ('c', 3260), ('d', 9874)]), ('ad', [('a', 16374), ('b', 13113), ('d', 3354)]), ('ba', [('a', 16212), ('b', 8339), ('c', 8139), ('d', 8263)]), ('bb', [('a', 8164), ('b', 4026), ('c', 2109), ('d', 6138)]), ('bc', [('a', 3116), ('b', 3030), ('c', 1099), ('d', 2996)]), ('bd', [('a', 15236), ('b', 12310), ('d', 3000)]), ('ca', [('a', 5743), ('b', 2803), ('c', 2815), ('d', 2909)]), ('cb', [('a', 5715), ('b', 2903), ('c', 1462), ('d', 4239)]), ('cc', [('a', 1457), ('b', 1483), ('c', 520), ('d', 1419)]), ('cd', [('a', 7105), ('b', 5691), ('d', 1492)]), ('da', [('a', 17148), ('b', 8619), ('c', 8696), ('d', 8727)]), ('db', [('a', 13779), ('b', 6967), ('c', 3479), ('d', 10260)]), ('dd', [('a', 4475), ('b', 3371), ('d', 869)])]
[('aa', [('a', 26566), ('b', 12948), ('c', 13068), ('d', 13276)]), ('ab', [('a', 13025), ('b', 6503), ('c', 3318), ('d', 9671)]), ('ac', [('a', 9830), ('b', 9882), ('c', 3263), ('d', 9760)]), ('ad', [('a', 16371), ('b', 13125), ('d', 3422)]), ('ba', [('a', 16209), ('b', 8043), ('c', 8101), ('d', 8100)]), ('bb', [('a', 8094), ('b', 4119), ('c', 2018), ('d', 6078)]), ('bc', [('a', 3108), ('b', 3063), ('c', 1042), ('d', 3093)]), ('bd', [('a', 15340), ('b', 12170), ('d', 3028)]), ('ca', [('a', 5735), ('b', 2869), ('c', 2917), ('d', 2813)]), ('cb', [('a', 5665), ('b', 2893), ('c', 1473), ('d', 4346)]), ('cc', [('a', 1396), ('b', 1432), ('c', 465), ('d', 1477)]), ('cd', [('a', 7228), ('b', 5632), ('d', 1470)]), ('da', [('a', 17348), ('b', 8657), ('c', 8649), ('d', 8729)]), ('db', [('a', 13669), ('b', 6794), ('c', 3497), ('d', 10443)]), ('dd', [('a', 4444), ('b', 3476), ('d', 848)])]
*/
