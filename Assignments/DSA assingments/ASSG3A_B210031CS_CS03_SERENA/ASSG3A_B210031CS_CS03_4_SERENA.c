#include<stdio.h>

struct heap
{
    int a[10000];
    int len;
};

void min_heapify(struct heap *Q, int i)
{
    int smallest = i;
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;
    if (left < Q->len && Q->a[left] < Q->a[smallest])
    {
        smallest = left;
    }
    if (right < Q->len && Q->a[right] < Q->a[smallest])
    {
        smallest = right;
    }
    if (smallest != i)
    {
        int temp = Q->a[smallest];
        Q->a[smallest] = Q->a[i];
        Q->a[i] = temp;
        min_heapify(Q, smallest);
    }
}

int extract_min(struct heap *Q)
{
    int min = Q->a[0];
    Q->a[0] = Q->a[Q-> len-1];
    Q->len--;
    min_heapify(Q, 0);
//    printf("EXTRACTED\n");
    return min;
}

void insert(struct heap* Q, int k)
{
    Q->a[Q->len] = k;
    int ptr = Q->len;
    Q->len++;

//    printf("INSERTED \n");
    while (ptr > 0 && Q->a[(ptr - 1) / 2] > Q->a[ptr])
    {
        int temp = Q->a[ptr];
        Q->a[ptr] = Q->a[(ptr - 1) / 2];
        Q->a[(ptr - 1) / 2] = temp;
        ptr = (ptr - 1) / 2;
    }
}

int cost(struct heap *Q)
{
    int cost =0;
    //int ptr= Q->len;
    
    while(Q->len != 1)
    {
    int min = extract_min(Q);
    int min2 = extract_min(Q);
    int temp = min + min2;
   
    cost = cost + temp;
     insert(Q,temp);
    }
    return cost;
}

int main()
{
    struct heap * Q, q;
    Q= &q;
    
    int n;
    scanf("%d", &n);

    for(int i =0 ; i< 10000; i++)
    {
        Q->a[i] = '\0';
    }

    Q->len =0;
    for(int i =0; i<n;i++)
    {
        int k;
        scanf("%d",&k);
        insert(Q,k);
    }

    //  for(int i =0; i<n;i++)
    // {
    //     printf("%d ", Q->a[i]);
    //    // insert(Q,Q->a[i]);
    // }

    int temp = cost(Q);
    printf("%d\n", temp);
}