#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main(int argc,char **argv)
{
    int n=0;
    int length;
    int base;
    int result;
    int temp;//用來記錄length除6的商
    char c;
    char arr[10000];
    char arr2[40000];
    char arr3[40000];
    char BASE64[64]=
    {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','+','/'
    };
    //get opt
    while((c=getopt(argc,argv,"i:o:")) != EOF){
        switch(c){
            case 'i':
            freopen(optarg,"r",stdin);
            break;
            case 'o':
            freopen(optarg,"w",stdout);
            break;
        }
    }
    //將每一個輸入的Hex digit轉為4bit一組
    while(scanf("%s",arr) != EOF)
    {
        for(int i=0;i<strlen(arr);i++)
        {
            switch(arr[i])
            {
                case '0':
                    strcat(arr2, "0000");
                    break;
                case '1':
                    strcat(arr2, "0001");
                    break;
                case '2':
                    strcat(arr2, "0010");
                    break;
                case '3':
                    strcat(arr2, "0011");
                    break;
                case '4':
                    strcat(arr2, "0100");
                    break;
                case '5':
                    strcat(arr2, "0101");
                    break;
                case '6':
                    strcat(arr2, "0110");
                    break;
                case '7':
                    strcat(arr2, "0111");
                    break;
                case '8':
                    strcat(arr2, "1000");
                    break;
                case '9':
                    strcat(arr2, "1001");
                    break;
                case 'a':
                case 'A':
                    strcat(arr2, "1010");
                    break;
                case 'b':
                case 'B':
                    strcat(arr2, "1011");
                    break;
                case 'c':
                case 'C':
                    strcat(arr2, "1100");
                    break;
                case 'd':
                case 'D':
                    strcat(arr2, "1101");
                    break;
                case 'e':
                case 'E':
                    strcat(arr2, "1110");
                    break;
                case 'f':
                case 'F':
                    strcat(arr2, "1111");
                    break;
            }
        }
        //優化效率
        length = strlen(arr2);
        switch(length%6)
        {
            //整除的狀況
            case 0:
                for(int i=0;i<length;i+=6)
                {
                    base = 1,result = 0;
                    for(int j=i+5;j>=i;j--)
                    {
                        result += ( arr2[j] - '0' ) * base;
                        base <<= 1;
                    }
                    printf("%c",BASE64[result]);
                }
                break;
            //補2個=
            case 2:
                //小於24bit的時候暴力解
                if(length<24)
                {
                    base = 1<<5 , result =0;
                    for(int i=0;i<6;i++)
                    {
                        result += (arr2[i] - '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);

                    base = 1<<5 , result =0;
                    for(int i=6;i<8;i++)
                    {
                        result += (arr2[i] - '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);
                    printf("==");
                }

                else if(length>24)
                {
                    //可以被6整除的部分
                    for(int i=0;i<length-2;i+=6)
                    {
                        base = 1,result = 0;
                        for(int j=i+5;j>=i;j--)
                        {
                            result += ( arr2[j] - '0' ) * base;
                            base <<= 1;
                        }
                        printf("%c",BASE64[result]);
                    }
                    base = 1<<5,result = 0;
                    //剩下的2個bit
                    for(int i=length-2;i<length;i++)
                    {
                        result += (arr2[i]- '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);
                    printf("==");
                }

                break;
            //補1個=
            case 4:
                //小於24bit的時候暴力解
                if(length<24)
                {
                    int i,j;
                    result=0;base=1<<5;
                    for(int i=0;i<6;i++)
                    {
                        result += (arr2[i] - '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);
                    result=0;base=1<<5;
                    for(int i=6;i<12;i++)
                    {
                        result += (arr2[i] - '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);
                    result=0;base=1<<5;
                    for(int i=12;i<16;i++)
                    {
                        result += (arr2[i] - '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);
                    printf("=");
                }
                else if(length>24)
                {
                    //可以被6整除的部分
                    for(int i=0;i<length-4;i+=6)
                    {
                        base = 1,result = 0;
                        for(int j=i+5;j>=i;j--)
                        {
                            result += ( arr2[j] - '0' ) * base;
                            base <<= 1;
                        }
                        printf("%c",BASE64[result]);
                    }
                    base = 1<<5,result = 0;
                    //剩下的4個bit
                    for(int i=length-4;i<length;i++)
                    {
                        result += (arr2[i]- '0') * base;
                        base >>= 1;
                    }
                    printf("%c",BASE64[result]);
                    printf("=");
                }
                break;
        }
        //每次執行完清空陣列
        memset(arr2,'\0',strlen(arr));
        memset(arr2,'\0',length);
        printf("\n");
    }
    return 0;
}
