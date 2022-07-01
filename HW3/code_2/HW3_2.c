#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char card[2];
    int number;
    struct Node* next;
};
int count=0;
int record[13]={0};
struct Node *head=NULL;
struct Node *current=NULL;
char input[2];

int card_number(char card[2])
{
    int temp=0;
    int i=0;
    if(card[0]=='K')
    {
        return 13;
    }
    else if(card[0]=='Q')
    {
        return 12;
    }
    else if(card[0]=='J')
    {
        return 11;
    }
    else if(card[0]=='A')
    {
        return 1;
    }
    else
    {
        while(card[i]>='0' && card[i]<='9')
        {
            temp*=10;
            temp+=card[i]-'0';
            i++;
        }
        return temp;
    }
}

void input_data()
{
    struct Node* first_node = (struct Node*)malloc(sizeof(struct Node));
    scanf("%s",first_node->card);
    first_node->number=card_number(first_node->card);
    first_node->next=NULL;
    head=first_node;
    current=first_node;
    count++;
    while(count<12)
    {
        struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
        scanf("%s",new_node->card);
        new_node->number=card_number(new_node->card);

        new_node->next=NULL;
        current->next=new_node;
        current=new_node;
        count++;
    }
    struct Node* last_node = (struct Node*)malloc(sizeof(struct Node));
    scanf("%s",last_node->card);
    last_node->number=card_number(last_node->card);
    last_node->next=head;
    current->next=last_node;
    count++;
}

void print_out(int n)
{
    while(n>0)
    {
        if(current->number!=n)
        {
            for(int i=n;i>0;i--)
            {
                printf("%s",current->card);
                if(i!=1)
                {
                    printf(" ");
                }
                current=current->next;
            }
            printf("\n");
            current=current->next;
        }
        else
        {
            for(int i=n;i>0;i--)
            {
                printf("%s",current->card);
                if(i!=1)
                {
                    printf(" ");
                }
                current=current->next;
            }
            if(count>0)
            {
                printf("\n");
            }
            break;
        }
    }
}

void count_down()
{
    while(count>0)
    {
        print_out(count--);
        struct Node*temp=current;
        head=current->next;
        current=head;
        free(temp);
        for(int i=0;i<count-1;i++)
        {
            current=current->next;
        }
        current->next=head;
        current=head;
    }
}

int main()
{
    input_data();
    current=head;
    count_down();
    return 0;
}
