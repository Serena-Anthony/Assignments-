#include <stdio.h>
void Merge(int A[],int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int L[52],R[52];
    for(int i=0;i<n1;i++)
    {
        L[i]=A[p+i];
    }
    for(int j=0;j<n2;j++)
    {
        R[j]=A[q+j+1];
    }
    int i=0,j=0,k=p;
    while(i<n1 && j<n2)
    {
        if(L[i]>=R[j])
        {
            A[k]=R[j];
            j++;
        }
        else
        {
            A[k]=L[i];
            i++;
        }
        k++;
    }
    while(i<n1)
    {
        A[k]=L[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        A[k]=R[j];
        j++;
        k++;
    }
}
void Mergesort(int A[],int p,int r)
{
    if(r>p)
    {
        int q=(r+p)/2;
        Mergesort(A,p,q);
        Mergesort(A,q+1,r);
        Merge(A,p,q,r);
    }
}
int main()
{
    int n,A[50];
    scanf("%d",&n);
    int p=0,r=n-1;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&A[i]);
    }
    Mergesort(A,p,r);
    for(int i=0;i<n;i++)
    {
        printf("%d ",A[i]);
    }

}
