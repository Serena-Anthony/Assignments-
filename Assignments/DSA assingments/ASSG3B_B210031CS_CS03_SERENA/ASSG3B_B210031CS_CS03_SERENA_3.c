#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    int rank;
    int count;
    struct node* parent;
};
// count = 0 =>non rep;

struct node* makeset(int x)
{
    struct node* temp = (struct node*)malloc (sizeof(struct node));
    temp->data = x;
    temp->rank =0;
    temp->count=1;
    temp->parent = temp;
    //printf("created\n");
    return temp;
}

struct node* findset_pathcomp(struct node* x)
{
    //printf("enterefindset\n");
    if(x!= NULL)
    {
        if(x->parent == x)
        {
            return x;
        }
        else if(x->parent != x)
        {
            x->parent = findset_pathcomp(x->parent);
            return x->parent;
        }
    }
}

struct node* ranked_link(struct node*a, struct node* b)
{
    //printf("enteredlinking\n");
    if (b->rank > a->rank)
    {
        b->count+=a->count;
        a->count=0;
        a->parent = b;
        return b;
    }
    else if (b->rank < a->rank)
    {
        b->parent = a;
        a->count+=b->count;
        b->count=0;
        return a;
    }  
    
    else if(a->rank == b->rank)
        {
            a->count+=b->count;
            b->count=0;
            a->rank = a->rank +1 ;
            b->parent = a;
            return a;
        }
}

struct node* union_both(struct node*x, struct node* y)
{
    //printf("entered union\n");
    return ranked_link(findset_pathcomp(x), findset_pathcomp(y));
}


int main()
{
    struct node *arr[1001];
    for(int i =0; i<1001; i++)
    {
        arr[i]= NULL;
    }
    int g=0;
    struct node* temp = NULL;
    struct node* temp1 = NULL;
    struct node* tempf = NULL;

    while(1)
    {
        char ch;
        scanf("%c", &ch);

        if(ch == 't')
        {
            int x,y;
            scanf("%d %d", &x ,&y);

          //  printf("scanned\n");
            
            if(arr[x]== NULL)
            {
             //   printf("set1made\n");
                arr[x] = makeset(x);
                g++;
                temp = arr[x];
            }
            //else 
            //{
                //arr[x]== -1;
            //    printf("-1\n");
           // }
            // else if (arr[x]!= NULL)
            // {
            //    temp = findset_pathcomp(x);
            // }

            if(arr[y]== NULL)
            {
             //   printf("set2made\n");
                arr[y] = makeset(y);
                g++;
                temp1 = arr[y];
             }
            // else
            // {
                //arr[y]=-1;
              //  printf("-1\n");
             //}
            // else
            // {
            //     temp1= findset_pathcomp(y);
            // }
          //  printf("going to enter union\n");
            tempf = union_both(temp, temp1);
            g--;
           // printf("%d\n", tempf->data);

        }

        if(ch == 'T')
        {
           printf("%d\n",g);
        }

        if(ch == 'd')
        {
            int freq[100];
            int j=0;
            int go=0;
            int sum=0;
            //count of all possible data collecting groups
            for(int i=0; i<1001 ;i++)
            {
                if( arr[i]!=NULL && arr[i]->count!=0)
                {
                    freq[j++]=arr[i]->count;
                    go++;
                }
                // if(arr[i])
                // {
                //     printf("%d\n",arr[i]->count);
                // }
                if(go==g)
                {
                    break;
                }
            }
           // printf("j=%d\n",j);
            for(int i=0;i<j;i++)
            {
                for(int p=i+1 ;p<j ; p++)
                {
                    //printf("%d %d \n", freq[i], freq[p]);
                    sum+=freq[i]*freq[p];
                }
            }

            if(sum==0)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n",sum);
            }
        }

        if(ch == 'v')
        {
            //checks if data collecting group is valid or not
            int x, y;
            scanf("%d %d", &x,&y);
            
            if(arr[x]==NULL|| arr[y]== NULL)
            {
                printf("-1\n");                
            }
            else if(x>y || (findset_pathcomp(arr[x]) == findset_pathcomp(arr[y])))
            {
                printf("-1\n");
            }
            else
            {
                printf("1\n");
            }
        }

        if(ch == 'e')
        {
            break;
        }
    }
}

