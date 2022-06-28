#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[20];
    int exam[2];
    float avg;
    char grade;
}STUDENT;

void find_student(STUDENT slist[], int n);
void print_one_student(STUDENT s, int no);
void print_students(STUDENT slist[], int n);
void add_student(STUDENT *p);

int main() {
    int idx = 0;
    STUDENT slist[10];
    char command[20];

    while (1) {
        printf(">> ");
        scanf("%s",command);

        if (strcmp(command,"add" ) ==0) {
            add_student(&slist[idx]);
            idx++;
        }
        else if (strcmp(command,"print" ) ==0) {
            print_students(slist, idx);
        }
        else if (strcmp(command,"find" ) ==0) {
            find_student(slist, idx);
        }
        else if (strcmp(command,"quit" ) ==0) {
            break;
        }
    }
    return 0;
}

void find_student(STUDENT slist[], int n) {
    int i;
    char name[20];
    printf("이름: ");
    scanf("%s",&name);
    for (i=0; i<n; i++) {
        if (strcmp(name,slist[i].name) ==0) {
            printf("번호\t\t이름                중간   기말   평균 (학점)\n");
            print_one_student(slist[i],  i+1);
        }
    }
    printf("\n");
}
void print_one_student(STUDENT s, int no) {
    printf("%d\t  %-20s %d   %d   %.1f (%c)\n", no, s.name, s.exam[0], s.exam[1], s.avg, s.grade);
}

void print_students(STUDENT slist[], int n) {
    int i;
    printf("번호\t\t이름                중간  기말  평균 (학점)\n");
    for (i=0; i<n; i++)
    {
        print_one_student(slist[i], i+1);
    }
    printf("\n");
}

void add_student(STUDENT *p) {
    printf("이름: ");
    scanf("%s", &p->name);
    printf("중간고사: ");
    scanf("%d", &p->exam[0]);
    printf("기말고사: ");
    scanf("%d", &p->exam[1]);
    p->avg = (float)(0.5)*(p->exam[0]+p->exam[1]);

    if(p->avg >=90) {
        p->grade = 'A';
    }
    else if(p->avg <90 &&p->avg >=80) {
        p->grade = 'B';
    }
    else if(p->avg <80 &&p->avg >=70) {
        p->grade = 'C';
    }
    else if(p->avg <70 &&p->avg >=60) {
        p->grade = 'D';
    }
    else {
        p->grade = 'F';
    }
    printf("\n");
}