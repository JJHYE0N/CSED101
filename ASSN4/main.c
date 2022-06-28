//MacOS CLion
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_Musicsize 45
#define MAX_Artistsize 45
#define MAX_Filenamesize 30

typedef struct  //MUSIC 구조체 선언
{
    char name[MAX_Musicsize];
    char artist[MAX_Artistsize];
    int playtime;
    int numplay ;
}MUSIC;

typedef struct node //NODE 구조체 선언
{
    MUSIC data;
    struct node* next;
}NODE;

typedef struct  //LIST 구조체 선언
{
    int count;
    NODE* head;
    NODE* tail;
}LIST;

void input_list(LIST* plist, FILE* infile);
void delete_list(LIST* plist);
void search_list(LIST* plist);
void show_top3list(LIST* plist);
void show_list(LIST* plist);
void move_list(LIST* plist);
void free_list(LIST* plist);
void fprint_one_music(MUSIC s, int* alltime, int* numsong, char outfilename [MAX_Filenamesize]);
void print_one_music(MUSIC s, int no,int* alltime, int* numsong);
void add_music(LIST* plist);
void clear_scanf();

int main() {
    char command[20],flag=1;    //커맨드와 flag를 선언한다.
    LIST slist;
    //초기화
    slist.count = 0;
    slist.head = NULL;
    slist.tail = NULL;

    FILE* infile;
    char filename[MAX_Filenamesize];
    while(1) {
        printf("기존의 플레이리스트를 저장한 파일 이름을 입력해주세요. >> ");   //문자열을 출력한다.
        scanf("%s", filename);  //filename을 입력받는다.
        infile = fopen(filename, "r");  //filename에 해당하는 파일을 연다.
        if(infile == NULL) {    //파일이 존재하지 않을 경우, 재입력 받게 한다.
            printf("유효하지 않은 입력입니다. ");
        }
        else {  //아닐경우
            break; //break한다.
        }
    }

    input_list(&slist, infile); //input_list를 호출하여 infile로 부터 값을 받아온다.
    printf("\n재생 횟수 Top 3 음악의 정보입니다.\n");
    show_top3list(&slist);  //show_top3list를 호출하여 top3에 해당하는 출력을 해준다.


    while (1) {
        printf("명령어를 입력해주세요. >> ");
        scanf("%s",command);    //command를 입력받는다.
        if (strcmp(command,"show" ) ==0) {  //show 일 경우 show_list 호출
            show_list(&slist);
        }
        else if (strcmp(command,"search" ) ==0) {   //search 일 경우 search_list 함수 호출
            search_list(&slist);
        }
        else if (strcmp(command,"add" ) ==0) {  //add일 경우 add_list 함수 호출
            add_music(&slist);
        }
        else if (strcmp(command,"delete" ) ==0) {   //delete일 경우 delete_list 함수 호출
            delete_list(&slist);
        }
        else if (strcmp(command,"move" ) ==0) { //move일 경우 move_list 함수 호출
            move_list(&slist);
        }
        else if (strcmp(command,"quit" ) ==0) { //quit일 경우
            if (slist.count ==0) {  //안에 값들이 없을 경우
                printf("플레이리스트에 저장할 내용이 없습니다.\n");
                flag=0; //flag를 0으로 하여 파일 출력이 안되도록 한다.
            }
            break;  //break 한다.
        }
        else {
            printf("유효하지 않은 입력입니다. ");  //나머지 입력일 경우 문자열 출력
        }
    }
    if (flag) { //자료가 1개이상 있을 경우
        char outfilename[MAX_Filenamesize];
        printf("저장할 파일 이름을 입력해주세요. >> ");   //outfilename을 받아 출력해주도록한다.
        scanf("%s", outfilename);
        FILE *outfile;
        outfile = fopen(outfilename, "w");  //outfilename에 해당하는 파일을 쓰기모드 로 연다.
        fclose(outfile);    //outfilename을 닫는다.
        int* alltime=0; int* numsong=0;
        NODE* temp;
        for (temp = slist.head; temp != NULL ; temp = temp->next) { //node의 수만큼 반복시킨다.
            fprint_one_music(temp->data, &alltime, &numsong, outfilename);  //fprint_one_music을 호출하여 outfilename에 값을 입력한다.
        }
    }
    free_list(&slist);  //free_list를 호출하여 slist에 할당을 해제해준다.
    return 0;
}

void input_list(LIST* plist, FILE* infile){

    int i=0,j=0;
    NODE* pPre; //pPre를 선언한다.

    while(!feof(infile))  { //infile이 끝이 아닐 경우
        NODE *temp = (NODE *) malloc(sizeof(NODE)); //temp를 동적할당 해준다.
        temp->next = NULL;  //temp의 다음을 NULL로 한다.
        fscanf(infile, "%[^\t] %[^\t] %d %d\n", temp->data.name, temp->data.artist, &temp->data.playtime,
               &temp->data.numplay);    //각각의 데이터들을 받아온다.
        i++;    //i의 값을 증가시킨다.
        if (plist->head == NULL) {  //head가 NULL일 경우
            plist->head = temp; //head를 temp로 한다.
        } else {    //head에 값이 있을 경우
            if((plist->head->data.numplay)<(temp->data.numplay)) {  //head->data.numplay가 temp->data.numplay보다 작을 경우
                temp->next = plist->head;   //temp의 next를 head로 하고,
                plist->head = temp; //temp를 head로 한다.
            }
            else {  //아닐 경우
                j=1;    //j=1으로 초기화한다.
                for (pPre = plist->head; pPre != NULL; pPre = pPre->next) { //pPre를 node의 개수만큼 반복시켜주고
                    j++;    //j++하고
                    if (j == i) { //노드의 마지막에 pPre가 있을 경우
                        pPre->next = temp;  //pPre의 다음에 temp로 한다.
                        break;
                    }
                    else if ((pPre->next->data.numplay)<(temp->data.numplay)) {   //pPre->next->data.numplay가 temp->data.numplay보다 작을 경우
                        temp->next = pPre->next;    //temp의 next는 pPre의 next로 하고
                        pPre->next = temp;  //pPre의 next를 temp로 한다.
                        break;
                    }
                }
            }
        }
        plist->count++;
    }
}

void show_top3list(LIST* plist) {
    NODE *temp;
    int i = 0;
    int *numsong = 0;
    int *alltime = 0;
    printf("\n=============================================================================================================================\n");
    printf("\t  title\t\t\t\t\t\t\t\t\t\t   artist\t\t\t\t\t\t\t\t\t\t\ttime\t# of plays\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    for (temp = plist->head; temp != NULL && i<3; temp = temp->next) {  //3개만 출력하도록 반복문을 돌린다.
        i++;
        print_one_music(temp->data, i, &alltime, &numsong); //print_one_music을 호출하여 정보를 출력한다.
    }
    printf("=============================================================================================================================\n");
    printf("   [total: %d music, %d (s)]\n\n", numsong, alltime);   //문자열을 출력한다.
}

void show_list (LIST* plist)
{
    NODE* temp;
    int i = 0;
    int* numsong=0;
    int* alltime=0;
    printf("\n=============================================================================================================================\n");
    printf("\t  title\t\t\t\t\t\t\t\t\t\t   artist\t\t\t\t\t\t\t\t\t\t\ttime\t# of plays\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------\n");
    for(temp = plist->head; temp != NULL; temp=temp->next) {    //모든 노드들이 출력될 수 있도록 반복문 선언
        i++;
        print_one_music(temp->data,i,&alltime, &numsong);   //print_one_music을 호출하여 정보를 출력한다.
    }
    printf("=============================================================================================================================\n");
    printf("   [total: %d music, %d (s)]\n\n",numsong,alltime); //문자열을 출력한다.
}

void print_one_music(MUSIC s, int no, int* alltime, int* numsong) {
    printf("%d\t  %-45s%-45s\t%-4d   \t%-10d\n", no, s.name, s.artist, s.playtime, s.numplay);  //해당 노드의 정보들을 출력해준다.
    *alltime += s.playtime;//playtime의 값을 alltime에 넣어준다.
    *numsong += 1;//numsong의 값을 1 증가시킨다.
}

void fprint_one_music(MUSIC s, int* alltime, int* numsong,char outfilename [MAX_Filenamesize]) {    //fprintf로 출력해주는 함수이다.
    FILE* outfile;  //파일입출력 outfile을 선언한다.
    outfile = fopen (outfilename,"a");  //outfilename으로 a모드로 open한다.
    fprintf(outfile,"%s\t%s\t%d\t%d\n", s.name, s.artist, s.playtime, s.numplay);   //값들을 출력해준다.
    *alltime += s.playtime; //playtime의 값을 alltime에 넣어준다.
    *numsong += 1;  //numsong의 값을 1 증가시킨다.
    fclose(outfile);    //outfile을 닫는다.
}

void free_list(LIST* plist)
{
    NODE* temp; //temp를 가져와서
    while (plist->head != NULL) //각각의 노드들을 할당해제해준다.
    {
        temp = plist->head;
        plist->head = plist->head->next;
        free(temp);
    }
}

void search_list(LIST* plist)
{
    NODE* temp;
    int i = 0;
    int* numsong=0; //노래의 개수에 해당하는 정수형 포인터 선언
    int* alltime=0; //재생시간에 해당하는 정수형 포인터 선언
    char artist[MAX_Artistsize]; //아티스트 이름에 해당하는 배열 선언
    printf("어떤 아티스트의 음악을 검색할까요> >> ");
    scanf("%s",artist);
    for(temp = plist->head; temp != NULL; temp=temp->next) {    //temp가 node의 끝까지 돌도록 반복문 선언한다.
        if (strcmp(artist,temp->data.artist) ==0) { //artist와 tmep 가 같을 경우
            i++;    //i 값을 증가시킨다.
        }
    }
    if(i==0) {
        printf("플레이리스트에 해당 아티스트의 음악이 없습니다.\n\n");
    }
    else {  //i가 0이 아니라면
        i = 0;
        printf("\n=============================================================================================================================\n");
        printf("\t  title\t\t\t\t\t\t\t\t\t\t   artist\t\t\t\t\t\t\t\t\t\t\ttime\t# of plays\n");
        printf("-----------------------------------------------------------------------------------------------------------------------------\n");
        for (temp = plist->head; temp != NULL; temp = temp->next) { //temp가 node의 끝까지 돌도록 반복문 선언한다.
            i++;
            if (strcmp(artist, temp->data.artist) == 0) {   //artist와 tmep 가 같을 경우
                print_one_music(temp->data, i, &alltime, &numsong); //해당 아티스를 출력한다.
            }
        }
        printf("=============================================================================================================================\n");
        printf("   [total: %d music, %d (s)]\n\n", numsong, alltime);   //노래의 개수랑 재생시간을 출력해준다.
    }
}

void add_music(LIST *plist) {
    int n;
    NODE *pPre;
    NODE* temp  = (NODE*)malloc(sizeof(NODE));
    while(1) {  //반복문을 사용해 적절한 값을 받도록 한다.
        printf("몇 번째 순서로 음악을 추가할까요? >> ");
        scanf("%d",&n); //n의 값을 입력받느다.
        if(n<1 || n> (plist->count +1)) {   //n의 값이 적절하지 않을 경우 문자열을 출력
            printf("유효하지 않는 입력입니다. ");
        }
        else break; //적절한 n의 값일 경우 break 한다.
    }

    //각 MUSIC에 요소들을 입력받는다.
    printf("추가할 음악의 제목을 입력해주세요. >> ");
    clear_scanf();
    scanf("%[^\n]", temp->data.name);
    printf("추가할 음악의 아티스트을 입력해주세요. >> ");
    clear_scanf();
    scanf("%[^\n]", temp->data.artist);
    printf("추가할 음악의 재생 시간을 입력해주세요. >> ");
    scanf("%d", &temp->data.playtime);
    printf("추가할 음악의 재생 횟수을 입력해주세요. >> ");
    scanf("%d", &temp->data.numplay);
    printf("\n");

    if(n==1) {  //n이 1일 경우
        temp->next = plist->head;   //head를 temp의 next로 하고
        plist->head = temp; //temp라는 것을 head로 지정하여 첫번째에 오게한다.
    }
    else {
        int i = 0;
        for (pPre = plist->head; pPre->next != NULL; pPre = pPre->next) {   //pPre가 node의 모든 값을 돌도록 반복문한다.
            i++;
            if (i == n-1) { //n-1 번째 노드일 경우 break한다.
                break;
            }
        }
        temp->next = pPre->next;   //temp의 next를 pPre의 next로 하고
        pPre->next = temp;  //pPre의 next를 temp로 하여 자리를 바꾼다.
    }
    (plist->count)+=1;  //요소를 추가해주는 것이기 때문에 count 값을 1 증가 시켜준다.
}

void move_list(LIST* plist) {
    int n1,n2,i;
    NODE* pPre1;    //temp1보다 1칸 전의 pPre1 선언
    NODE* pPre2;    //temp2보다 1칸 전의 pPre2 선언
    NODE* pPos1;    //temp1보다 1칸 뒤에 pPos1 선언
    NODE* pPos2;    //temp2보다 1칸 뒤에 pPos2 선언
    NODE* temp1 = (NODE*)malloc(sizeof(NODE));  //n1번째 칸의 temp1 동적할당하여 선언
    NODE* temp2 = (NODE*)malloc(sizeof(NODE));  //n2번째 칸의 temp2 동적할당하여 선언

    if (plist->count <= 1) {    //값이 1개만 남았을 경우
        printf("플레이리스트에 순서를 이동할 음악이 없습니다.\n\n");
    }
    else    //값이 2개 이상일 경우
    {
        while (1) { //적절한 값을 받기 위해 반복문 선언
            printf("몇 번째 순서의 음악의 위치를 바꿀까요? >> ");
            scanf("%d", &n1);   //n1의 값을 입력받는다.
            if (n1 >= 1 && n1 <= plist->count) break;   //1보다 크거나 같고 count보다 작거나 같을 경우 break 한다.
            else printf("유효하지 않은 입력입니다. ");
        }
        while (1) {
            printf("몇 번째 순서로 이동시킬까요? >> ");
            scanf("%d", &n2);   //n2의 값을 입력받는다.
            if (n2 >= 1 && n1 != n2 && n2 <= plist->count) break;   //1보다 크거나 같고, n1과 같지않으며  count보다 작거나 같을 경우 break 한다.
            else printf("유효하지 않은 입력입니다. ");
        }
    }

    i = 0;
    for (temp1 = plist->head; temp1 != NULL; temp1 = temp1->next) { //temp1를 n1번째 노드로 가도록 반복문 선언한다.
        i++;
        if (i == n1) {
            break;
        }
    }
    i = 0;
    for (temp2 = plist->head; temp2 != NULL; temp2 = temp2->next) { //temp2를 n2번째 노드로 가도록 반복문 선언한다.
        i++;
        if (i == n2) {
            break;
        }
    }
    i = 0;
    for (pPre1 = plist->head; pPre1 != NULL; pPre1 = pPre1->next) { //pPre1을 n1번째보다 1칸 전에 노드로 가도록 반복문 선언한다.
        i++;
        if (i == n1 - 1) {
            break;
        }
    }
    i = 0;
    for (pPre2 = plist->head; pPre2 != NULL; pPre2 = pPre2->next) { //pPre2을 n2번째보다 1칸 전에 노드로 가도록 반복문 선언한다.
        i++;
        if (i == n2 - 1) {
            break;
        }
    }
    i = 0;
    for (pPos1 = plist->head; pPos1 != NULL; pPos1 = pPos1->next) { //pPos1을 n1번째보다 1칸 뒤에 노드로 가도록 반복문 선언한다.
        i++;
        if (i == n1 + 1) {
            break;
        }
    }
    i = 0;
    for (pPos2 = plist->head; pPos2 != NULL; pPos2 = pPos2->next) { //pPos2을 n2번째보다 1칸 뒤에 노드로 가도록 반복문 선언한다.
        i++;
        if (i == n2 + 1) {
            break;
        }
    }
    if(n1==1) { //n1 이 1일 경우

        if (n2==plist->count) { //n2가 count일 경우
            plist->head = temp1->next;
            temp1->next = temp2->next;
            temp2->next = temp1;
        }
        else {  //n2가 count가 아닐 경우
            plist->head = temp1->next;
            temp2->next = temp1;
            temp1->next = pPos2;
        }
    }
    else if (n1==plist->count) {    //n1이 count일 경우
        if (n2==1) {    //n2가 1일 경우
            plist->head = temp1;
            temp1->next = temp2;

            pPre1->next = NULL;
        }
        else {  //n2가 1이 아닐 경우
            pPre2->next = temp1;
            temp1->next = temp2;

            pPre1->next = NULL;
        }
    }
    else {  //n1이 1,count 둘다 아닐 경우
        if (n2==1) {    //n2가 1일 경우
            pPre1->next = temp1->next;
            plist->head = temp1;
            temp1->next = temp2;

        }
        else if (n2==plist->count) {    //n2가 count일 경우
            pPre1->next = temp1->next;
            temp1->next = pPos2;
            temp2->next = temp1;

        }
        else {  //n2가 1,count가 아닐 경우
            if(n1>n2) { //n1>n2일 경우
                pPre1->next = temp1->next;
                pPre2->next = temp1;
                temp1->next = temp2;

            }
            else if (n1<n2) {   //n1<n2일 경우
                pPre1->next = temp1->next;
                temp2->next = temp1;
                temp1->next = pPos2;

            }
        }
    }
}

void delete_list(LIST* plist) {
    int n,i;
    NODE* pPre; //temp의 전 노드를 pPre로 선언
    NODE* temp  = (NODE*)malloc(sizeof(NODE));  //temp 동적할당
    if(plist->head==NULL) { //NULL값일 경우
        printf("플레이리스트에 삭제할 음악이 없습니다\n\n");
    }

    else {
        while(1) {  //적절한 값을 받기 위해 반복문  선언
            printf("몇 번째 순서의 음악을 삭제할까요? >> ");
            scanf("%d",&n);
            if (n>=1 && n<=plist->count) break; //1과 count 값까지일 경우 break 한다.
            else printf("유효하지 않은 입력입니다. ");
        }
        pPre = plist->head; //pPre는 plist->head로 한다.
        if (n == 1) {   //만약 입력값이 1일 경우
            plist->head = pPre->next;   //1번째 노드를 연결을 해제하고 다음을 연결한다.
            free(pPre);
        } else {
            if (n == plist->count) {    //만약 n이 count일 경우
                i = 0;
                for (temp = plist->head; temp != NULL; temp = temp->next) { //temp를 n번째 노드로 가도록 반복문 선언한다.
                    i++;
                    if (i == n) {
                        break;
                    }
                }
                i = 0;
                for (pPre = plist->head; pPre != NULL; pPre = pPre->next) { //pPre를 n-1(temp으 전단계)번째 노드로 가도록 반복문 선언한다.
                    i++;
                    if (i == n - 1) {
                        break;
                    }
                }
                plist->tail = pPre; //pPre를 노드의 마지막으로 하고, 다음은 NULL값으로 바꿔준다.
                pPre->next = NULL;
                free(temp); //temp를 할당해제 해준다.
            } else {    //아닐경우 (n이 count가 아닌 모든 경우)
                i = 0;
                for (temp = plist->head; temp != NULL; temp = temp->next) { //temp를 n번째 노드로 가도록 반복문 선언한다.
                    i++;
                    if (i == n) {
                        break;
                    }
                }
                i = 0;
                for (pPre = plist->head; pPre != NULL; pPre = pPre->next) { //pPre를 n-1(temp으 전단계)번째 노드로 가도록 반복문 선언한다.
                    i++;
                    if (i == n - 1) {
                        break;
                    }
                }
                pPre->next = temp->next;    //pPre의 다음을 temp의 다음으로 하여 temp 의 연결을 끊는다.
                free(temp); //temp를 할당해제 해준다.
            }

        }
        (plist->count) -= 1;    //delete이므로 count의 값을 하나 빼준다.
    }
}
void clear_scanf() {    //버퍼를 지워주는 함수
    int clear;
    while ((clear = getchar()) != EOF && clear != '\n') {};
}