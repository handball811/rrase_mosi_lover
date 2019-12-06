#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"
#include "../../../DataStructure/OutputStructure/output_v1.h"
#include <string.h>
#include <stdio.h>

output_structure prediction2(middle_predict_structure* predict){
  int distribution[4][4] = {{3,0,2,1},{3,0,1,2},{1,1,0,1},{2,1,-1,0}};
  output_structure output;
  int predict_parts_len=0,answer=0,answer_part_len=0;
  int parts_len; //各パーツの長さ
  //確定していない部分を順に埋める
  for(int i = 0;i < (*predict).predict_len;i+=2){

    if( (*predict).predict[i] == 0){

    }else{
      predict_parts_len = (*predict).predict[i+1]-(*predict).predict[i];//確定していない部分の長さ
      answer = (*predict).range[0];
      answer_part_len = (*predict).range[1]-(*predict).range[0];

      for(int j = 0;j < (*predict).range_len-1;j++){ //各パーツを順に当てはめる
        parts_len = (*predict).range[j+1]-(*predict).range[j];

        if(parts_len > predict_parts_len){
          continue;
        }else{
            for(int k = 0; k < parts_len;k++){
              if((*predict).str[(*predict).predict[i+k]] != 'x'  &&  (*predict).str[(*predict).predict[i]+k] != (*predict).parts[(*predict).range[j]+k]){
                //printf("break j=%d,k=%d, %c != %c\n",j,k,(*predict).str[(*predict).predict[i+k]],(*predict).parts[(*predict).range[j+k]]);
                break;
              }

              if(k==0){
                if(distribution[(*predict).str[(*predict).predict[i]-1] - 97][(*predict).parts[(*predict).range[j]] - 97] >
                  distribution[(*predict).str[(*predict).predict[i]-1] - 97][(*predict).parts[answer] - 97] &&
                  (*predict).str[(*predict).predict[i]] != (*predict).parts[(*predict).range[j+k]])
                {
                  answer = (*predict).range[j];
                  answer_part_len = parts_len;
                  //printf("k=0 %d\n",answer);
                }
              }else{
                if(distribution[(*predict).parts[(*predict).range[j+k-1]] - 97][(*predict).parts[(*predict).range[j+k]] - 97] >
                  distribution[(*predict).parts[(*predict).range[j+k-1]] - 97][(*predict).parts[answer+k] - 97 ])
                {
                  answer = (*predict).range[j];
                  answer_part_len = parts_len;
                  //printf("k=%d %d\n",k,answer);
                  break;
                }
              }

            }
          }
      }
    }
    //答えの挿入、partsの更新
    //answerはpartsに対するインデックス
    if(((*predict).parts[answer]) != 'x'){
      memcpy((*predict).str + (*predict).predict[i] , &((*predict).parts[answer]),(int)sizeof(char)*answer_part_len);

      for(int l = 0; l < answer_part_len;l++){
        (*predict).parts[answer+l] = 'x';
      }
      if(answer_part_len < predict_parts_len){
        //printf("parts_len %d,%d\n",i,answer_part_len);
        (*predict).predict[i] += answer_part_len;
        i-=2;
      }
      //printf("%d %s %s\n",answer,(*predict).parts,(*predict).str);
    }

  }

  strcpy(output.ans,(*predict).str);
  output.ans_len = (*predict).str_len;

  return output;
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
