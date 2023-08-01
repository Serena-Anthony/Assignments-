#include<stdio.h>

void merge(char A,int p,int q,int r)
{   int i,j,k;
    int n1= q-p+1;
    int n2= r-q;
    int L[n1][1000], R[n2][1000];
   
    for (i=0; i< n1;i++)
    { 
        for (k=0; A[p+i-1][k] != '\0'  ; k++)
           {
             L[i][k]= A[p+i-1][k] ;
           }
            
    }

    for ( j=0; j< n2;j++)
    {
        for (k=0;A[q+j][k] != '\0' ; k++)
        {
             R[j][k]= A[q+j][k] ;
        }
    }

    L[n1+1][1000]= 100000;
    R[n2+1][1000]= 100000;

        for ( g=p ; g<r ; g++)
        {   
            int i=0,j=0;
            if (L[i]<= R[j])
            {   
                for()
                A[g]= L[i];
                i++;         
            }

            else 
            {
                A[g]= R[j];
                j++;
            }
        }

        while (i< n1)
        { 
            A[g] = L[i];
            i++;
            g++;
        }

        while (j < n2)
        {
            A[g] = R[j];
            j++;
            g++;
        }

}

void mergesort (char A, int p, int r)
{
    if(p<r)
    {  
        int q = (p+r)/2;
        mergesort (A,p,q);
        mergesort (A,q+1,r);
        merge (A,p,q,r);
    }    
}


int main ()
{
    int n ;
    scanf("%d", &n);
    getchar();
    char A[n][1000];
    
    for (int i=0; i<n; i++)
    {
        scanf("%[^\n]s",A[i]) ;
        getchar();
    }

    for (int i=0;i<n ; i++)
    {
        for (int j=0;A[i][j]!='\0'; j++)
        {
            printf("%c",A[i][j]) ;
        }
        printf("\n");
    }

}


