#include<stdio.h>
#include<string.h>
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"

middle_predict_structure prediction1(middle_predict_structure* middle){
    int partlength=0; 
    //printf("%s\n",middle->str);
    int j=0,i=0,k=0,l=0;
    int memo=0;
    int flag=0;//確定か確定じゃないか判断

    while(middle->unsettledPlace[i+1]!=0){//決まっていない部分がなくなるまで繰り返す
        int wordlength=middle->unsettledPlace[i+1]-middle->unsettledPlace[i];//決まっていない単語の長さ
        if(wordlength>2){//2文字以下の単語はここでは決まらないと考える
            for(j=0;j<middle->partsNum[wordlength];j++){
                for(k=0;k<wordlength;k++){
                    if(middle->parts[wordlength][j][k]!=middle->unsettledPlace[i+wordlength]){
                        break;
                    }
                }
                if(k==wordlength && flag==0){
                    flag=1;//見つけてることを示す
                    memo=j;
                }else if(flag==1){
                    flag=0;//もう見つけてるなら不確定
                    break;//探す必要がないので飛ばす
                }
            }
            if(flag==1){//見つけられたのなら確定
                for(j=wordlength;j<middle->strLen;j++){
                    middle->str[j]=middle->unsettledPlace[j];//決まったものを文字列に入れる
                }
                middle->partsNum[wordlength]--;//一つ減らす
                if(wordlength==middle->maxPartsLen){//maxが変わるのなら修正
                    int maxlength=wordlength-1;
                    for(l=maxlength-1;l>0;l--){
                        if(middle->partsNum[l]!=0){
                            middle->maxPartsLen=l;
                            break;
                        }
                    }
                }
                if(memo!=middle->partsNum[wordlength]){//当てはまらない文字列の情報修正
                    for(j=memo;j<middle->partsNum[wordlength]-1;j++){
                        middle->parts[wordlength][j]=middle->parts[wordlength][j+1];
                    }
                }
                k=0;
                while(middle->unsettledPlace[k+i]!=0){//xの場所のリセット
                    middle->unsettledPlace[k+i]=middle->unsettledPlace[k+i+1];
                    k++;
                }
            }
        }
        i++;//次のものを探す
    }
    return *middle;
}