#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void season_print(int x);

int main() {
    srand(time(NULL));
    int a=rand()%12+1;

    int b=rand()%12+1;

    int c=rand()%12+1;
    season_print(a);
    season_print(b);
    season_print(c);

    return 0;
}

void season_print(int x) {
    switch (x) {
        case 1: printf(" 1월, 겨울\n"); break;
        case 2: printf(" 2월, 겨울\n"); break;
        case 3: printf(" 3월, 봄\n"); break;
        case 4: printf(" 4월, 봄\n"); break;
        case 5: printf(" 5월, 봄\n"); break;
        case 6: printf(" 6월, 여름\n"); break;
        case 7: printf(" 7월, 여름\n"); break;
        case 8: printf(" 8월, 여름\n"); break;
        case 9: printf(" 9월, 가을\n"); break;
        case 10: printf(" 10월, 가을\n"); break;
        case 11: printf(" 11월, 가을\n"); break;
        case 12: printf(" 12월, 겨울\n"); break;
    }
}