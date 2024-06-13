void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
int partition(int A[],int low,int high)
{
    int x=A[high];
    int i=low-1;
    for(int j=low;j<high;j++)
    {
        while(A[j]<=x)
        {
            i++;
            swap(&A[i],&A[j]);
        }
    }
    swap(&A[i+1],&A[high]);
}
void quicksort(int A[],int low,int high)
{
    int q=partition(A,low,high);
    quicksort(A,low,q-1);
    quicksort(A,q+1,high);
}

