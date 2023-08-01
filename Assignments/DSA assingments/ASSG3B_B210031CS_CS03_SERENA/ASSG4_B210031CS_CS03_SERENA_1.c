#include<stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int a[1000][1000];
    for(int i = 0 ; i<n; i++)
    {
        for(int j =0; j<n;j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    for(int i = 0; i<n ; i++)
    {
        printf("%d ", i);
        for(int j=0; j<n ; j++)
        {
        if(a[i][j] == 1)
        {
            printf("%d ", j);
        }
        }
        printf("\n");
    }
}