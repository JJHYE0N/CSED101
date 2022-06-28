#define _CRT_SECURE_NO_WARNINGS //scanf함수 오류 제거
#include <stdio.h>  //표준입출력 헤더파일 추가
#include <math.h>   //math 헤더파일 추가
#include <string.h> //string 헤더파일 추가

int inputSelection();   //정수형 함수 선언

void funcRiemannSum();  //void형 함수 선언
void calcRiemannSum(int a,int b,int c,int inivalue,int finvalue,int numsqr,float dx); //void형 함수 선언, 정수형,실수형 파라미터 선언

void funcRomanNumerals(); //void형 함수 선언
void printRoman(int num); //void형 함수 선언
void printOnes(int n1); //void형 함수 선언
void printTens(int n2); //void형 함수 선언
void printHundreds(int n3); //void형 함수 선언

void funcMysteryNumber(); //void형 함수 선언
int checkPrime(int num); //정수형 함수 선언
int maxDigit(int num); //정수형 함수 선언
int minDigit(int num); //정수형 함수 선언

int main() { //메인함수 선언
    inputSelection();   //inputSelection 함수 호출
    return 0;   //메인함수 종료
}

int inputSelection()
{
    int sel,flag=1; //정수형 sel함수와 flag 함수 선언
    do {    //do ~while 반복문 시작

        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"); //문자열 출력
        printf("CSED 101 Assignment 1\nChoose from the following:\n\n"); //문자열 출력
        printf("1. Riemann Sum\n2. Roman Numerals\n3. The Mystery Number\n4. Terminate Program\n"); //선택을 알려주는 문자열 출력
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");   //문자열 출력
        while (1) { //1,2,3,4 값만 입력받기 위한 while문 시작
            printf("\nSelection: "); //문자열 출력
            scanf("%d", &sel);  //sel 변수값을 입력받는다.
            if (sel == 1 || sel == 2 || sel == 3 || sel == 4) { //만약 sel이 1,2,3,4값을 입력받을 경우
                break;  //break한다.
            } else printf("Invalid selection\n");   //조건문이 거짓일 때 올바른 값을 입력받도록 문자열 출력
        }   //while문 종료
        switch (sel) {  //sel 값에 따른 switch문 시작
            case 1: funcRiemannSum(); break; //sel=1 일 때, funcRiemannSum 함수 호출
            case 2: funcRomanNumerals(); break; //sel=2 일 때, funcRomanNumerals 함수 호출
            case 3: funcMysteryNumber(); break; //sel=3 일 때, funcMysteryNumber 함수 호출
            case 4: printf("\nProgram Terminated."); flag=0; break; }   //sel=4 일 때, 문자열 출력 및 flag=0으로 do while문 break
    } while (flag); //flag의 값이 0일 때까지 반복
    return 0;//함수 종료
}

void funcRiemannSum() {

    int a,b,c,inivalue,finvalue,numsqr; //ax^2+bx+c 형태의 함수에서 a,b,c와 값의 범위 및 사각형의 수에 해당하는 변수 선언
    float dx;   //실수형 변수 dx 선언
    char RiemannAns;    //문자형 RiemannAns 변수 선언
    do {
        getchar(); //버퍼 제거
        printf("\nEnter integer coefficients [a b c]: ");   //문자열 출력
        scanf("%d %d %d",&a,&b,&c); //함수의 계수 입력받음
        getchar();  //버퍼 제거
        printf("Enter the initial value of x: ");   //문자열 출력
        scanf("%d",&inivalue);  //initial 값 입력받는다.

        while (1) {     //finalvalue가 initial보다 작지 않도록 반복문 선언
            getchar();  //버퍼 제거
            printf("Enter the final value of x: "); //문자열 출력
            scanf("%d", &finvalue); //finvalue 값 입력받는다.
            if(inivalue>=finvalue) printf("Final value of x must be greater than initial value\n"); //비정상적인 finalvalue임을 알려준다.
            else break; //정상적일 경우 반복문 빠져나온다.
        }

        while(1) {  //numsqr, 사각형 개수가 양수로 입력받도록 반복문 선언
            getchar();  //버퍼 제거
            printf("\nEnter the number of approximating rectangles: "); //문자열 출력
            scanf("%d", &numsqr);   //사각형의 개수를 입력받는다.
            if(numsqr>0) break; //양수일경우 반복문 빠져나온다.
            else printf("Number of rectangles must be positive\n"); //음수일경우 양수로 입력하라는 메세지
        }

        dx=(finvalue-inivalue)/(float)numsqr;   //dx의 값은 initial과 final value 값을 사각형 개수의 값으로 나눠준다.

        calcRiemannSum(a,b,c,inivalue,finvalue,numsqr,dx);  //calcRiemannSum함수 호출하여 RiemannSum 계산
        getchar();  //버퍼 제거
        printf("\nDo you want to continue(y/n)> "); //문자열 출력
        scanf("%c",&RiemannAns);   //RiemannAns을 문자형으로 받는다.

    } while (RiemannAns=='y'||RiemannAns=='Y'); //RiemannAns가 y일 때 다시 반복하고 아닐경우 break한다.
    printf("\n\n"); //줄바꿈
}

void calcRiemannSum(int a,int b,int c,int inivalue,int finvalue,int numsqr,float dx) {  //a,b,c,inivalue,finvalue 등 여러 매개변수를 받는다.
    float RMsum_1=0,RMsum_2=0,RMsum_3=0;    //left,mid,right를 각각 1,2,3순으로 변수를 만들어 저장한다.
    float i;    //i 선언, x좌표라고 생각한다.
    printf("Estimated Area : \n");  //문자열 출력
    for(i=inivalue; i<=finvalue-dx; i+=dx)  //left hand는 initial에서 시작해서고 i는 dx씩 더해가고, finvalue-dx보다 작거나 같을 경우 반복한다.
    {
        RMsum_1+= (a * i * i + b * i + c) * (float)dx;  //dx * 함수값 (ax^2+bx+c)의 결과를 더해준다.
    }

    for(i=inivalue+(0.5*dx); i<finvalue; i+=dx) //midpoint sum은 initial에서 dx의 절반만큼 더한 지점에서 시작하고 i dx를 더해주고 finvalue보다 작을 경우 반복한다.
    {
        RMsum_2+=(a * i * i + b * i + c) * (float)dx;   //dx * 함수값 (ax^2+bx+c)의 결과를 더해준다.
    }
    for(i=inivalue+dx; i<=finvalue; i+=dx)  //right hand는 initial에서 dx더한 지점에서 시작하고 i에 dx를 더해주며 ,i가 finvalue보다 작거나 같을 경우 반복한다.
    {
        RMsum_3+=(a * i * i + b * i + c) * (float)dx;   //dx * 함수값 (ax^2+bx+c)의 결과를 더해준다.
    }
    printf("\nLefthand sum: %.4f sq. units",RMsum_1);   //소수점 4자리까지 lefthand sum을 출력한다.
    printf("\nMidpoint sum: %.4f sq. units",RMsum_2);   //소수점 4자리까지 midpoint sum을 출력한다.
    printf("\nRighthand sum: %.4f sq. units\n",RMsum_3);    //소수점 4자리까지 righthand sum을 출력한다.
}

void funcRomanNumerals() {
    int ans;    //숫자를 받기 위해 ans 함수를 선언한다.
    char RomanAns;  //RomanAns라는 y/n 판정하기 위한 문자형 변수를 선언한다.

    do {    //y/n 판정을 위한 do while문 선언
        while (1) { //number 값이 음수이거나 1000보다 클때를 대비하여 반복문 선언
            printf("\nEnter number: "); //문자열 출력
            scanf("%d",&ans);   //ans값을 입력받는다.
            if (ans<0) printf("The number should be positive\n");   //음수일 때 문자열 출력해준다.
            else if (ans>1000) printf("The number should be equal to or less than 1000\n"); //1000초과일때 1000미만으로 하도록 문자열 출력
            else break; //정상적인 값일 경우 break 한다.
        }
        if (ans==1000) {
            printf("Decimal Number: %d\n", ans); //ans 값과 문자열을 출력해준다.
            printf("Roman Numerals: M\n");
        }
        else {
            printf("Decimal Number: %d\n", ans); //ans 값과 문자열을 출력해준다.
            printRoman(ans);    //printRoman() 함수 호출한다.
        }
        getchar();  //버퍼 제거
        printf("\nDo you want to continue(y/n)> "); //문자열 출력
        scanf("%c", &RomanAns);  //Romans값을 받는다.

    }while (RomanAns=='Y'||RomanAns=='y'); //RomanAns가 y일 때 다시 반복하고 아닐경우 break한다.
    printf("\n\n"); //줄바꿈
}

void printRoman(int num) { //num을 매개변수로 받는다.
    printf("Roman Numerals: "); //문자열 출력
    printHundreds(num/100); //num의 100의 자리 수를 printHundreds 함수에 넣어 호출한다.
    printTens(num%100/10);  //num의 10의 자리 수를 printTens 함수에 넣어 호출한다.
    printOnes(num%10);  //num의 1의 자리 수를 printOnes 함수에 넣어 호출한다.
    printf("\n");   //줄바꿈
}
void printHundreds(int n1)  //100의 자리숫자 n1값을 받는다.
{
    switch(n1) {    //100의 자리숫자 n1에 대하여 스위치문 선언
        case 1: printf("C"); break;
        case 2: printf("CC"); break;
        case 3: printf("CCC"); break;
        case 4: printf("CD"); break;
        case 5: printf("D"); break;
        case 6: printf("DC"); break;
        case 7: printf("DCC"); break;
        case 8: printf("DCCC"); break;
        case 9: printf("CM"); break;
    }
}
void printTens(int n2) {    //10의 자리숫자 n2를 받는다.
    switch(n2) {    //10의 자리숫자 n2에 대하여 스위치문 선언
        case 1: printf("X"); break;
        case 2: printf("XX"); break;
        case 3: printf("XXX"); break;
        case 4: printf("XL"); break;
        case 5: printf("L"); break;
        case 6: printf("LX"); break;
        case 7: printf("LXX"); break;
        case 8: printf("LXXX"); break;
        case 9: printf("XC"); break;
    }
}
void printOnes(int n3) {    //1의 자리숫자 n3를 받는다.
    switch(n3) {    //1의 자리숫자 n3에 대하여 스위치문 선언
        case 1: printf("I"); break;
        case 2: printf("II"); break;
        case 3: printf("III"); break;
        case 4: printf("IV"); break;
        case 5: printf("V"); break;
        case 6: printf("VI"); break;
        case 7: printf("VII"); break;
        case 8: printf("VIII"); break;
        case 9: printf("IX"); break;
    }
}

void funcMysteryNumber() {
    int number,MNsum,i,cPrime;  //number로 입력받을 변수 선언, 자리수에 대해 주어진 식을 저장해줄 MNsum변수, 반복문에 쓰일 i 변수, Prime 여부를 받아올 함수 선언
    char MNAns; //y/n을 값을 받아주는 문자형 변수 MNAns 선언
    int numcount,count; //반복문에서 10씩 나눠지며 자리수 계산에 필요한 변수, numcount 선언 및자리수를 세줄 count 변수 선언
    do {    //y/n을 판단하기 위한 do while 문 선언

        while (1) { //number에 정상적인 수를 입력받기 위해 반복문 선언
            MNsum=0;    //MNsum 값 0으로 초기화
            printf("\nEnter your number: ");    //문자열 출력
            scanf("%d",&number);    //number 값을 입력받는다.
            if (number<0) printf("Positive values only\n"); //음수일 경우 양수로 하라는 문자열 출력
            else if (number>1000000000) printf("The number should be equal to or less than 1000000000\n");  //특정 값을 넘을 경우 그 아래로 받도록 문자열 출력
            else break; //정상적인 값을 받으면 break한다.
        }
        numcount=number,count=0;    //numcount에 number로 값을 초기화, 자리수를 세줄 count 의 값을 0으로 초기화한다.
        while(1) {  //자리수 계산을 위한 반복문 선언
            if(numcount<=0) break;  //numcount가 0보다 작거나 같을 경우 break;
            numcount/=10;//num값을 10으로 나눠주고
            count++;//count의 값을 1 증가 시킨다.
        }
        int j=0;    //i값을 받아 각자리수를 추출해줄 j변수 선언
        for(i=number;i>0;i/=10) {
            j=i;    //j=i 값으로 초기화
            while(1) {  //반복문

                if (j > 10) {   //j가 1자리 숫자가 될때까지 if 문 실행
                    j=i%10; //j는 i를 10으로 나눈 나머지 값으로 초기회
                }
                else break; //한자리 수가 되면 break한다.
            }
            MNsum+=pow(j,count);    //MNsum에 j의 count 제곱을 더해준다.
            count--;    //count 의 값을 1 빼준다.
        }
        int calc;   //정수형 변수 calc 선언
        cPrime=checkPrime(MNsum);   //cPrime에 Prime 여부를 확인 해주는 함수 checkPrime 호출
        if (cPrime==0) {    //cPrime이 0(소수가 아님)일 경우
            calc=minDigit(number);  //calc에 minDigit함수를 호출하여 각자리수 중 가장 작은 숫자 반환.
            MNsum-=calc; //MNsum에 calc 값을 빼준다.
        }
        else if (cPrime==1) {   //cPrime이 1(소수) 일 경우
            calc=maxDigit(number);  //calc에 maxDigit함수를 호출하여 각자리수 중 가장 큰 숫자 반환.
            MNsum+=calc; //MNsum에 calc 값을 더한다.
        }
        printf("The final result of the input %d is: %d\n",number,MNsum);   //number,MNsum과 문자열을 출력한다.
        getchar();  //버퍼 제거
        printf("\nDo you want to continue(y/n)> "); //문자열 출력
        scanf("%c",&MNAns); //MNAns의 값을 받는다.
    } while (MNAns=='y'||MNAns=='Y');   //MNAns가 y일 때 다시 반복하고 아닐경우 break한다.
    printf("\n\n"); //줄바꿈
}

int checkPrime(int num) {
    int i,Prime=1;  //정수형 변수 i 선언하고 Prime 값을 1로 초기화
    for (int i=num-1;i>1;i--)   //num 값보다 1작은 수부터 1씩 작아지며 반복하고, i가 1보다 클때만 실행함.
    {
        if(num%i==0) {  //num이 i로 나눈 나머지가 0인경우 (소수가 아님)
            Prime=0;    //Prime을 0으로 초기화한다.
            break;  //break한다.
        }
    }
    return Prime;   //Prime 값을 반환한다.
}

int maxDigit(int num) {
    int i,result=0; //for문을 위해 i를 선언하고 result 값을 0으로 초기화한다.
    for(i=num;i>0;i/=10) {  //i=num으로 초기화 해주고 i가 0보다 클경우 반복하며 i를 10씩 나눠준다.
        if(i%10>result) result=i%10;  //i를 10으로 나눈 나머지가 result보다 클경우 그 값을 result 값으로 초기화한다.
    }
    return result; //result 값을 반환한다.
}

int minDigit(int num) {
    int i,result=9; //for문을 위해 i를 선언하고 result 값을 9로 초기화 해준다.
    for(i=num;i>0;i/=10) {  //i=num으로 초기화 해주고 i가 0보다 클경우 반복하며 i를 10씩 나눠준다.
        if(i%10<result) result=i%10;    //i를 10으로 나눈 나머지가 result 보다 작을 경우 그 값을 result 값으로 초기화한다.
    }
    return result;  //result 값을 반환한다.
}