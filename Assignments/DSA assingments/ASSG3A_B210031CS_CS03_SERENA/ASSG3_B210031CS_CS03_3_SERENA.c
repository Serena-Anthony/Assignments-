#include<stdio.h>

void printarray(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {printf("%d ", A[i]);    } 

    printf("\n");
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify (int A[], int n, int i)
{   
    
    int largest =i;
    int left = 2*i+1;
    int right = 2*i+ 2;

    if (left < n && A[left] > A[largest])
    {
        largest = left;
    }

    if (right < n && A[right] > A[largest])
    {
        largest = right;
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

int extract_next_process(int A[], int length)
{
 if(length==0)
    {
        return -1;
    }
    else
    {
        int temp=A[0];
        A[0]=A[length-1];
        length--;
        for(int i=length/2-1;i>=0;i--)
        {
            build_max_heap(A,length);
        }
        return temp;
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    for(int i =0 ; i<t ; i++)
    {
        int n;
        scanf("%d", &n);
        int A[n];
        for(int i =0; i<n; i++)
        {
            scanf("%d", &A[i]);
        }

        int k;
        scanf("%d", &k);
        
        build_max_heap(A,n);
        //printarray(A,n);
       // printf("\n");

        int B[k];
        for(int i =0; i<k ;i++)
        {
            B[i]= '\0';
        }
        
        for(int i =0; i<k ;i++)
        {
            B[i]= extract_next_process(A,n);
        }
       
       printarray(B, k);
    }
}

