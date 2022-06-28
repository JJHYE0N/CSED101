#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

void triangle(int a, int b, float *perimeter, float *area);
void print(float perimeter, float area);

int main() {

    int a,b;
    float perimeter,area;
    printf("Enter two integer sides: ");
    scanf("%d%d",&a,&b);

    triangle(a,b,&perimeter,&area);
    print(perimeter,area);

    return 0;
}

void triangle(int a, int b, float *perimeter, float *area)
{
    float c=sqrt(a*a+b*b);
    *perimeter = a+b+c;
    *area=1/2*(a+b);
    return;
}
void print(float perimeter, float area)
{
    printf("Perimeter: %f\n",perimeter);
    printf("Area     : %f",area);
    return;
}