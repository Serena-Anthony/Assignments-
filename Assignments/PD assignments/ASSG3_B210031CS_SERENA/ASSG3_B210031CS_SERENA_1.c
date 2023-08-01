#include<stdio.h>

    void insertionsort (float A[], int n)
    {
        int i,j,k;
        float key;
        for (i=0;i<n;i++)
        {
            key = A[i];// define key
            j=i-1;

            while (j>=0 && A[j]>key)
            {
                A[j+1]= A[j];
                j=j-1;
            }

            A[j+1]= key;
        }
    }
    
    
    int findindex (float A[], float B[], int n)
    {   
        for (int i=0; i<n; i++)
        {
              for (int k=0;k<n ;k++)
            {
               if (B[i] == A[k])
               printf ("%d ", k);
            }
        } 
      
    }

 
int main()
{
    int n;
    scanf("%d",&n);
    float A[n];
    float B[n];
    for (int i=0; i<n; i++)
    {
        scanf("%f", &A[i]);
        B[i]= A[i];
    }

    insertionsort(A, n);
    
    findindex(A, B, n);

    return 0;
}