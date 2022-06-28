#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 10

int seqSearch(int a[],int num);

int main() {
    int a[SIZE];
    int i,num;
    printf("Input 10 integer values: ");
    for( i=0; i<SIZE ; i++)
        scanf("%d", &a[i]);
    printf("Enter number is        : ");
    for( i=0; i<SIZE ; i++)
        printf("%d ", a[i]);
    printf("\nInput an integer that you want to find: ");
    scanf("%d",&num);

    i=seqSearch(a,num);
    if(i>=0) printf("The index of %d is %d",num,i);
    else if(i==-1) printf("Not Found");
    return 0;
}
int seqSearch(int a[],int num) {
    int i;
    for(i=0; i<SIZE; i++) {
        if(num==a[i]) return i;
    }
    return -1;
}
