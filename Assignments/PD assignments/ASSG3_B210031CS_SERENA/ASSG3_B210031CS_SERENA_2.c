#include<stdio.h>

int mergesort(int A[] , int B[], int m, int n, int temp[])
{
    int i=0, j=0, k=0;
    while (i<m && j<n)
    {
        if (A[i] <= B[j])
        {temp[k]= A[i];
        i++; k++;}

        else 
       {temp [k]= B[j];
        j++; 
        k++;}

    }
}

int main ()
{
    int m,n;// take input of integers
    scanf ("%d %d", &m, &n);

    int A[m], B[n];

    for (int l =0; l<m; l++)
    { scanf("%d " , &A[l]) ;}

    for (int p =0; p<n; p++)
    { scanf("%d " , &B[p]) ;}

    int t; // scan input target element
    scanf("%d" , &t);

    int new = m+n;
    int temp[new];// define new array
   

    for( int i=0; i<m ; i++)
    { A[i] == temp [i];    }
    for( int j=0; j<n ; j++)
    { B[j] == temp [m+j];    }

    mergesort( A, B, m,  n , temp);
       
    int flag = 0;
    for (int g=0; g< new ;g++)
    { if (temp[g]==t)
           { printf( "%d ", g );
             flag = 1;
           }
    }
    
    if (flag ==0)
    {printf ("-1");}
}