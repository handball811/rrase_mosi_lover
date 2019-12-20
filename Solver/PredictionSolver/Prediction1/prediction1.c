#include<stdio.h>
#include<string.h>
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"

middle_predict_structure prediction1(middle_predict_structure* middle){
    int number=0; 
    int wordlength=middle->maxPartsLen;
    //printf("%s\n",middle->str);
    int j=0,i=0;
    int cnt=0;//どれぐらい埋めたかカウントする
    while(wordlength>2){//文字列の長さが2つ以下であれば諦めて次に回す
        
        while(number<(middle->partsNum[wordlength])){//次に探すものがなくなるまで繰り返す
           
            int memostr=0;//当てはまる場所のメモ用
            int memonum1,memonum2=0;//どの部分が埋まったかのメモ用
            int flag=0; //既に見つけてるかを判断するflag
            int length=0;
            int howlong=0;
            while(middle->unsettledPlace[j+1]!=0){ //middle.strから探す
                int k=0;
                for(k=0;k<=wordlength-(middle->unsettledPlace[j+1]-middle->unsettledPlace[j]);k++){
                    if((middle->str[middle->unsettledPlace[j]+k]==middle->parts[wordlength][number][0]) || (middle->str[middle->unsettledPlace[j]+k]=='x')){//もし一文字めが一緒であれば
                        for(i=1;i<wordlength;i++){   
                            if((middle->str[middle->unsettledPlace[j]+k+i]!=middle->parts[wordlength][number][i]) && (middle->str[middle->unsettledPlace[j]+k+i]!='x')){//異なる場所があったらループを抜ける
                                break;
                            }
                        }
                        if((i==wordlength) && (flag==0)){
                            flag=1;//見つけたフラグを立てる
                            memostr=middle->unsettledPlace[j]+k;//場所のメモ
                            memonum1=j;
                            memonum2=k;
                            //printf("%d\n",memostr);
                        }else if(i==wordlength){
                            flag=0;//悩ましいので次に回す
                        }
                    }
                }
                j+=2;//次に行く
            }
            howlong=j+1;
            j=0;//jのリセット
            if(flag==1){//もし1つだけ見つけられているのであれば、この部分は確定であることから決定してしまう
                int k=0;
                for(k=0;k<wordlength;k++){
                    middle->str[k+memostr]=middle->parts[wordlength][number][k];//strにpartを写す
                }
                k=memonum1;
                if(memonum2==0){
                    if(middle->unsettledPlace[k+1]-middle->unsettledPlace[k]!=wordlength){
                        middle->unsettledPlace[k]+=wordlength;
                    }else if(memonum2==0){
                        while(middle->unsettledPlace[k]!=0){
                            middle->unsettledPlace[k]=middle->unsettledPlace[k+2];
                            middle->unsettledPlace[k+1]=middle->unsettledPlace[k+3];
                            k++;
                        }
                    }
                }else{
                    if(middle->unsettledPlace[k+1]==middle->unsettledPlace[k]+memonum2+wordlength){
                        middle->unsettledPlace[k+1]-=wordlength;
                    }else{
                        int save1,save2,N,l;
                        N=k+4;
                        for(l=howlong;l<N;l++){
                            middle->unsettledPlace[l]=middle->unsettledPlace[l-2];
                            middle->unsettledPlace[l+1]=middle->unsettledPlace[l-1];
                        }
                        middle->unsettledPlace[k+3]=middle->unsettledPlace[k+1];
                        middle->unsettledPlace[k+1]=middle->unsettledPlace[k]+memonum2;
                        middle->unsettledPlace[k+2]=middle->unsettledPlace[k+1]+wordlength;
                    }
                }
                
                for(k=number;k<middle->partsNum[wordlength];k++){//決まったpartを消す
                    middle->parts[wordlength][k]=middle->parts[wordlength][k+1];
                }
                if(wordlength==middle->maxPartsLen){//最大長さ修正
                    int max=wordlength-1;
                    while(middle->partsNum[max]==0){
                        if(max==2)break;
                        max--;
                    }
                    middle->maxPartsLen=max;
                }

                cnt++;
                flag=0;//flagのリセット
            }
            number++;//次に行く
        }
        number=0;
        middle->partsNum[wordlength]-=cnt;//パーツの総数のリセット
        cnt=0;
        wordlength--;
    }
    return *middle;
}