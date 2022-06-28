#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5


void ReadBoard();
void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE],int n); //현재의 빙고 보드를 출력
int checkBingo(char board[][MAX_SIZE],int n);
//빙고 보드에서 가로, 세로, 대각선 등 빙고가 존재하는지를 판단하여 있다면 1, 없다면 0을 반환
int Bingo_main();
int RandomStart(int n);

int main() {
    srand(time(NULL));
    Bingo_main();

    return 0;
}

int Bingo_main() {

    int sel_rd,sel_brd;
    while (1) {
        printf("Random or read from file? (1: Random, 2:Read) ");
        scanf("%d",&sel_rd);
        if(sel_rd==1) {
            while (1) {
                printf("Size of Bingo board? (3~5) ");
                scanf("%d",&sel_brd);
                if (sel_brd==3||sel_brd==4||sel_brd==5) {
                    RandomStart(sel_brd);
                    break;
                }
            }
        }
        else if(sel_rd==2) {
            ReadBoard();

            break;
        }
    }
}
int RandomStart(int n) {

    char player[99][99];
    char player_rand[99];
    char computer[99][99];
    char computer_rand[99];
    int i,j,check,k;




    for (i=0; i<(n*n); i++) { //랜덤 수들의 중복제거
        do {
            check=0;
            player_rand[i] = rand() % (n * n) + 65;
            for (j = 0; j < (n*n); j++) {
                if (player_rand[i] == player_rand[j]) check += 1;
            }
        }while(check>1);
    }
    k=0;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%d")
            player[i][j]=player_rand[k];
            k+=1;
        }
    }


    for (i=0; i<(n*n); i++) { //랜덤 수들의 중복제거
        do {
            check=0;
            player_rand[i] = rand() % (n * n) + 65;
            for (j = 0; j < (n*n); j++) {
                if (player_rand[i] == player_rand[j]) check += 1;
            }
        }while(check>1);
    }

    for (i=0; i<(n*n); i++) {       //일차원 배열을 이차원 배열로 만든다.
        do {
            check=0;
            computer_rand[i] = rand() % (n * n) + 65;
            for (j = 0; j < (n*n); j++) {
                if (computer_rand[i] == computer_rand[j]) check += 1;
            }
        }while(check>1);
    }
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%c ",player[i][j]);
        }
    }
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("%c ",computer[i][j]);
        }
    }
    /*for (i=0,j=0,k=0; k<n*n; k++,j++) {

        if(j==n) {
            j-=n;
            i++;
        }
        if (i<=n) {
            player[i][j] = player_rand[k];
        }
    }
    for (i=0,j=0,k=0; k<n*n; k++,j++) {

        if(j==n) {
            j-=n;
            i++;
        }
        if (i<=n) {
            computer[i][j] = computer_rand[k];
        }
    }*/

    /*int count=1;
    while (count<=n*n) {
        for (i = 0; i < n; i++) {
            do {
                TF = 0;
                for (j = 0; j < n; j++) {
                    player[i][j] = rand() % (n * n) + 65;
                    for (p=0;p<n*n; p++) {
                        player_rand[]
                        check = player[j];
                        if (player[i][j] == player_rand[j]) {
                        TF += 1;
                        break;
                        }
                    }
                }
            } while (TF >= 2);
        }
    }*/

       /* for (i=0; i<=n*n-1; i++) {
            do {
                TF=0;
                computer_rand[i] = rand() % n*n + 65;
                for (j = 0; j <= n*n-1; j++) {
                    if(i!=j&&computer_rand[j]!=computer_rand[i]) {
                        TF=1;
                        break;
                    }
                }
            } while (TF=0);

        }*/
        FILE* outfile;
        outfile = fopen("result.txt","a");
        k=0;
        for (i=0; i<=n-1; i++) {
            for (j=0; j<=n-1; j++) {
                fprintf(outfile,"%c ",&player_rand[k]);
                player[i][j]=player_rand[k];
                k++;
            }
            k-=3;
            fprintf(outfile,"     ");
            for (j=0; j<=n-1; j++) {
                fprintf(outfile,"%c ",&computer_rand[k]);
                computer[i][j]=player_rand[k];
                k++;
            }
            fprintf(outfile,"\n");
        }
        printBoard(player,computer,n);

}

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE],int n) {
    int flag1=0, flag2 = 0, flag3 = 0;
    while(flag1==0 && flag2==0 && flag3==0) {
    int i, j, k1 = 0,k2 =0;
    FILE* outfile;
    outfile = fopen("result.txt","a");
    for (i=0; i<=n-1; i++) {
        for (j=0; j<=n-1; j++) {
            fprintf(outfile,"%c ",&user_board[i][j]);
            int al=user_board[i][j];
        }

            fprintf(outfile,"     ");
        for (j=0; j<=n-1; j++) {
            fprintf(outfile,"%c ",&comp_board[i][j]);
        }
            fprintf(outfile,"\n");
    }
    int nprime=2*n+1;
    for (i = 0; i < nprime; i++) {
        for (j = 0; j <  nprime; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) printf("+");
                else if (j % 2 == 1) printf("-");
            } else if (i % 2 == 1) {
                if (j % 2 == 0) printf("|");
                else if (j % 2 == 1) {
                    k1++;
                    if (k1>=n) {
                        k1-=n;
                        k2++;
                    }
                    printf("%c", user_board[k2][k1]);
                }
            }
        }
            printf("      ");
            k2=0;
            k1 -= n;
        for (j = 0; j <  nprime ; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) printf("+");
                else if (j % 2 == 1) printf("-");
            } else if (i % 2 == 1) {
                if (j % 2 == 0) printf("|");
                else if (j % 2 == 1) {
                    if (comp_board == '#') printf("%c", comp_board[k1]);
                    else printf(" ");
                    //k++;
                }
            }
        }
        printf("\n");
    }

    char user_ans, comp_ans;
    do {
        flag1 = 0;
        printf("\nYour choice: ");
        scanf("%c ", &user_ans);
        for (i=0; i<n*n; i++) {
            for (j=0; j<n*n; j++) {
                if (user_ans == user_board[i][j])
                 printf("4");
            }
        }
        if (user_ans>=65+n*n) {
            flag1 = 0;
            break;
        }
        //else if ()
        fprintf(outfile, "\nUser's choice: %c\n",user_ans);
        for (i = 0; i < n; i++) {
            if (user_board[i] == user_ans) {
                flag1 = 1;
                user_board[i] == '#';
                break;
            }
        }
    } while (!flag1);
    flag2 = checkBingo(user_board, n);

    do {
        flag3 = 0;
        printf("\nComputer's choice: ");
        comp_ans = rand() % (n * n) + 65;
        fprintf(outfile, "\nComputer's choice: %c\n",comp_ans);
        for (i = 0; i < n; i++) {
            if (comp_board[i] == user_ans) {
                flag3 = 1;
                comp_board[i] == '#';
                break;
            }
        }
    } while (!flag3);
    flag3 = checkBingo(comp_board, n);

    if (flag2 == 1 || flag3 == 1) {
        if (flag2 == flag3) printf("\nDraw ");
        else if (flag2 > flag3) printf("\nYou Win!");
        else if (flag2 < flag3) printf("\nComputer Wins!");

        break;
    }
        else RandomStart(n);
    }
}

void ReadBoard() {
    int n;
    FILE* infile;
    infile = fopen("board.txt","r");
    char user_board[MAX_SIZE][MAX_SIZE];
    char player[99];
    char comp_board[MAX_SIZE][MAX_SIZE];
    char computer[99];
    fscanf(infile,"%d",&n);
    int i,j,k=0;
    for(int i=0; i<=n-1; i++) {
        for (j=0; j<=n-1; j++) {
            fscanf(infile, "%c ", &user_board[i][j]);
            user_board[i][j]=player[k];
        }
    }

    for(int i=0; i<=n-1; i++) {
        for (j=0; j<=n-1; j++) {
            fscanf(infile, "%c ", &comp_board[i][j]);
            user_board[i][j]=player[k];
        }
    }
    FILE* outfile;
    outfile = fopen("result.txt","a");
    k=0;
    for (i=0; i<=n-1; i++) {
        for (j=0; j<=n-1; j++) {
            fprintf(outfile,"%c ",player[k]);
            k++;
        }
        k-=3;
        fprintf(outfile,"     ");
        for (j=0; j<=n-1; j++) {
            fprintf(outfile,"%c ",computer[k]);
            k++;
        }
        fprintf(outfile,"\n");
    }
    printBoard(&user_board,&comp_board,n);
}

int checkBingo(char board[][MAX_SIZE],int n) {
    int i,j,check_1=0,check_2=0,check_3=0,check_4=0;

    for (i=0; i<n; i+=2) {
        if (board[i][i] == '#') {
            check_1 += 1;
        }
        if (check_1 == n) return 1;
    }
    for (i=0; i<n; i++) {
        check_2=0;
        for (j=0; j<n; j++) {
            if(board[i][j]=='#') check_2+=1;
        }
        if(check_2==n) return 1;
    }
    for (i=0; i<n; i++) {
        check_3=0;
        for (j=0; j<n; j++) {
            if(board[j][i]=='#') check_3+=1;
        }
        if(check_3==n) return 1;
    }
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            if(i+j==(n-1)&&board[j][i]=='#') check_4+=1;
        }
        if(check_4==n) return 1;
    }

    return 0;
}