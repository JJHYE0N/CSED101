#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define PI 3.141592

int main() {
    double r;
    printf("반지름을 입력하시오: ");
    scanf("%lf",&r);
    printf("원 둘레: %lf\n",2*PI*r);
    printf("원 넓이: %lf",PI*r*r);
    return 0;
}
