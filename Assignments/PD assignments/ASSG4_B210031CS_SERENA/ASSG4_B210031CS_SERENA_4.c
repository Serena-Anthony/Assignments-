#include <stdio.h>

void printarray(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {printf("%d ", A[i]);    } 
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

int insert_process(int A[],int B, int length)
{
    A[length]=B;
    length++;
    if(length!=1)
    {
        build_max_heap(A,length);
    }
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
        A[length-1]=temp;
        length--;
        for(int i=length/2-1;i>=0;i--)
        {
            max_heapify(A,length,0);
        }
        return temp;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int A[n];
    int freq[n];
    int f[1000][2];
    int p=0;
    
    for(int j=0; j<n; j++)
    {
        scanf("%d", &A[j]);
        freq[j]= -1;
    }

    int k;
    scanf("%d", &k);
    
    int temp=0;
    
    for(int i=0; i<n; i++)
    {
        int count =1;
        for(int j=i+1; j<n; j++)
        {
            if (A[i]== A[j])
            {
                count ++;
                freq[j]=0;
            }
            
        }
        if (freq[i] != 0)
        {
            temp++;
            freq[i]= count;
            f[p][0]=A[i];
            f[p][1]=count;
            p++;
        }
    }
    
    
    int B[temp];
    int j;
    for( j=0; j<temp; j++)
    {
        B[j]= f[j][1];
    }

    int C[temp];
    for (int j=0; j<temp; j++)
    {
     insert_process(C,B[j],j);
    }

    int t=temp;
    for(int i=0; i<k; i++)
    {
        int w = extract_next_process (C,t);
        t--;
        for( int j =0; j<temp; j++)
        {
            if(f[j][1]==w)
            {
                f[j][1]=-1;
                printf("%d ",f[j][0]);
                break;
            }
        }
    }
}

