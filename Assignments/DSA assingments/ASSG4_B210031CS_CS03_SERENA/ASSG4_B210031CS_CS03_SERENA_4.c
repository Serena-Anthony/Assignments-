#include <stdio.h>
#include <stdlib.h>

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

struct node 
{
  int vertex;
  struct node* pointer;
};

struct edge
{
    int svert;
    int evert;
    int weight;
};

struct node* makeset(int x)
{
    struct node* temp = (struct node*)malloc (sizeof(struct node));
    temp->vertex = x;
    temp->pointer = temp;
   // printf("created\n");
    return temp;
}

struct edge* makedge(int x, int y, int w)
{
    struct edge* temp = (struct edge*)malloc (sizeof(struct edge));
    temp->svert = x;
    temp->evert = y;
    temp->weight = w;
   // printf("created\n");
    return temp;
}

struct node* findset(struct node* x)
{
    if(x!= NULL)
    {
        if(x->pointer == x)
        {
            return x;
        }
        else
        {
            return findset(x->pointer);
        }
    }
}
struct node* link (struct node*a, struct node*b)
{
    b->pointer= a;
    return a;
}

struct node* union_xy(struct node*x, struct node*y)
{
    return link(findset(x), findset(y));
}

void sort (int n, struct edge* arr[])
{
   // printf("entered sorting\n");
    int i,j;
    struct edge* key;

    for( i =1; i<n; i++)
    {
        key = arr[i];
      //  printf("key is given value\n");
        j = i -1;

        while(j>=0 && arr[j]->weight> key->weight)
        {
          //  printf("entered while for sort\n");
            arr[j+1]= arr[j];
            j = j-1;
        }
       // printf("exited while in sort\n");
        arr[j+1]= key;
       // printf("finishing forloop\n");
    }
}

void kruskal(int n, int len,struct node*array[],struct edge *arr[])
{
    // n = no of vertices, len = no of edges
    int sum =0;
    int i;

    for(i =0; i<len; i++)
    {   
       // printf("entering forloop - kruskal\n");
        int vertex1 = arr[i]->svert;
        int vertex2 = arr[i]->evert;

        struct node *temp1 = array[vertex1];
        struct node *temp2 = array[vertex2];

        if(findset(temp1)!= findset(temp2))
        {
            union_xy(temp1, temp2);
            sum = sum + arr[i]->weight;
        }
    }    
    printf("%d\n", sum);
}

//prims functions
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
    char ch;
    scanf("%c", &ch);
    if(ch =='a')
    {
            int n;
        scanf("%d", &n);
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

    // printf("enter the weights\n");

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
            // createweights(i,j, k);
                j++;
                if(c=='\n')
                {
                    break;
                }
            }
        }
    // printarray(n,a);

        struct edge*arr[100];
        int l =0;
        for(int i=0; i<n;i++)
        {
        // printf("entered for\n");
            int j =i+1;
            while(j<n)
            {
            // printf("entered while\n");
                if(a[i][j]!= 0)
                { 
                    int w = a[i][j];
                    arr[l] = makedge(i,j,w);
                    l++;
                }
                j++;
            }
        }

        len = l;
    
        //  for (int  i = 0; i < len; i++)
        // {
        //     if (arr[i]== NULL)
        //     {
        //         printf("YES\n");
        //     }
        //     else
        //     {
        //     printf("%d %d %d", arr[i]->svert,arr[i]->evert, arr[i]->weight );
        //     printf("\n");
        //     }
        // }

        sort(len,arr);

        //  for (int  i = 0; i < len; i++)
        // {
        //     if (arr[i]== NULL)
        //     {
        //         printf("YES\n");
        //     }
        //     else
        //     {
        //     printf("%d %d %d", arr[i]->svert,arr[i]->evert, arr[i]->weight );
        //     printf("\n");
        //     }
        // }

        struct node* array[100];
        for(int i =0; i<n ; i++)
        {
            array[i]= makeset(i);
        }

        kruskal(n,len,array,arr);
    }

    if(ch == 'b')
    {
        int n;
        scanf("%d", &n);
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

        // for(int i =0; i<n; i++)
        // {
        //     for(int j =0; j<2; j++)
        //     {
        //         printf("%d ", arr[i][j]);
        //     }
        //     printf("\n");
        // }
        
        //set starting as 0
        int l=n;
        arr[0][1]=0;
        int sum = 0;
        int j =0;
        while (j<n)
        {
            int min = arr[0][1];
            int vertex=arr[0][0];
            visited[vertex]=-1000;
            extractmin(l,arr);
            l--;
            for(int i=0; i<n; i++)
            {
                int bleh = a[vertex][i];
                if(bleh!= 0 && visited[i]!= -1000)
                {
                    for(int j=0;j<l;j++)
                    {
                        if(arr[j][0]==i && bleh<arr[j][1])
                        {
                            decrease_key(arr,j,bleh);
                        }
                    }
                }
            }

        // printf("min:%d vertex:%d j:%d \n");
            j++;
            sum = sum +min;
        }

        
        printf("%d", sum);
    }
    
}

/*
5
0 1 3
1 0 2 3 4
2 1 4
3 0 1 4
4 1 2 3
0 2 6
1 2 3 8 5
2 3 7
3 6 8 9
4 5 7 9

sum = 16

*/