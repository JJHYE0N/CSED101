#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int add(int x, int y)
{
    return x+y;
}

float average(int x,int y)
{
    return (float)(x+y)/2;
}

void printResult(int x,int y,int sum, float avg)
{
    printf("The sum of %d and %d is %d\n",x,y,x+y);
    printf("The average of numbers is %.1f",avg);
}

int main() {
    int num1,num2,s;
    float a;
    printf("Enter two integers: ");
    scanf("%d %d",&num1,&num2);
    s=add(num1,num2);
    a=average(num1,num2);
    printResult(num1,num2,s,a);
    return 0;
}
