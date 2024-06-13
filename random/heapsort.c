#include <stdio.h>

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

void max_heapify(int A[],int i,int n)
{
    int l=2*i+1;
    int r=2*i+2;
    int largest=i;

    if(l<n && A[l]>A[i])
    {
        largest=l;
    }

    if(r<n && A[r]>A[largest])
    {
        largest=r;
    }
    
    if(largest!=i)
    {
        swap(&A[i],&A[largest]);
        max_heapify(A,largest,n);
    }
}

void build_max_heap(int A[],int n)
{
    for(int i=n/2-1;i>=0;i--)
    {
        max_heapify(A,i,n);
    }
}

void heapsort(int A[],int n)
{
    build_max_heap(A,n);
    for(int i=n-1;i>=0;i--)
    {
        int temp=A[0];
        A[0]=A[i];
        A[i]=temp;
        max_heapify(A,0,i);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int A[n];
    for(int i=0;i<n;i++)
    {
        scanf("%d",&A[i]);
    }
    heapsort(A,n);
    for(int j=0;j<n;j++)
    {
        printf("%d ",A[j]);
    }
}