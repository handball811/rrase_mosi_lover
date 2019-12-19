#include<stdio.h>
#include"input_v1.h"

int main(void){
    input_structure out;
    out=change();
    printf("%c\n",out.str[0]);
    return 0;
}
