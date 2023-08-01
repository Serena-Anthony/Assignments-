/*The three different methods for open addressing are linear probing, quadratic probing, and double hashing.*/
#include<stdio.h>
#include<stdlib.h>

int linear(int a[], int k,int n, int *col1)
{
    int i =1;
    int hash = k%n;
    int temp = hash;
    
    if(a[temp]== 0)
    {
        a[temp] = k;
        return temp;
    }

    while(a[temp]!=0 && i<=n)
    {
        (*col1)++;
        temp =(hash + i)%n;
        i++;
        if(a[temp]== 0)
        {
            a[temp] = k;
            return temp;
        }
    }
    return -10;
}

int quad(int a[], int k,int n, int *col2)
{
    int i =1;
    int hash = k%n;
    int temp = hash;

    if(a[temp]== 0)
    {
        a[temp] = k;
        return temp;
    }

    while(a[temp]!=0 && i<=n)
    {
        (*col2)++;
        temp =(hash + (i*i))%n;
        i++;
        if(a[temp]== 0)
        {
            a[temp] = k;
            return temp;
        }
    }
    return -10;
}

int maxprime(int n)
{
   int prime = -1;
   for(int i =n-1; i>= 0; i--)
   {
       int flag =0;
       for (int j=2; j<i; j++)
       {
           if(i%j == 0)
           {
               flag =1;
               break;
           }
       }
       if (flag ==0)
       {
           prime =i;
           break;
       }
   }
   return prime;
}

/*
int maxprime(int n)
{
    int prime = -1;
    for(int i = n-1; i>=0; i--)
    {
        int flag =0;
        for(int j =2; j < i ; j++)
        {
            if(i%j == 0)
            {
                flag = 1;
                break;
            }
        }
        if(flag ==0)
        {
            prime = i;
            break;
        }
    }
    return prime;
}
*/

int doublehash(int a[], int k,int n, int *col3)
{
    int i =0;
    int h1= k%n;
   
    int r = maxprime(n);
    
    int h2 = r - (k %r);
    int temp = (h1 + i*h2)%n;
   
    if(a[temp]== 0)
    {
        a[temp] = k;
        return temp;
    }

    while(a[temp]!=0 && i<n)
    {
        (*col3)++;
         i++;
        temp = (h1 + i*h2)%n;
        if(a[temp]== 0)
        {
            a[temp] = k;
            return temp;
        }
    }
    return -10;
}

int main()
{
    int n;
    scanf("%d", &n);
    int b[1000];
    int a[1000];
    
    for(int i=0; i<n; i++)
    {
        a[i]= 0;
    }
    
    int i =0;
    char c;
    while(1)
    {
        scanf("%d%c", &b[i++],&c);

        if(c=='\n')
        {
            break;
        }
    }
    int len = i;
 
    int col1=0, col2=0, col3=0;
   
    int k;
    for( i=0; i<len;i++)
    {
        k= b[i];
        int temp = linear(a,k,n,&col1);
        if(temp != -10)
        {
        printf("%d ",temp);
        }
        else
        {
            printf("E\n");
        }
    }
    printf("\n");
    printf("%d\n", col1);
    
    for(int i=0; i<n; i++)
    {
        a[i]= 0;
    }
    
    int j;
    for( i=0; i<len;i++)
    {
        j= b[i];
        int temp = quad(a,j,n,&col2);
        if(temp != -10)
        {
        printf("%d ",temp);
        }
        else
        {
            printf("E\n");
        }
    }
    printf("\n");
    printf("%d\n", col2);
   
    
    for(int i=0; i<n; i++)
    {
        a[i]= 0;
    }
    
    int m;
    for( i=0; i<len;i++)
    {
        m= b[i];
        int temp = doublehash(a,m,n,&col3);
        if(temp != -10)
        {
        printf("%d ",temp);
        }
        else
        {
            printf("E\n");
        }
    }
    printf("\n");
    printf("%d\n", col3);
}