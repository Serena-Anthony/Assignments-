#include <stdio.h>
int length =0;

void min_heapify(int Q[],int i,int n)
{
    int l,r,smallest=i;
    l=2*i+1;
    r=2*i+2;
    if (l<n && Q[l]<Q[i])
    {
        smallest=l;
    }
    if (r<n && Q[r]<Q[smallest])
    {
        smallest=r;
    }
    if (smallest!=i)
    {
        int temp=Q[i];
        Q[i]=Q[smallest];
        Q[smallest]=temp;
        min_heapify(Q,smallest,n);
    }
}

void build_min_heap(int Q[],int n)
{
    for(int i=n/2-1;i>=0;i--)
    {
        min_heapify(Q,i,n);
    }
}


int insert_process(int Q[],int k)
{
Q[length]=k;
    length++;
    if(length!=1)
    {
        build_min_heap(Q,length);
    }
}

int extract_next_process(int Q[])
{
 if(length==0)
    {
        return -1;
    }
    else
    {
        int temp=Q[0];
        Q[0]=Q[length-1];
        Q[length-1]=temp;
        length--;
        for(int i=length/2-1;i>=0;i--)
        {
            min_heapify(Q,0,length);
        }
        return temp;
    }
}

void get_next_process(int Q[])
{
if(length==0)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n",Q[0]);
    }
}

void change_priority(int Q[], int k, int x)
{
for(int i=0;i<length ;i++)
    {
        if(Q[i]==k)
        {
            Q[i]=x;
            break;
        }
    }
    for(int i=length/2-1;i>=0;i--)
    {
        min_heapify(Q,0,length);
    }
}

void display_queue(int Q[])
{
    if(length==0)
    {
        printf("-1\n");
    }
    else
    {
        for(int i=0;i<length;i++)
        {
            printf("%d ",Q[i]);
        }
        printf("\n");
    }
}

int main()
{
	int Q[10000];
	char ch;

    while (1)
    {
        int k,x;
    	scanf("%c", &ch);

        switch (ch)
        {
        	case 'i':	scanf("%d",&k);
                        insert_process(Q,k);
        				break;

        	case 'e':	printf("%d\n", extract_next_process(Q));
        				break;

        	case 'm':	get_next_process(Q);
        				break;

        	case 'c':	scanf("%d",&k);
                        scanf("%d",&x);
                        change_priority(Q,k,x);
        				break;

        	case 'd': 	display_queue(Q);
        				break;

            case 's': 	return -1;

        }
    }
}