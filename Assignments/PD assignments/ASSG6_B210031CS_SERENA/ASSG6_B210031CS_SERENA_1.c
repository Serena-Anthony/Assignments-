#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int top;
    int A[100000];
    int n;
};

int stack_empty(struct stack *ptr)
{
    if(ptr->top == -1)//array is empty
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int stack_full(struct stack *ptr)
{
    if(ptr->top == ptr->n-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int push(struct stack *ptr, int k)
{
    if(stack_full(ptr))
    {
        printf("Full\n");
    } 
    
    else
    {
        ptr->top ++;
        ptr->A[ptr->top] = k;
    }
}

int pop(struct stack *ptr)
{
    if (stack_empty(ptr))
    {
        return -10000000;
    }
    else
    {
        ptr->top--;
        return ptr-> A[ptr->top+1];
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    
    struct stack *ptr = (struct stack *)malloc(sizeof(struct stack));
    ptr->top =-1;
    ptr->n=n;
    char ch;
    while(1)
    {
        scanf("%c", &ch);
        
        switch(ch)
        {
            case 'i':
                    {   int m;
                        scanf("%d", &m);
                        push(ptr,m);
                        break;
                    } 
                    
            
            case 'd':
                    {  int k;
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
            
            case 'f': 
                    {
                      int temp = stack_full(ptr);
                      if (temp)
                      {
                          printf("YES\n");
                      }
                      else
              
                      {
                           printf("NO\n");
                      }
                      break;
                    } 

            case 'e':
                    {  int temp = stack_empty(ptr);
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

             case 't': {    return -10000000;
                           break;}
        }
    }
}

