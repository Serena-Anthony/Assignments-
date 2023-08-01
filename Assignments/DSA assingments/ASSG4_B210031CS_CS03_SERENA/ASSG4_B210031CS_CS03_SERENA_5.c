#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int printarray(int n, int a[100][100])
{
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int findmin(int n, int a[100][2])
{
    int min = 1000000;
    for(int i=0; i<n;i++)
    {
        int j =1;
        
            if(a[i][j]<min)
            {
                min = a[i][j];
            }
        
    }
    return min;
}

void minheapify(int A[][2],int i,int n)
{
   // printf("minheapifyentered\n");
    int l,r,largest=i;
    l=2*i+1;
    r=2*i+2;
    if (l<n && A[l][1]<A[i][1])
    {
        largest=l;
    }
    if (r<n && A[r][1]<A[largest][1])
    {
        largest=r;
    }
    if (largest!=i)
    {
        int temp=A[i][1];
        A[i][1]=A[largest][1];
        A[largest][1]=temp;

        temp=A[i][0];
        A[i][0]=A[largest][0];
        A[largest][0]=temp;
        
        minheapify(A,largest,n);
    }
  // printf("minheapify completed\n");
}

void extractmin(int n,int Q[][2])
{
   // printf("extract min entered\n");
    if(n==0)
    {
        return ;
    }
    else
    {
        Q[0][0]=Q[n-1][0];
        Q[0][1]=Q[n-1][1];
        n--;
        minheapify(Q,0,n);
     //     printf("extract min exited\n");
        return;
    }
}

void decrease_key(int arr[][2],int j,int bleh)
{
    //bleh is value to be updated
    // arr[j][1]->updated
   
   // printf("decreased \n");
    arr[j][1]= bleh;
    int p = (j-1)/2;

    while(p>=0 && arr[p][1]>arr[j][1])
    {
        int temp = arr[p][1];
        arr[p][1]= arr[j][1];
        arr[j][1]= temp;

        temp = arr[p][0];
        arr[p][0]= arr[j][0];
        arr[j][0]= temp;
        
        j = p;
        p = (j-1)/2;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int src, des,sv;
  //  printf("scan completed\n");
    int temp =0;
    int a[100][100] = {0};
    int k;
    char c;
    int len =0;
    for(int i =0; i<n; i++)
    {
        //makeset(i);
        scanf("%d%c",&k,&c);
        while(1)
        {
            scanf("%d%c",&k,&c);
            a[i][k] = -1;

            if(c=='\n')
            {
                break;
            }
        }
    }
   // printarray(n,a);

  //  printf("enter the weights\n");

    for(int i =0; i<n; i++)
    {
        int j=0;
        scanf("%d%c",&k,&c);
        while(1)
        {
            scanf("%d%c",&k,&c);

            while(a[i][j] != -1)
            {
                j++; 
            }
            a[i][j]= k;
            j++;
            if(c=='\n')
            {
                break;
            }
        }
    }
    //printarray(n,a);
    // got weight of arrays


    int arr[n][2]; // to have the distances put in 
    int visited[n] ; //array to store constructed mst
    int dist[n];

    for(int j =0; j<n; j++)
    {
        arr[j][0] = j;
        arr[j][1] = 1000;
    }

    while(1)
    {
        char str[5];
        scanf("%s", &str);
        
        if(strcmp(str,"apsp"))
        {
                int src; //source vertex
                scanf("%d", &src);
                        
                int l=n;
                decrease_key(arr,src,0);
                int sum = 0;
                int j =0;
                int min;
                while (j<n)
                {
                    min = arr[0][1];
                    int vertex=arr[0][0];
                    visited[vertex]=-1000;
                    printf("min is %d \n",min);
                    extractmin(l,arr);
                    l--;
                    for(int i=0; i<n; i++)
                    {
                        int bleh = a[vertex][i];
                        if(bleh!= 0 && visited[i]!= -1000)
                        {
                            for(int j=0;j<l;j++)
                            {
                                if(arr[j][0]==i && bleh+min<arr[j][1])
                                {
                                    decrease_key(arr,j,bleh+min);
                                }
                            }
                        }
                    }

                // printf("min:%d vertex:%d j:%d \n");
                    j++;
                   // sum = sum +min;
                }
                   // printf("%d", sum);
        }

        if(strcmp(str,"sssp"))
        {
            int src, des;
            scanf("%d %d", &src, &des);
            
                int l=n;
                decrease_key(arr,src,0);
                int sum = 0;
                int j =0;
                int min;
                while (j<n)
                {
                    min = arr[0][1];
                    int vertex=arr[0][0];
                    visited[vertex]=-1000;
                   // printf("%d ",min);
                   if(vertex == des)
                   {
                    break;
                   }
                    extractmin(l,arr);
                    l--;
                    for(int i=0; i<n; i++)
                    {
                        int bleh = a[vertex][i];
                        if(bleh!= 0 && visited[i]!= -1000)
                        {
                            for(int j=0;j<l;j++)
                            {
                                if(arr[j][0]==i && bleh+min<arr[j][1])
                                {
                                    decrease_key(arr,j,bleh+min);
                                }
                            }
                        }
                    }

                // printf("min:%d vertex:%d j:%d \n");
                    j++;
                   // sum = sum +min;
                }

                printf("%d\n", min);
        }

        if(strcmp(str,"stop"))
        {
            break;
        }
    }

/*
    int l=n;
    decrease_key(arr,src,0);
    int sum = 0;
    int j =0;
    while (j<n)
    {
        int min = arr[0][1];
        int vertex=arr[0][0];
        visited[vertex]=-1000;
        printf("%d ",min);
        extractmin(l,arr);
        l--;
        for(int i=0; i<n; i++)
        {
            int bleh = a[vertex][i];
            if(bleh!= 0 && visited[i]!= -1000)
            {
                for(int j=0;j<l;j++)
                {
                    if(arr[j][0]==i && bleh+min<arr[j][1])
                    {
                        decrease_key(arr,j,bleh+min);
                    }
                }
            }
        }

       // printf("min:%d vertex:%d j:%d \n");
        j++;
        sum = sum +min;
    }

    
    printf("%d", sum);
 */   
}