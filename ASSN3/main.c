#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_WORD_LENGTH 9
#define MAX_FILE_NAME 30
#define MAX_STR_LEN 30

void mainBingo(char*** user_board, char*** comp_board, int** priority_board);
void printBingo(char*** user_board, char*** comp_board, int** priority_board, char filename[MAX_FILE_NAME], int size);

void userTurn(char*** user_board, char*** comp_board, int** priority_board, char filename[MAX_FILE_NAME], int size);
//사용자의 턴에 게임 진행 (단어 입력 등)
void compTurn(char*** user_board, char*** comp_board, int** priority_board, char filename[MAX_FILE_NAME], int size);
//컴퓨터의 턴에 게임 진행 (우선 순위 보드로부터 단어 선택)
int countBingo(char*** board, ...);
//빙고 보드(board)에서 빙고 개수를 세어서 반환
void updatePriority(int** priority_board, ...);
//컴퓨터의 빙고 보드에 변화가 있을 때 우선 보드를 업데이트 하는 함수
void freeBingo(char*** user_board, char*** comp_board, int** priority_board, ...);
//게임이 종료되면, 동적 할당 받은 빙고 보드 (사용자, 컴퓨터)와 우선 순위 보드를 할당 해제


int main() {
    srand(time(NULL));
    char*** user_board = NULL;
    char*** comp_board = NULL;
    int** priority_board = NULL;

    mainBingo(user_board,comp_board,priority_board);
    return 0;
}

void mainBingo(char*** user_board, char*** comp_board, int** priority_board) {
    int i,j;
    char*** board;

    //다시확인
    //char** board_row;
    //char* board_col;
    int board_row,board_col;

    int numstring,flag;

    FILE* infile;
    char filename[MAX_FILE_NAME];

    int choice,size,numBingo,selshuffle;
    while (choice!=2) {
        printf("[Bingo Game]\n");
        printf("=========================\n");
        printf("1: Start\n");
        printf("2: Exit\n");
        printf("=========================\n");
        while (1) {
            printf("Choice: ");
            scanf("%d", &choice);
            if (choice == 1) {

                printf("File Name: ");
                scanf("%s", &filename);

                infile = fopen(filename, "r");
                fscanf(infile,"%d",&numstring);
                if (infile == NULL) {
                    printf("Err: File does not exist.\n\n");
                    break;
                }
                else {
                    while (1) {
                        printf("Bingo Board Size (2~%d): ",sqrt(numstring));
                        scanf("%d", &size);
                        if (size <= sqrt(numstring) && size >= 2) {
                            break;
                        } else printf("Err: Wrong bingo board size.\n");
                    }
                    while (1) {
                        printf("Number of bingos to win (1~10): ");
                        scanf("%d", &numBingo);
                        if (numBingo >= 1 && numBingo <= (2 * size + 2)) {
                            break;
                        } else printf("Err: Wrong number to win.\n");
                    }
                    printf("Shuffle (1: Yes, 0:No): ");
                    scanf("%d", &selshuffle);

                    board_col=size;
                    board_row=size;
                    //셔플
                    char temp[MAX_WORD_LENGTH];
                    int str_len;
                    if(selshuffle==0) {
                        //유저 보드
                        user_board = (char***) calloc (board_row, sizeof(char**));
                        for(i = 0; i < board_row; i++) {
                            user_board[i] = (char **) calloc(board_col, sizeof(char *));
                            for (j=0; j< board_col; j++) {
                                fscanf(infile, "%s", temp);
                                str_len = strlen(temp);
                                user_board[i][j]= (char *) malloc(sizeof(char) * str_len + 1);
                                strcpy(user_board[i][j],temp);
                            }
                        }
                        //지워도 되는부분
                        /*for(i = 0; i < board_row; i++) {
                            for (j=0; j< board_col; j++) {
                                printf("%s ",user_board[i][j]);
                            }
                            printf("\n");
                        }*/

                        if (numstring-2*size*size>=0) {
                            for (i=1;i<=numstring-2*size*size; i++) {
                                fscanf(infile, "%s",temp);
                            }
                        }
                        else {
                            fclose(infile);
                            infile = fopen(filename, "r");
                            fscanf(infile,"%d");
                            for (i = 1; i <= numstring - size * size; i++) {
                                fscanf(infile, "%s", temp);
                            }
                        }

                        //컴퓨터 보드
                        comp_board = (char***) calloc (board_row, sizeof(char**));
                        for(i = size-1; i >= 0; i--) {
                            comp_board[i] = (char **) calloc(board_col, sizeof(char *));
                            for (j=size-1; j>= 0; j--) {
                                fscanf(infile, "%s", temp);
                                str_len = strlen(temp);
                                comp_board[i][j]= (char *) malloc(sizeof(char) * str_len + 1);
                                strcpy(comp_board[i][j],temp);
                            }
                        }

                        //지워도 되는 부분
                        /*for(i = 0; i < board_row; i++) {
                            for (j=0; j< board_col; j++) {
                                printf("%s ",comp_board[i][j]);
                            }
                            printf("\n");
                        }*/

                            //int** priority_board;
                            priority_board = (int **)calloc(board_row, sizeof(int *));
                            for(i = 0; i < board_row; i++) {
                                priority_board[i] = (int *) calloc(board_col, sizeof(int));
                            }

                            for(i=0; i<board_row; i++) {
                                for(j=0; j<board_col; j++) {

                                }
                            }

                            printBingo(user_board, comp_board, priority_board, filename, size);
                    }
                    //셔플
                    else if(selshuffle==1) {
                        char str[MAX_STR_LEN];
                        char* p;

                        for (int i = 0; i < numstring; i++) {
                            fscanf(infile, "%s", str);
                            int str_len = strlen(str);
                            p = (char *)malloc(sizeof(char) * str_len +1);
                            strcpy(p, str);
                        }

                        /*for (int i = 0; i < numstring; i++) {
                            do {
                                flag=0;
                                board[i] = temp[rand() % numstring];
                                for (int j=0; j<=numstring; j++) {
                                    if (i!=j&&board[i]==board[j]) {
                                        flag-=1;
                                    }
                                }
                            }while (flag);
                        }*/
                    



                    }


                    char str[MAX_STR_LEN];
                    char *p;
                    fscanf(infile, "%s", str);

                    p = (char *)malloc(sizeof(char) * (strlen(str)+1));
                    strcpy(p, str);


                   }
                }
                else if(choice == 2) {
                      break;
                }
            else printf("Err: Wrong choice.\n");
            }
        }

    //파일 출력 선언 부분
    FILE* outfile;
    char outname[99];
    sprintf(outname, "%d%d%d_%s.txt",size,numBingo,selshuffle,filename);
    outfile = fopen(outname,"w");

    //파일 읽기 시작
    //int numstring;
    char str[MAX_WORD_LENGTH];
    char tempWord[MAX_WORD_LENGTH];
    int templen;
    board = (char ***)calloc(board_row, sizeof(char **));
    for(i =0; i < board_row; i++) {
        board[i] = (char **) calloc(board_col, sizeof(char *));

        fscanf(infile,"%s\n", &tempWord);
        templen=strlen(tempWord);
        //board[board_row-1][0] = (char *)malloc(sizeof(char) * (templen + 1));
        board[i]=tempWord;
        //fscanf(infile,"%s\n",board[i]);
    }


    fclose(infile);
    fclose(outfile);

    printBingo(user_board,comp_board,priority_board,filename,size);

}

void printBingo(char*** user_board, char*** comp_board, int** priority_board,char filename[MAX_FILE_NAME] ,int size) {

    FILE* outfile;
    outfile = fopen(filename,"a");

    int newsize=size*2+1;
    for (int i=0; i<newsize; i++) {
        for(int j=0; j<newsize; j++)
        {
            if(i%2==0) {
                if(j%2==0) {
                    printf("+");
                }
                else if (j%2==1) {
                    printf("---------");
                }
            }
            if(i%2==1) {
                if(j%2==0) {
                    printf("|");
                }
                else if (j%2==1) {
                    printf("%-9s",user_board[i/2][j/2]);
                }
            }
        }

        printf("\t\t");
;
        for(int j=0; j<newsize; j++)
        {
            if(i%2==0) {
                if(j%2==0) {
                    printf("+");
                }
                else if (j%2==1) {
                    printf("---------");
                }
            }
            if(i%2==1) {
                if(j%2==0) {
                    printf("|");
                }
                else if (j%2==1) {
                    printf("%-9s",comp_board[i/2][j/2]);
                }
            }
        }
        printf("\n");
    }


    userTurn(user_board,comp_board,priority_board,filename,size);
    compTurn(user_board,comp_board,priority_board,filename,size);
}

void userTurn(char*** user_board, char*** comp_board, int** priority_board, char filename[MAX_FILE_NAME], int size) {
    int i,j, flag=1;
    while(flag) {
        char temp[MAX_WORD_LENGTH];
        printf("\nYour Choice: ");
        scanf("%s",temp);
        for(i=0; i<size; i++) {
            for (j=0; j<size; j++) {
                if(strcmp(user_board[i][j],temp)==0) {
                    flag=0;
                    user_board[i][j]="#########";
                }
            }
        }
        if(flag) printf("\nWrong Input '%s' does not exist.\n",temp);
    }
    //printBingo(user_board,comp_board,priority_board,filename,size);
}