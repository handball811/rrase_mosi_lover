#include <stdio.h>
#include "MT.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 400000

int main(int argc,char *argv[]){
    int i, j,cal=0,max=0,x,*num_rand;
    int num_len[50000];
    double lamda = 0.0923;
    char str[400001],str2[400001];
    char **S;
    int num, count[5] = {0};
    char s[5] = {'x', 'a', 'b', 'c', 'd'};
    if(argc!=3){
        printf("ファイル名を二つ拡張子をつけてに入力してください。一つ目が答え、二つ目が入力になります。");
        return -1;
    }
    //fp1には文字列の答えを格納、fp2には復元前の文字列を出力
    FILE *fp1,*fp2;
    fp1 = fopen(argv[1], "w");
    if (fp1 == NULL){
        printf("file not opne");
        return -1;
    }
    fp2 = fopen(argv[2], "w");
    if (fp2 == NULL)
    {
        printf("file not opne");
        return -1;
    }
    //復元後の文字列を計画書にある確率分布にしたがって作成、擬似乱数にはメルセンヌツイスタを利用
    init_genrand((unsigned)time(NULL));
    for(i=0;i<2;i++){
        num = genrand_int32() % (4) + 1;
        str[i] = s[num];
        count[num]++;
    }
    for (i = 2; i < 400000; i++){
        num = genrand_int32() % (400000) + 1;
        switch (str[i - 2]){
        case 'a':
            switch (str[i - 1]){
            case 'a':
                if (num <= 26460.0 / 65926.0 * 400000.0){
                    str[i] = s[1];
                }else if (num <= 39396.0 / 65926.0 * 400000.0){
                    str[i] = s[2];
                }else if (num <= 52621.0 / 65926.0 * 400000.0){
                    str[i] = s[3];
                }else{
                    str[i] = s[4];
                }
                break;
            case 'b':
                if (num <= 12999.0 / 32536.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 19529.0 / 32536.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 22779.0 / 32536.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'c':
                if (num <= 9839.0 / 32831.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 19828.0 / 32831.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 23086.0 / 32831.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'd':
                if (num <= 16365 / 47695 * 400000)
                    str[i] = s[1];
                else if (num <= 29616.0 / 47695.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 44616.0 / 47695.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        case 'b':
            switch (str[i - 1])
            {
            case 'a':
                if (num <= 16326.0 / 40833.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 24533.0 / 40833.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 32652.0 / 40833.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'b':
                if (num <= 8209.0 / 20316.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 12238.0 / 20316.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 14244.0 / 20316.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'c':
                if (num <= 3054.0 / 10087.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 6039.0 / 10087.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 7058.0 / 10087.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'd':
                if (num <= 15213.0 / 35726.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 27623.0 / 35726.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 32623.0 / 35726.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        case 'c':
            switch (str[i - 1])
            {
            case 'a':
                if (num <= 5804.0 / 14342.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 8642.0 / 14342.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 11474.0 / 14342.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'b':
                if (num <= 5764.0 / 14335.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 8605.0 / 14335.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 10009.0 / 14335.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'c':
                if (num <= 1449.0 / 4773.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 2864.0 / 4773.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 3342.0 / 4773.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'd':
                if (num <= 7076.0 / 14205.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 12777.0 / 14205.0 * 400000.0)
                    str[i] = s[2];
                else
                    str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        case 'd':
            switch (str[i - 1])
            {
            case 'a':
                if (num <= 17335.0 / 42987.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 25890.0 / 42987.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 34546.0 / 42987.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'b':
                if (num <= 13861.0 / 34739.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 20777.0 / 34739.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 24204.0 / 34739.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'c':
                if (num <= 13861.0 / 34739.0 * 400000.0)
                    str[i] = s[1];
                else if (num <= 20777.0 / 34739.0 * 400000.0)
                    str[i] = s[2];
                else if (num <= 24204.0 / 34739.0 * 400000.0)
                    str[i] = s[3];
                else
                    str[i] = s[4];
                break;
            case 'd':
                if (num <= (4333.0 / 8532.0) * 400000.0)
                    str[i] = s[1];
                else if(num <= (7710.0 / 8532.0 * 400000.0))
                    str[i] = s[2];
                else
                    str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        default:
            printf("calculation error.");
        }
    }
    str[400000] = '\0';
    memcpy(str2,str,sizeof(str));
    //復元後の文字列を出力
    fprintf(fp1,"%s\n", str);
    fclose(fp1);
    /*虫食いされた文字列の作成
            (x)が58000個
            (x)×2が23000個
            (x)×3が9500個
            (x)×4が3500個
            (x)×5が2000個
            (x)×6が500個
            (x)×7が10個
            (x)×8個以上は0個と仮定、ただしすべて図から読み取った概数
            よって、xの文字列は長さ１を含めて96510個と考え、文字列中のxは2個と仮定する
            そうするとxは159570個になるので、逆にx以外の文字は240430個
    */
    for(i=0;i<400000;i++){
        num = genrand_int32() % (336940) + 1;
        if(num <= 96510){
            str[i]=s[0];
            num = genrand_int32() % (96510) + 1;
            if(num <= 58000){
                i++;
                continue;
            }else if(num <= 81000){
                str[i+1]=s[0];
                i=i+2;
            }else if(num <= 90500){
                for(j = 1; j < 3 && (i + j) <= 399999; j++){
                    str[i+j]=s[0];
                }
                i=i+3;
            }else if (num <= 94000){
                for (j = 1; j < 4 && (i + j) <= 399999; j++){
                    str[i+j]=s[0];
                }
                i=i+4;
            }else if (num <= 96000){
                for (j = 1; j < 5 && (i + j) <= 399999; j++){
                    str[i+j]=s[0];
                }
                i=i+5;
            }else if (num <= 96500){
                for (j = 1; j < 6 && (i + j) <= 399999; j++){
                    str[i + j] = s[0];
                }
                i=i+6;
            }else{
                for (j = 1; j < 7 && (i + j) <= 399999; j++){
                    str[i + j] = s[0];
                }
                i=i+7;
            }
        }
    }
    fprintf(fp2,"%s\n",str);
    /*
    切ったときの配列の長さは指数分布になっていると仮定して計算
    図より平均λ=0.0923の指数分布と仮定する。
    逆関数法によって指数分布を生成する。
    */
    for (i = 0; i < MAX; i++)
    {
        num_len[i] = -1.0 / lamda * log(1.0 - genrand_real3());
        while (num_len[i] == 0)
        {
            num_len[i] = -1.0 / lamda * log(1.0 - genrand_real3());
        }
        cal = num_len[i] + cal;
        if (cal > MAX)
        {
            max = i;
            break;
        }
    }
    S = malloc(sizeof(char *) * max);
    for (i = 0; i <= max; i++)
    {
        S[i] = malloc(sizeof(char) * (num_len[i] + 1));
    }
    cal = 0;
    for (i = 0; i < MAX;)
    {
        for (j = 0; j < num_len[cal] && (i + j) < MAX; j++)
        {
            S[cal][j] = str2[i + j];
        }
        S[cal][j] = '\0';
        i = num_len[cal] + i;
        cal++;
    }
    /*配列の順番を並び変えていく*/
        num_rand=malloc(sizeof(int)*(max+1));
    for(i=0;i<=max;i++){
        num_rand[i]=i;
    }
    for(i=0;i<=max;i++){
        num = genrand_int32() % (max);
        x=num_rand[i];
        num_rand[i]=num_rand[num];
        num_rand[num]=x;
    }
    for (i = 0; i <= max; i++){
        x=num_rand[i];
        fprintf(fp2,"%s\n",S[x]);
    }
    for (i = 0; i <=max; i++)
    {
        free(S[i]);
    }
    free(S);
    fclose(fp2);
    free(num_rand);
    return 0;
}