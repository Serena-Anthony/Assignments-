#include <stdio.h>
#include <stdlib.h>

struct queue
{
   int data;
   struct queue *next;
};

struct Q
{
struct queue *head;
struct queue *tail;
};

struct queue *create_node(int k)
{
    struct queue* temp= (struct queue*)malloc(sizeof(struct queue)); 
    temp->data = k;
    temp->next = NULL; 
    return temp; 
}

int queue_empty (struct Q *ptr)
{
    if(ptr->tail==NULL)
    {
        return 1;
    }
    else
    {
    return 0;
    }
}

int enqueue(struct Q *ptr, int k)
{
    struct node *link=create_node(k);
    if(ptr->head==NULL)
    {
        ptr->head=link;
    }
    else
    {
        ptr->tail->next=link;
    }
    ptr->tail=link;
}

int dequeue(struct Q *ptr)
{
    if(queue_empty(ptr))
    {
        return 100000001;
    }
    else
    {
        int c=ptr->head->data;
        if(ptr->head==ptr->tail)
        {
            ptr->tail=NULL;
        }
        ptr->head=ptr->head->next;
        return c;
    }
}

int main()
{
    int n,k;
    scanf("%d", &n);

    struct Q* ptr= (struct Q*)malloc(sizeof(struct Q));
    ptr->head=NULL;
    ptr->tail=NULL;
    char ch;

    while(1)
    {
        scanf("%c",&ch);
        switch(ch)
        {
             case 'i':
               {
                    scanf("%d",&k);
                    enqueue(ptr,k);
                }

             case 'd':
             {
                scanf("%d",&k);
                while(k!=0)
                {
                    int c=dequeue(ptr);
                    if(c==100000001)
                    {
                        printf("Empty ");
                    }
                    else
                    {
                        printf("%d ",c);
                    }
                    k--;
                }
                printf("\n");
            }

             case 'e':
            {
                if(queue_empty(ptr))
                {
                    printf("YES\n");
                }
                else
                {
                    printf("NO\n");
                }
            }

             case 't': {    return -10000000;
                           break;}


        }

    }
}    
    