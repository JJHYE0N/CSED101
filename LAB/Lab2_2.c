#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define PI 3.141592

int main() {
    double r;
    printf("�������� �Է��Ͻÿ�: ");
    scanf("%lf",&r);
    printf("�� �ѷ�: %lf\n",2*PI*r);
    printf("�� ����: %lf",PI*r*r);
    return 0;
}
