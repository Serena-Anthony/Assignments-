#include <stdio.h>

void MAX_HEAPIFY(int A[],int i,int n)
{
    int l,r,largest=i;
    l=2*i+1;
    r=2*i+2;
    if (l<n && A[l]>A[i])
    {
        largest=l;
    }
    if (r<n && A[r]>A[largest])
    {
        largest=r;
    }
    if (largest!=i)
    {
        int temp=A[i];
        A[i]=A[largest];
        A[largest]=temp;
        // swap A[i] and A[largest]
        
        MAX_HEAPIFY(A,largest,n);
    }
}

void BUILD_MAX_HEAP(int A[],int n)
{
    for(int i=n/2-1;i>=0;i--)
    {
        MAX_HEAPIFY(A,i,n);
    }
}

void HEAPSORT(int A[],int n)
{
    BUILD_MAX_HEAP(A,n);
    for (int i=n-1;i>=0;i--)
    {
        int temp=A[0];
        A[0]=A[i];
        A[i]=temp;

        // swap(A[0], A[i]);
        MAX_HEAPIFY(A,0,i);
    }
}