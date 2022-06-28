#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 20

void print_matrix(int a[MAX_SIZE][MAX_SIZE],int n);

int main() {
    int n,i,j;
    int a[MAX_SIZE][MAX_SIZE];
    printf("Enter the size of square: ");
    scanf("%d",&n);

    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            if(j<n-i-1) a[i][j]=1;
            else if (j==n-i-1) a[i][j]=0;
            else a[i][j]=-1;
        }
    }
    print_matrix(a,n);
    return 0;
}

void print_matrix(int a[MAX_SIZE][MAX_SIZE],int n) {
    int i,j;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf(" %2d",a[i][j]);
        }
        printf("\n");
    }
}
