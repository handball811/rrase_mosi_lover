#include <stdio.h>
#include "MT.h"
#include "input_v1.h"
#include "output_v1.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 400001

void QuestionGenerate(input_structure *in, output_structure *out){
    int i, j, cal = 0, x, *num_rand, max = 0;
    int num_len[50000];
    double lamda = 0.0923;
    char **S;
    int num, count[5] = {0};
    char s[5] = {'x', 'a', 'b', 'c', 'd'};
    //復元後の文字列を計画書にある確率分布にしたがって作成、擬似乱数にはメルセンヌツイスタを利用
    init_genrand((unsigned)time(NULL));
    for (i = 0; i < 2; i++)
    {
        num = genrand_int32() % (4) + 1;
        in->str[i] = s[num];
        count[num]++;
    }
    for (i = 2; i < MAX; i++)
    {
        num = genrand_int32() % (400000) + 1;
        switch (in->str[i - 2])
        {
        case 'a':
            switch (in->str[i - 1])
            {
            case 'a':
                if (num <= 26460.0 / 65926.0 * 400000.0)
                {
                    in->str[i] = s[1];
                }
                else if (num <= 39396.0 / 65926.0 * 400000.0)
                {
                    in->str[i] = s[2];
                }
                else if (num <= 52621.0 / 65926.0 * 400000.0)
                {
                    in->str[i] = s[3];
                }
                else
                {
                    in->str[i] = s[4];
                }
                break;
            case 'b':
                if (num <= 12999.0 / 32536.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 19529.0 / 32536.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 22779.0 / 32536.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'c':
                if (num <= 9839.0 / 32831.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 19828.0 / 32831.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 23086.0 / 32831.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'd':
                if (num <= 16365 / 47695 * 400000)
                    in->str[i] = s[1];
                else if (num <= 29616.0 / 47695.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 44616.0 / 47695.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        case 'b':
            switch (in->str[i - 1])
            {
            case 'a':
                if (num <= 16326.0 / 40833.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 24533.0 / 40833.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 32652.0 / 40833.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'b':
                if (num <= 8209.0 / 20316.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 12238.0 / 20316.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 14244.0 / 20316.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'c':
                if (num <= 3054.0 / 10087.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 6039.0 / 10087.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 7058.0 / 10087.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'd':
                if (num <= 15213.0 / 35726.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 27623.0 / 35726.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 32623.0 / 35726.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        case 'c':
            switch (in->str[i - 1])
            {
            case 'a':
                if (num <= 5804.0 / 14342.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 8642.0 / 14342.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 11474.0 / 14342.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'b':
                if (num <= 5764.0 / 14335.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 8605.0 / 14335.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 10009.0 / 14335.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'c':
                if (num <= 1449.0 / 4773.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 2864.0 / 4773.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 3342.0 / 4773.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'd':
                if (num <= 7076.0 / 14205.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 12777.0 / 14205.0 * 400000.0)
                    in->str[i] = s[2];
                else
                    in->str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        case 'd':
            switch (in->str[i - 1])
            {
            case 'a':
                if (num <= 17335.0 / 42987.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 25890.0 / 42987.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 34546.0 / 42987.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'b':
                if (num <= 13861.0 / 34739.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 20777.0 / 34739.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 24204.0 / 34739.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'c':
                if (num <= 13861.0 / 34739.0 * 400000.0)
                    in->str[i] = s[1];
                else if (num <= 20777.0 / 34739.0 * 400000.0)
                    in->str[i] = s[2];
                else if (num <= 24204.0 / 34739.0 * 400000.0)
                    in->str[i] = s[3];
                else
                    in->str[i] = s[4];
                break;
            case 'd':
                if (num <= (4333.0 / 8532.0) * 400000.0)
                    in->str[i] = s[1];
                else if (num <= (7710.0 / 8532.0 * 400000.0))
                    in->str[i] = s[2];
                else
                    in->str[i] = s[4];
                break;
            default:
                printf("calculation error.");
            }
            break;
        default:
            printf("calculation error.");
        }
    }
    in->str[MAX] = '\0';
    memcpy(out->ans, in->str, sizeof(in->str));
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
    for (i = 0; i < MAX; i++)
    {
        num = genrand_int32() % (336940) + 1;
        if (num <= 96510)
        {
            in->str[i] = s[0];
            num = genrand_int32() % (96510) + 1;
            if (num <= 58000)
            {
                i++;
                continue;
            }
            else if (num <= 81000)
            {
                in->str[i + 1] = s[0];
                i = i + 2;
            }
            else if (num <= 90500)
            {
                for (j = 1; j < 3 && (i + j) < MAX; j++)
                {
                    in->str[i + j] = s[0];
                }
                i = i + 3;
            }
            else if (num <= 94000)
            {
                for (j = 1; j < 4 && (i + j) < MAX; j++)
                {
                    in->str[i + j] = s[0];
                }
                i = i + 4;
            }
            else if (num <= 96000)
            {
                for (j = 1; j < 5 && (i + j) < MAX; j++)
                {
                    in->str[i + j] = s[0];
                }
                i = i + 5;
            }
            else if (num <= 96500)
            {
                for (j = 1; j < 6 && (i + j) < MAX; j++)
                {
                    in->str[i + j] = s[0];
                }
                i = i + 6;
            }
            else
            {
                for (j = 1; j < 7 && (i + j) < MAX; j++)
                {
                    in->str[i + j] = s[0];
                }
                i = i + 7;
            }
        }
    }
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
            S[cal][j] = out->ans[i + j];
        }
        S[cal][j] = '\0';
        i = num_len[cal] + i;
        cal++;
    }
    /*配列の順番を並び変えていく*/
    num_rand = malloc(sizeof(int) * (max + 1));
    for (i = 0; i <= max; i++)
    {
        num_rand[i] = i;
    }
    for (i = 0; i <= max; i++)
    {
        num = genrand_int32() % (max);
        x = num_rand[i];
        num_rand[i] = num_rand[num];
        num_rand[num] = x;
    }
    in->parts = malloc(sizeof(char *) * max);
    for (i = 0; i <= max; i++)
    {
        x = num_rand[i];
        in->parts[i] = malloc(sizeof(char) * (strlen(S[x]) + 1));
        memcpy(in->parts[i], S[x], sizeof(char) * strlen(S[x]));
    }
    for (i = 0; i <= max; i++)
    {
        free(S[i]);
    }
    free(S);
    free(num_rand);
    in->strLen = MAX;
    in->partsNum = max;
    out->ans_len = MAX;
    /*partsは動的な配列なので後でfreeする必要がある*/
}
int main(void){
    FILE *fp;
    fp=fopen("randtest.txt","w");
    int i;
    input_structure in;
    output_structure out;
    QuestionGenerate(&in, &out);
    for (i = 0; i < in.partsNum; i++){
        fprintf(fp,"%s\n",in.parts[i]);
        free(in.parts[i]);
    }
    fprintf(fp, "%s\n", out.ans);
    fprintf(fp, "%s\n", in.str);
    printf("out.ans_len:%d\n",out.ans_len);
    printf("in.strLen:%d\n", in.strLen);
    printf("in.partsNum:%d",in.partsNum);
    free(in.parts);
    fclose(fp);
}