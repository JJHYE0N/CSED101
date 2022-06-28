#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int n,sum=0;
    printf("Enter a number: ");
    scanf("%d",&n);
    while(n>0)
    {
        sum+=n%10;
        n/=10;
    }
    printf("The sum of digits is %d",sum);
    return 0;
}
