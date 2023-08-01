#include <stdio.h>

void swap(float *a, float *b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify (float A[], int n, int i)
{   
    int largest =i;
    int left = 2*i+1;
    int right = 2*i+ 2;

    if (left < n && A[left] > A[largest])
       { largest = left;}
    if (right < n && A[right] > A[largest])
        { largest = right;  }

    if (largest != i) 
    {
    swap( &A[i], &A[largest]); 
    max_heapify(A, n, largest);
    }
}   
 
void build_max_heap(float A[], int n)
{
 for (int i = n/2 -1; i>=0; i--)
    {  max_heapify(A,n,i);}
}

void heapsort(float A[], int n)
{
    build_max_heap(A,n);
    
    for(int i=n-1; i>=0;i--)
    {
        swap(&A[0], &A[i]);
        max_heapify(A,i,0);
    }
}

int main()
{
    int n,k;
    scanf ("%d %d", &n, &k);

    float A[n];
    for (int i = 0; i < n; i++)
    { scanf("%f", &A[i]);    } 

    int m= n/k;
    float temp[m][k];

    int h=0;
        for(int j=0; j<m; j++ )
        {
            for(int i=0; i<k; i++)
            {
            temp[j][i]= A[h];
            h++;
            }
            heapsort(temp[j], k);
        }

       for (int j=0; j<m; j++)
       { printf("%0.2f ", temp[j][k-1]); }
}
