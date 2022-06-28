
#include <stdio.h>

void partial_print(int *arr_start,int size);
int partial_sum(int *arr_start,int *arr_end);

int main() {
    printf("Enter 10 elements of array: ");
    int a[10];
    int i;
    for (i=0; i<=9; i++) {
        scanf(" %d",&a[i]);
    }
    printf("Numbers that you enter are: ");
    partial_print(a,10);

    int s,e;
    printf("Enter the starting and ending index: ");
    scanf("%d %d",&s, &e);

    int result=partial_sum(a+s,a+e);
    printf("\nSum from array[%d] to array[%d] is %d\n",s,e,result);
    printf("Partial array output: ");
    partial_print(a+s,e-s+1);

    return 0;
}

void partial_print(int *arr_start,int size) {
    int i;

    for (i=0; i<size; arr_start++ ,i++ ) {
        printf("%d ", *arr_start);
    }
    printf("\n");
}

int partial_sum(int *arr_start,int *arr_end) {
    int result=0;
    while (arr_start <= arr_end) {
        result+= *arr_start;
        arr_start++;
    }
    return result;
}
