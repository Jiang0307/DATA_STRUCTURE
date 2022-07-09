#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 13
#define PRIME 7

int input[13]={0};
int hash1[13]={0};
int hash2[13]={0};
int output[13]={0};

void HASH1()
{
    for(int i=0;i<13;i++)
    {
        int temp = (input[i]%TABLE_SIZE);
        hash1[i] = temp;
    }
}

void HASH2()
{
    for(int i=0;i<13;i++)
    {
        int temp =  (PRIME-(input[i]%PRIME));
        hash2[i] = temp;
    }
}

int calculate(int a,int b,int j)
{
    return (a+(j*b))%13;
}

void insert()
{
    for (int i = 0; i < 13; i++)
	{
		int a = hash1[i];
		int b = hash2[i];
		int j = 0;
		int index=calculate(a,b,j);
		if (output[index] == 0)
		{
			output[index] = input[i];
		}
		else
		{
			do
			{
				index = calculate(a, b, j++);
			} while (output[index] > 0);
			output[index] = input[i];
		}
	}
}

void print()
{
    for(int i=0;i<13;i++)
    {
        printf("%d->%d",i,output[i]);
        if(i!=12)
        {
            printf("\n");
        }
    }
}

int main()
{
    for(int i=0;i<13;i++)
    {
        scanf("%d",&input[i]);
    }
    HASH1();
    HASH2();
    insert();
	print();
    return 0;
}
