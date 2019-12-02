#include "../../DataStructure/OutputStructure/output_v1.h"
#define MAX(x,y) ((x) > (y) ? (x) : (y))

int _snake(int k, int y, char *l, char *r, int l_len, int r_len)      //  対角線が存在する場合は、移動する
{
	int x = y - k;
    while( x < l_len && y < r_len && l[x] == r[y] ) {
        ++x;
        ++y;
    }
    return y;
}

int get_edit_distance(output_structure *l, output_structure *r)
{
	int i,k;
	// 初期の代入
	char *l_ans = l->ans;
	int l_len = l->ans_len;
	char *r_ans = r->ans;
	int r_len = r->ans_len;
	// a,b,c,d以外の値が入っていたら -1 を返す
	for(i=0;i<l_len;++i)
		if(l_ans[i]!='a'&&l_ans[i]!='b'&&l_ans[i]!='c'&&l_ans[i]!='d')
			return -1;
	for(i=0;i<r_len;++i)
		if(r_ans[i]!='a'&&r_ans[i]!='b'&&r_ans[i]!='c'&&r_ans[i]!='d')
			return -1;
	//編集距離を測ってみる
	static int fp[1000000];
	for(i=0;i<1000000;++i)
	{
		fp[i]=0;
	}
	int offset = l_len+1;
	int DELTA = r_len-l_len;
	for(i=0; fp[DELTA + offset] != r_len; ++i) {
        for(k = -i; k < DELTA; ++k)
            fp[k + offset] = _snake(k, MAX(fp[k-1+offset] + 1, fp[k+1+offset]), l_ans, r_ans, l_len, r_len);
        for(k = DELTA + i; k > DELTA; --k)
            fp[k + offset] = _snake(k, MAX(fp[k-1+offset] + 1, fp[k+1+offset]), l_ans, r_ans, l_len, r_len);
        fp[DELTA + offset] = _snake(k, MAX(fp[DELTA-1+offset] + 1, fp[DELTA+1+offset]), l_ans, r_ans, l_len, r_len);
    }
    return DELTA + (i - 1) * 2;
}