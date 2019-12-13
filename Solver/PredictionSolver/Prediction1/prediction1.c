#include<stdio.h>
#include<string.h>
#include "../../../DataStructure/MiddleStructure/middle_predict_v1.h"

middle_predict_structure prediction1(middle_predict_structure* middle){
    int partlength=0; 
    //printf("%s\n",middle->str);
    int j=0,i=0;
    int cnt=0;//どれぐらい埋めたかカウントする
    while(partlength!=(middle->partsNum)){//次に探すものがなくなるまで繰り返す
        int memostr=0;//当てはまる場所のメモ用
        int flag=0; //既に見つけてるかを判断するflag
        int length=0;
        while(j<middle->str_len){ //middle.strから探す
            //printf("%d %c %s\n",j,middle->str[j],middle->parts[partlength]);
            if((middle->str[j]==middle->parts[partlength][0]) || (middle->str[j]=='x')){//もし一文字めが一緒であれば
                for(i=0;i<strlen(middle->parts[partlength]);i++){
                    if((middle->str[j+i]!=middle->parts[partlength][i]) && (middle->str[j+i]!='x')){//異なる場所があったらループを抜ける
                    //printf("%c %c %d %lu\n",middle->str[j+i],middle->parts[partlength][i],i,strlen(middle->parts[partlength]));
                        break;
                    }
                }
                if((i==(int)strlen(middle->parts[partlength])) && (flag==0)){
                    flag=1;//見つけたフラグを立てる
                    memostr=j;//場所のメモ
                    //printf("%d\n",memostr);
                }else if(i==(int)strlen(middle->parts[partlength])){
                    flag=0;//悩ましいので次に回す
                }
                //printf("%d\n",flag);
            }
            j++;//次に行く
        }
        j=0;//jのリセット
        if(flag==1){//もし1つだけ見つけられているのであれば、この部分は確定であることから決定してしまう
            int k=0;
            for(k=0;k<strlen(middle->parts[partlength]);k++){
                //printf("%c %c \n",middle->str[k+memostr],middle->parts[partlength][k]);
                middle->str[k+memostr]=middle->parts[partlength][k];//strにpartを写す
                //printf("%c %c \n",middle->str[k+memostr],middle->parts[partlength][k]);
            }
            for(k=partlength;k<middle->partsNum-1;k++){//決まったpartを消す
                //printf("%s %s\n",middle->parts[k],middle->parts[k+1]);
                middle->parts[k]=middle->parts[k+1];
                //printf("%s %s\n",middle->parts[k],middle->parts[k+1]);
            }
            cnt++;
            flag=0;//flagのリセット
            //printf("%s\n",middle->str);
        }
        partlength++;//次に行く
    }
    middle->partsNum-=cnt;
    return *middle;
}