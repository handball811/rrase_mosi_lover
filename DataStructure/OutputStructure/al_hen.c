#include<stdio.h>
#include<string.h>
#include "output_v1.h"
#define MAX 400002

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

int get_edit_distance(output_structure *ls, output_structure *rs){
    char ans1[MAX],ans2[MAX];
    int p,q,r,i,j;
    //printf("%s",num1);
    ans1[0]='#';
    ans2[0]='#';
    for(i=1;i<MAX;i++){
        ans1[i]=ls->ans[i-1];
        ans2[i]=rs->ans[i-1];
    }
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
                r=str1[j-1]+check(ans1[i],ans2[j]);
                str2[j]=min(p,q,r);
                /*printf("p:%d\n",p);
                printf("q:%d\n", q);
                printf("r:%d\n", r);
                printf("%d",str2[j]);*/
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
                r = str2[j-1] + check(ans1[j], ans2[i]);
                str1[j] = min(p, q, r);
                /*printf("p:%d\n", p);
                printf("q:%d\n", q);
                printf("r:%d\n", r);
                printf("%d",str1[j]);*/
        }
     }
    }
    return str2[MAX-1];
}

