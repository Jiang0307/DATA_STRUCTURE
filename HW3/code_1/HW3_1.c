#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char input[10];
int status=0;
int* output_array;
int* larger_array;
int array_length=0;

struct STACK
{
    int data;
    struct STACK* next;
};
typedef struct STACK STACK;
STACK* top=NULL;

struct QUEUE_A
{
    int data;
    struct QUEUE_A* next;
};
typedef struct QUEUE_A QUEUE_A;
QUEUE_A* A_front=NULL;
QUEUE_A* A_rear=NULL;

struct QUEUE_B
{
    int data;
    struct QUEUE_B* next;
};
typedef struct QUEUE_B QUEUE_B;
QUEUE_B* B_front=NULL;
QUEUE_B* B_rear=NULL;

void dynamic_array(int value,int length)
{
    larger_array=(int*)malloc(sizeof(int) * length+1 );
    for(int i=0;i<length;i++)
    {
        larger_array[i]=output_array[i];
    }
    output_array=larger_array;
    output_array[length]=value;
    array_length++;
}

void PUSH()
{
    //top指向最新push進來的
    int push_in=0;
    scanf("%d",&push_in);
    STACK* stack=(STACK*)malloc(sizeof(STACK));
    stack->data=push_in;

    if(top==NULL)//top沒有指向東西
    {
        stack->next=NULL;
    }
    else
    {
        stack->next=top;
    }
    top=stack;
}

int POP()
{
    STACK* temp=NULL;
    int output=0;
    if(top!=NULL)
    {
        temp=top;
        output=temp->data;
        top=top->next;
        free(temp);
        //printf("POP %d\n",output);
        return output;
    }
}

void ENQUEUE(int value)
{
    char space,A_B;
    scanf("%c",&space);
    scanf("%c",&A_B);

    if(A_B=='A')
    {
        QUEUE_A *new_node=(QUEUE_A*)malloc(sizeof(QUEUE_A));
        new_node->data=value;
        new_node->next=NULL;
        if(A_front==NULL)
        {
            A_front=new_node;
            A_rear=new_node;
        }
        else
        {
            A_rear->next=new_node;
            A_rear=new_node;
        }
    }

    else if(A_B=='B')
    {
        QUEUE_B *new_node=(QUEUE_B*)malloc(sizeof(QUEUE_B));
        new_node->data=value;
        new_node->next=NULL;
        if(B_front==NULL)
        {
            B_front=new_node;
            B_rear=new_node;
        }
        else
        {
            B_rear->next=new_node;
            B_rear=new_node;
        }
    }
}

void DEQUEUE()
{
    char space,A_B;
    scanf("%c",&space);
    scanf("%c",&A_B);

    if(A_B=='A')
    {
        QUEUE_A* current=A_front;
        if(A_front==A_rear)
        {
            dynamic_array(current->data,array_length);
            free(current);
            A_front=NULL;
            A_rear=NULL;
        }
        else
        {
            dynamic_array(current->data,array_length);
            A_front=A_front->next;
            current->next=NULL;
            free(current);
        }
    }

    if(A_B=='B')
    {
        QUEUE_B* current=B_front;
        if(B_front==B_rear)
        {
            dynamic_array(current->data,array_length);
            free(current);
            B_front=NULL;
            B_rear=NULL;
        }
        else
        {
            dynamic_array(current->data,array_length);
            B_front=B_front->next;
            current->next=NULL;
            free(current);
        }
    }
}
int main()
{
    while(scanf("%s",input)!= EOF)
    {
        if(input[0]=='P' && input[1]=='U' && input[2]=='S' && input[3]=='H')
        {
            status=1;
        }
        else if(input[0]=='P' && input[1]=='O' && input[2]=='P')
        {
            status=2;
        }
        else if(input[0]=='E')
        {
            status=3;
        }
        else if(input[0]=='D')
        {
            status=4;
        }
        switch(status)
        {
            //PUSH
            case 1:
                PUSH();
                status=0;
                break;
            //POP
            case 2:
                //POP();
                status=0;
                break;
            //ENQUEUE
            case 3:
                ENQUEUE( POP() );
                status=0;
                break;
            //DEQUEUE
            case 4:
                DEQUEUE();
                status=0;
                break;
        }
    }
    for(int i=0;i<array_length;i++)
    {
        if(i!=array_length-1)
        {
            printf("%d\n",output_array[i]);
        }
        else
        {
            printf("%d",output_array[i]);
        }
    }
    return 0;
}
