#include <stdio.h>
int main()
{
    int n,b[100];
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&b[i]);
    }
    for(int j=0;j<n-1;j++)
    {
        int s=b[j],pos=j;
        for(int i=j+1;i<n;i++)
        {
            if(b[i]<s)
            {
                s=b[i];
                pos=i;
            }
        }
        b[pos]=b[j];
        b[j]=s;
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",b[i]);
    }
}
