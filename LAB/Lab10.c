#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void find_minmax(int *arr, int size, int *max, int *min);

int main() {
    int size,max,min,i;
    int* arr;
    int* pmax;
    pmax= &max;
    int* pmin;
    pmin= &min;

    printf("Enter array size: ");
    scanf("%d",&size);
    arr = (int *)malloc(size*sizeof(int));

    for (i=0; i<size; i++) {
        scanf("%d",&arr[i]);
    }
    printf("Entered numbers are\n");
    for (i=0; i<size; i++) {
        printf("%d  ",arr[i]);
    }
    find_minmax(arr,size,pmax,pmin);
    printf("\nMaximum is %d\n",max);
    printf("Minimum is %d\n\n",min);

    printf("Enter changed array size: ");
    scanf("%d",&size);
    arr= (int *)realloc(arr , size * sizeof(int));

    for (i=0; i<size; i++) {
        scanf("%d",&arr[i]);
    }
    printf("Entered numbers are\n");

    for (i=0; i<size; i++) {
        printf("%d ",arr[i]);
    }
    find_minmax(arr,size,pmax,pmin);
    printf("\nMaximum is %d\n",max);
    printf("Minimum is %d",min);

    free(arr);
    return 0;
}

void find_minmax(int *arr, int size, int *max, int *min) {
    int* pWalk;
    int* pLast;
    pLast=arr+size-1;

    for (pWalk = arr,*max=arr[0]; pWalk<=pLast; pWalk++) {
        if (*max<=*pWalk) {
            *max=*pWalk;
        }
    }
    for (pWalk = arr,*min=arr[0]; pWalk<=pLast; pWalk++) {
        if (*pWalk<=*min) {
            *min=*pWalk;
        }
    }
}
