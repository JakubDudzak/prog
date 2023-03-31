#include <stdio.h>


short int check(double c, int t, int n,const int d[],const int s[]){
    double t2 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] + c < 0) return 1;
        t2 += d[i]  / (s[i] + c);
    }
    if(t2==t)
        return 0;
    if(t2>t)
        return 1;
    if(t2<t)
        return -1;
    return 0;
}
//t = s/v+c

double binarySearchAnswer(double min, double max, int n, int t,int d[], int s[])
    {
    double  mid = (min+max)/2;
    short int checkMid = check(mid,t,n,d,s);

    if(checkMid == 0){
        return mid;
    }
    if(checkMid == 1){
            return binarySearchAnswer(mid,max,n,t,d,s);
        }
    else{
        return binarySearchAnswer(min,mid,n,t,d,s);
    }
}

int main(){
    int n;
    int t;
    double min = 1000;
    double max = 1001000;
    scanf("%d %d",&n, &t);

    int d[1000], s[1000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &d[i], &s[i]);
        if(min>s[i])
            min = s[i];
    }
    min = 0 - min;
    printf("%f",binarySearchAnswer(min,max,n,t,d,s));
    return 0;
}