#include <stdio.h>
#include <stdlib.h>

struct stack
{
   int data;
   struct stack *next;
};

struct S
{
struct stack *top; 
};

struct stack *create_node(int k)
{
    struct stack* temp= (struct stack*)malloc(sizeof(struct stack)); 
    temp->data = k;
    temp->next = NULL; 
    return temp; 
}

int stack_empty(struct S *ptr)
{
    if(ptr->top == NULL)//array is empty
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int push(struct S *ptr , int k)
{
    struct stack* bleh = create_node(k);
    bleh->next = ptr-> top;
    ptr->top = bleh;
}

int pop(struct S* ptr )
{
     if (stack_empty(ptr))
    {
        return -10000000;
    }
    else
    {
        int c=ptr->top->data;
        ptr->top= ptr->top->next ;
        return c;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    
    struct S *ptr = (struct S *)malloc(sizeof(struct S));
    ptr->top=NULL;
    char ch;
    while(1)
    {
        scanf("%c", &ch);
        
        switch(ch)
        {
            case 'i':
                    {  int k;
                        scanf("%d", &k);
                        push(ptr,k);
                        break;
                    } 
                    

            case 'd':{  int k;
                        scanf("%d", &k);
                     
                        for(int i=0; i<k;i++)
                        {
                            int temp = pop(ptr);
                            if (temp ==-10000000)
                            {
                                printf("Empty ");
                            }
                            else
                            {  
                                printf("%d ", temp);                        
                            }
                        }   
                        printf("\n"); 
                        break;  

                     }

            case 'e': {  int temp = stack_empty(ptr);
                        if (temp==1)
                        {
                            printf("YES\n");
                        }
                        else
                        {
                            printf("NO\n");
                        }
                        break;
                      }

            case 't':    { return -10000000;
                           break;}

        }
    }    
}