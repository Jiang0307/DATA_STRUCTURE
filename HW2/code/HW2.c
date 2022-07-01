#include <stdio.h>
#include <string.h>
int status;
char input[100];
char space;
char AorB;
int push[100000]={0};
int intA[100000]={0};
int intB[100000]={0};
int Index=0,IndexA=0,IndexB=0;
int countA=0,countB=0;

int main()
{

    while(scanf("%s",input)!= EOF)
    {
        //printf("%c%c%c\n",input[0],input[1],input[2]);
        if(input[0]=='P' && input[1]=='U' && input[2]=='S' && input[3]=='H')
        {
            status=1;
        }
        if(input[0]=='P' && input[1]=='O' && input[2]=='P')
        {
            status=2;
        }
        if(input[0]=='E')
        {
            status=3;
        }
        if(input[0]=='D' && input[1]=='E' && input[2]=='Q' && input[3]=='U' && input[4]=='E' && input[5]=='U' && input[6]=='E')
        {
            status=4;
        }

        switch(status)
        {
            //PUSH
            case 1:
                scanf("%d",&push[Index]);
                //printf("%d\n",push[Index]);
                Index++;
                //printf("%d\n",Index);
                status=0;
                break;
            //POP
            case 2:
                status=0;
                break;
            //ENQUEUE
            case 3:
                scanf("%c",&space);
                scanf("%c",&AorB);
                if(AorB == 'A')
                {
                    intA[IndexA] = push[Index-1];
                    //printf("%d",intA[countA]);
                    IndexA++;
                    //countA++;
                    if(Index>0)
                    {
                        Index--;
                    }
                }
                else if(AorB == 'B')
                {
                    intB[IndexB] = push[Index-1];
                    //printf("%d",intB[countB]);
                    IndexB++;
                    //countB++;
                    if(Index>0)
                    {
                        Index--;
                    }
                }
                status=0;
                break;
                //DEQUEUE
            case 4:
                scanf("%c",&space);
                scanf("%c",&AorB);
                if(AorB == 'A')
                {
                    printf("%d\n",intA[countA]);
                    countA++;
                }
                else if(AorB == 'B')
                {
                    printf("%d\n",intB[countB]);
                    countB++;
                }
                status=0;
                break;
        }
    }

    return 0;
}
