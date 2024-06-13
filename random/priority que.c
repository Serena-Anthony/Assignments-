#include <stdio.h>

int parent(int i)
{
    return (i-1)/2;
}

void max_heapify(int B[],int i,int len)
{
    int l=2*i+1;
    int r=2*i+2;
    int largest=i;
    if(l<len && B[l]>B[i])
    {
        largest=l;
    }
    if(r<len && B[r]>B[largest])
    {
        largest=r;
    }
    if(largest!=i)
    {
        int temp=B[largest];
        B[largest]=B[i];
        B[i]=temp;
        max_heapify(B,largest,len);
    }
}

int extract_max(int B[],int len)
{
    int max=B[0];
    B[0]=B[len-1];
    len--;
    max_heapify(B,0,len);
    return max;
}

void insert(int B[],int key,int len)
{//includes increase key function
    int i=len;
    B[len]=key;
    len++;
    int p=parent(i);
    while(i>0 && B[p]<B[i])
    {
        int temp=B[i];
        B[i]=B[p];
        B[p]=temp;
        i=p;
        p=parent(i);
    }
}


void build_max_heap(int B[],int len)
{
    for(int i=len/2-1;i>=0;i--)
    {
        max_heapify(B,i,len);
    }
}

void increase_key(int B[],int x,int key,int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        if(B[i]==x)
        {
            B[i]=key;
            break;
        }
    }
    int p=parent(i);
    while(i>=0 && B[p]<B[i])
    {
        int temp=B[i];
        B[i]=B[p];
        B[p]=temp;
        i=p;
        p=parent(i);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int key,len=0,B[1000];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&key);
        insert(B,key,i);
        len++;
    }
    while(1)
    {
         char c;
         getchar();
        scanf("%c",&c);
        if(c=='i')
        {
            scanf("%d",&key);
            insert(B,key,len);
            len++;
        }
        else if(c=='c')
        {
            int x;
            scanf("%d %d",&x,&key);
            increase_key(B,x,key,len);
        }
        else if(c=='d')
        {
            for(int i=0;i<len;i++)
            {
                printf("%d ",B[i]);
            }
            printf("\n");
        }

        else if(c=='s')
        {
            int m = extract_max( B, len);   
            len --;
            printf("%d", m);

        }

        else if(c=='t')
        {
            printf("\n-1");
            break;
        }
    }

}