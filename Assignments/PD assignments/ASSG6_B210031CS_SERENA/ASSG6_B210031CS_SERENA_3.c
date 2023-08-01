#include <stdio.h>
#include <stdlib.h>

struct Q
{
    int head;
    int tail;
    int n;
    int A[100000];
};


int queue_full(struct Q *ptr)
{
    if((ptr->head==ptr->tail+1)||(ptr->head==0 && ptr->tail==ptr->n-1))
    {
        return 1;
    }
    else 
    {
    return 0;
    }
}

int queue_empty(struct Q *ptr)
{
    if(ptr->head==ptr->tail)
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

    if(queue_full(ptr))
    {
        printf("Full\n");
    }
    else
    {
        ptr->A[ptr->tail]=k;
        if(ptr->tail==ptr->n-1)
        {
            ptr->tail=0;
        }
        else
        {
            ptr->tail++;
        }
    }
}

int dequeue(struct Q *ptr, int k)
{

    if(queue_empty(ptr))
    {
        return 100000001;
    }
    else
    {
        int c=ptr->A[ptr->head];
        if(ptr->head==ptr->n-1)
        {
            ptr->head=0;
        }
        else
        {
            ptr->head++;
        }
        return c;
    }
}


int main()
{
    int n,k;
    scanf("%d", &n);
    
    struct Q *ptr = (struct Q *)malloc(sizeof(struct Q));
    ptr->head =0;
    ptr->tail=0;
    ptr->n=n;
    char ch;

    while(1)
    {
        scanf("%c", &ch);
        
        switch(ch)
        {
            case 'i':
                    {   int k;
                        scanf("%d",&k);
                        enqueue(ptr,k);
                        break;
                    } 
                    
            
            case 'd':
                    {  int k;
                       scanf("%d", &k);
                       for(int i=0;i<k;i++)
                        {
                            int c=dequeue(ptr, k);
                            if(c==100000001)
                            {
                                printf("Empty ");
                            }
                            else
                            {
                                printf("%d ",c);
                            }
                        }
                    
                    printf("\n");
                    break;
                    }
                    
            


            case 'f': 
                    {
                        {
                            if(queue_full(ptr))
                            {
                                printf("YES\n");
                            }
                            else
                            {
                                printf("NO\n");
                            }
                        }
                    break;
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
                        break;
                    }

             case 't': {    return -10000000;
                           break;}
        }                   
    }
}
