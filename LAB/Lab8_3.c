#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 6

void bubble_sort(int a[],int size);
void swap(int *x,int *y);
void print_array(int a[],int size);
void input_array(int a[],int size);

int main() {
    int ary[MAX];

    printf("Input integer numbers to be sorted: ");
    input_array(ary,MAX);

    printf(" Unsorted: ");
    print_array(ary,MAX);

    printf("\n------------------------------------");
    bubble_sort(ary,MAX);
    printf("\n------------------------------------\n");

    printf("   Sorted: ");
    print_array(ary,MAX);

    return 0;
}

void bubble_sort(int a[],int size) {
    for(int i=0;i<size-1; i++) {
        for(int j=size-1;j>=i;j--) {
            if(a[j]<a[j-1]) swap( &a[j] ,&a[j-1]); }
        printf("\n[step  %d]: ",i+1);
        print_array(a,MAX);
    }
}
void swap(int *x,int *y) {
    int temp;
    temp= *x;
    *x= *y;
    *y= temp;
}
void print_array(int a[],int size) {
    for (int i=0; i<size; i++) {
        printf("%3d ",a[i]);
    }
}
void input_array(int a[],int size) {
    for (int i=0; i<size; i++) {
        scanf("%3d",&a[i]);
    }
}