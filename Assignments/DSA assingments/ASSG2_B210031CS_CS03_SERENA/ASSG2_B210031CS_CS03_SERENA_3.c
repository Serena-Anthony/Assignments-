/*Given two Arrays check whether they are similar or not using Hashing (Do not use sorting). The
arrays are of same size(i.e n).*/

#include<stdio.h>
#include<stdlib.h>

int hash(int a[], int b[], int n)
{
    int hash[1000]={0};

    int flag =0;
    for(int i=0; i<1000; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(a[j]==i)
            {
                hash[i]++;
            }
        }
    }

    for(int i=0; i<1000; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(b[j]== i)
            {
                hash[i]--;
            }
        }
    }

    for(int i=0; i<1000; i++)
    {
       // printf("%d ", hash[i]);
        if(hash[i]!=0)
        {
            flag =1;
        }
    }

    if(flag ==0) // arrays r similar
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[1000], b[1000];
    
    // 2 arrays of same size
    // similar : same frequeny of elemnts 
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i=0; i<n; i++)
    {
        scanf("%d", &b[i]);
    }

    hash(a,b,n);
}


