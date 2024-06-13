#include <stdio.h>
int main()
{
    int n,b[100];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&b[i]);
    }
    for(int j=1;j<n;j++)
    {
        float temp=b[j];
        int i=j-1;
        while(b[i]>temp && i>=0)
        {
            b[i+1]=b[i];
            i--;
        }
        b[i+1]=temp;
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",b[i]);
    }
}

