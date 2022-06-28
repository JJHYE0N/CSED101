#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int upperToLower(char c)
{
    printf("Lowercase of Entered character is %c\n",(c+32));
    return c+=32;
}

void getPosition(char c)
{
    int n=c;
    n-=96;
    printf("Position of '%c' in English Alphabets is %d",c,n);
}

int main() {
    char n;
    printf("Input a character in Uppercase: ");
    scanf("%c",&n);

    n=upperToLower(n);
    getPosition(n);

    return 0;
}