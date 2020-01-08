#include<stdio.h>
#include<string.h>
#include "output_v1.h"
#define MAX 400001

int str1[MAX], str2[MAX];

int check(char a,char b){
    if(a==b){
        return 0;
    }else{
        return 1;
    }
}

int min(int a,int b,int c){
    if(a<b){
        if(c<a){
            return c;
        }else{
            return a;
        }
    }else{
        if(c<b){
            return c;
        }else{
            return b;
        }
    }
}

int get_edit_distance(output_structure &ls, &rs)
{
    //printf("%s",num1);
    for(i=0;i<MAX;i++){
        str1[i]=i;
    }  
    for(i=1;i<MAX;i++){
        /*if(i%100==0){
            printf("%d\n",i);
        }*/
        if(i%2!=0){
            for(j=0;j<MAX;j++){
                if(j==0){
                    str2[j]=i;
                    continue;
                }
                p=str1[j]+1;
                q=str2[j-1]+1;
                r=str1[j-1]+check(ls->ans[j],rs->ans[i]);
                str2[j]=min(p,q,r);
            } 
        }else{
        for (j = 0; j < MAX; j++)
            {
                if (j == 0)
                {
                    str1[j] = i;
                    continue;
                }
                p = str2[j] + 1;
                q = str1[j - 1] + 1;
                r = str2[j-1] + check(ls->ans[j], rs->ans[i]);
                str1[j] = min(p, q, r);
        }
     }
    }
    printf("%d",str1[MAX-1]);
    return 0;
}