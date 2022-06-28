#define _CRT_SECURE_NO_WARNING
#include <stdio.h>

float average(int x, int y);
char grade(float score);
int main( )
{
    float allavg=0;
    int sid,mid,fin,numst=0;
    float stavg;
    FILE* infile , *outfile;

    infile = fopen("score.txt","r");
    if (infile == NULL)
    {
        printf("Cannot open input file.\n");
        return 100;
    }
    outfile = fopen("output.txt","w");

    fprintf(outfile , "=============================\n");
    fprintf(outfile , "   학번            총점(학점)\n");
    fprintf(outfile , "=============================\n");
    while (fscanf(infile,"%d %d %d",&sid,&mid,&fin )  != EOF)
    {
        stavg=average(mid,fin);
        fprintf(outfile,"%d            %.1f (%c)\n",sid,stavg,grade(stavg));
        numst+=1;
        allavg+=stavg;
    }
    fprintf(outfile , "=============================\n");
    fprintf(outfile , "   평균            %.1f\n",allavg/numst);
    fprintf(outfile , "=============================\n");

    fclose(outfile);
    fclose(infile);

    return 0;
}
float average(int x, int y) {
    return (float)((0.4)*x+(0.6)*y);
}
char grade(float score) {
    char grade;

    switch((int)score/10) {
    case 10: case 9: grade ='A'; break;
    case 8: grade ='B'; break;
    case 7: grade ='C'; break;
    case 6: grade ='D'; break;
    default: grade='F'; break;
    }
    return grade;
}