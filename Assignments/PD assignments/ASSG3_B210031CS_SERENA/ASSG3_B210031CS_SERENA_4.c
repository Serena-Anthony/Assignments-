#include<stdio.h>
//define functions

    int read_and_store(int A[],int n)
    {   
        for (int i=0;i<n;i++) 
        { scanf ("%d", &A[i]) ;}
    }

    int print(int A[], int n)
    {    for (int j=0; j<n ; j++) 
        { 
            printf ("%d ", A[j]);
        }
        printf("\n");
    }

    int digit_sum( int t)
    {   
        int sum =0;
            while( t>0)
              { int r = t%10;
                sum = sum + r;
                t/=10;
              } 
        return sum;
    }

    int digit_sort(int A[],int n) 
    {
        int temp[n];
        for(int a=0; a<n ; a++)
        {
            temp[a] = digit_sum (A[a]);        
        }
        int i,j,k;
        int key,item;
        for (j=0; j<n;j++)
        {
            key = temp[j];
            item=A[j];
            i=j-1;

            while (i>=0 && temp[i]> key)
            {
                temp[i+1] = temp [i];
                A[i+1]=A[i];
                i=i-1;
            }
            temp [i+1] = key;
            A[i+1]=item;
        }
    }  
    
int main ()
{
    while(1)
    {
        char ch;
        int n,len,A[10000] ;
        
        scanf("%c", &ch);

        if(ch=='r')
        {   scanf ("%d", &n);
            len=n;
            read_and_store( A, n) ;}
        
        if(ch=='p')
        {  print(A,len);  }
        
        if(ch=='d')// input integer for which sum to calc
        {
            scanf ("%d", &n);
            printf("%d\n",digit_sum(A[n]));
        }

        if(ch=='s')
        {digit_sort (A,len);}

        if(ch=='t')
          { printf("-1");
              break;
          }
    }
}