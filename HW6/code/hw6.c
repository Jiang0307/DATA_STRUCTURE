#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define MAXSIZE 1000
int count=0;
int count2=0;
int new_line=1;
int no_insert=0;
int D_step=0;

typedef struct node
{
    struct node *left;
    struct node *right;
    char name[MAXSIZE];
    char phone[MAXSIZE];
    int height;
} NODE;

NODE *root = NULL;

NODE *newNode(char name[], char phone[])
{
    NODE *node = (NODE *) malloc(sizeof(NODE));
    strncpy(node->name, name, strlen(name));
    strncpy(node->phone, phone, strlen(phone));
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

int height(NODE *node)
{
    return node ? node->height : 0;
}

int getBalance(NODE *node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

NODE *rightRotate(NODE *node)
{
    NODE *leftNode = node->left;
    NODE *leftRightNode = leftNode->right;
    leftNode->right = node;
    node->left = leftRightNode;
    node->height = 1 + max(height(node->left),height(node->right));
    leftNode->height = 1 + max(height(leftNode->left),height(leftNode->right));
    return leftNode;
}

NODE *leftRotate(NODE *node)
{
    NODE *rightNode = node->right;
    NODE *rightLeftNode = rightNode->left;
    rightNode->left = node;
    node->right = rightLeftNode;
    node->height = 1 + max(height(node->left),height(node->right));
    rightNode->height = 1 + max(height(rightNode->left),height(rightNode->right));
    return rightNode;
}

NODE *insert(NODE *subRoot, char name[], char phone[])
{
    if (subRoot == NULL)
    {
        return newNode(name, phone);
    }
    if (strcmp(name, subRoot->name) > 0)
        subRoot->right = insert(subRoot->right, name, phone);
    else if (strcmp(name, subRoot->name) < 0)
        subRoot->left = insert(subRoot->left, name, phone);
    else
        return NULL;
    subRoot->height = 1 + max(height(subRoot->left), height(subRoot->right));
    int balance = getBalance(subRoot);
    if (balance > 1 && strcmp(name, subRoot->left->name) < 0)
        return rightRotate(subRoot);

    if (balance > 1 && strcmp(name, subRoot->left->name) > 0)
    {
        subRoot->left = leftRotate(subRoot->left);
        return rightRotate(subRoot);
    }

    if (balance < -1 && strcmp(name, subRoot->right->name) > 0)
        return leftRotate(subRoot);

    if (balance < -1 && strcmp(name, subRoot->right->name) < 0)
    {
        subRoot->right = rightRotate(subRoot->right);
        return leftRotate(subRoot);
    }
    return subRoot;
}

NODE *search(NODE *subRoot, char *name)
{
    if (subRoot != NULL)
    {
        if (!strcmp(subRoot->name, name))
        {
            return subRoot;
        }
        else
        {
            //name比當前節點的name還要小，往左邊搜尋
            if (strcmp(name, subRoot->name) < 0)
                return search(subRoot->left, name);
            else
                return search(subRoot->right, name);
        }
    }
    else
        return NULL;
}

void preOrder(NODE *subtreeRoot)
{
    if (subtreeRoot)
    {
        printf("%s", subtreeRoot->name);
        count--;
        if (subtreeRoot->left != NULL)
        {
            if(count>0)
                printf(" ");
        }
        preOrder(subtreeRoot->left);
        if (subtreeRoot->right != NULL)
        {
            if(count>0)
                printf(" ");
        }
        preOrder(subtreeRoot->right);
    }
}

int main()
{
    char opt;
    int flag = 1;
    //Read 'D'
    scanf("%s",&opt);
    while(1)
    {
        char name[100]={'\0'}, phone[100]={'\0'};
        scanf("%s",name);
        //Read 'S'
        if(strlen(name) == 1)
        {
            new_line=0;
            break;
        }
        scanf("%s",phone);
        count++;
        D_step++;
        root = insert(root,name,phone);
    }
    preOrder(root);
    //搜尋電話

    while(1)
    {
        char name[100] = {'\0'};
        scanf("%s",name);
        //Read'E'
        if(strlen(name) == 1)
            break;
        else
            count2++;
        if(count2>0 && D_step>0)
            printf("\n");
        NODE* node = search(root,name);
        if(node)
        {
            printf("%s %s",node->name,node->phone);
            continue;
        }
        printf("%s null",name);
        D_step++;
    }
    return 0;
}
