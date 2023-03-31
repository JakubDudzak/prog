#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/*bool isNumber(char* number){
    for (int i = 0, len = strlen(number); i < len; ++i)
        if(!isdigit(number[i]))
            return false;
    return true;
}*/
/*int sum(char* number){
    int ret = 0;
    for (int i = 0, len = strlen(number); i < len; ++i)
        ret = ret + number[i]-'0';
    return ret;
}*/
int sum(unsigned long number){
    int ret = 0;
    if(number<0)
        return number;
    while (number>0){
        ret += number%10;
        number/=10;
    }
    if(ret>9)
        ret = sum((unsigned long)ret);
    return ret;
}
int main() {
    unsigned char got = 0;
    unsigned long ret = 0;
    do{
        got = getchar();
        if(isdigit(got))
            ret += got-'0';
    }while (got!='\n');

    printf("%d\n", sum(ret));
    return 0;
}
