#include <stdio.h>
int count=0;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printarray(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {printf("%d ", A[i]);    } 
}
   
void max_heapify (int A[], int n, int i)
{   
    
    int largest =i;
    int left = 2*i+1;
    int right = 2*i+ 2;

    if (left < n && A[left] > A[largest])
    {
        count++;
        largest = left;
    }
    else if(left<n)
    {
        count++;
    }
    if (right < n && A[right] > A[largest])
    {
        count++;
        largest = right;
    }
    else if(right<n)
    {
        count++;
    }
    if (largest != i)
    {
        swap(&A[i], &A[largest]);
        max_heapify(A, n, largest);
    }
}   
 
void build_max_heap(int A[], int n)
{
 for (int i = n/2 -1; i>=0; i--)
    {  max_heapify(A,n,i);}
}

void heapsort(int A[], int n)
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
    int n;
    scanf("%d", &n);
    int A[n];
    for(int j=0; j<n; j++)
    {
        scanf("%d", &A[j]);
    }

    heapsort(A,n);

    printarray(A,n);
    printf("\n%d",count);
}