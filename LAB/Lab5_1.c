#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

float calc_average(int x,int y);
float calc_grade(float z);

int main() {
    int a,b;
    printf("Enter your midterm score: ");
    scanf("%d",&a);
    printf("Enter your final score: ");
    scanf("%d",&b);
    float avg=calc_average(a,b);
    printf("Average: %.1f",avg);
    char grd=calc_grade(avg);
    printf("\nGrade: %c",grd);

    return 0;
}

float calc_average(int x,int y)
{
    return (float)(x+y)/2;
}
float calc_grade(float z)
{
    if(z>=90) return 'A';
    else if(80<=z&&z<90) return 'B';
    else if(70<=z&&z<80) return 'C';
    else if(60<=z&&z<70) return 'D';
    else if(z<60) return 'F';
}