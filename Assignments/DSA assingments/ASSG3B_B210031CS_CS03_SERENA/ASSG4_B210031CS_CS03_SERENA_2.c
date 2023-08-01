/*
create a queue Q 
mark v as visited and put v into Q 
while Q is non-empty 
    remove the head u of Q 
    mark and enqueue all (unvisited) neighbours of u
*/

// BREADTH FIRST SEARCH

/*
if colour :  white = 0;  grey = 1; black = 2
*/

#include<stdio.h>
#include<stdlib.h>

struct queue
{
   int head;
   int tail;
   int size;
   int arr[1001];
};

struct node
{
    int vertex;
    struct node*next;
};

struct graph
{
    int numofvert;
    struct node** adjlist;
    int *visits;
};

struct node* createNode(int v) 
{
  struct node* new = malloc(sizeof(struct node));
  new->vertex = v;
  new->next = NULL;
  return new;
}

struct queue* createqueue()
{
  struct queue* q = malloc(sizeof(struct queue));
  q->head = 0;
  q->tail = 0;
  return q;
}

struct graph* creategraph(int vertices)
{
    struct graph * g = (struct graph*)malloc(sizeof(struct graph));
    g->numofvert = vertices;
    g->adjlist = malloc(vertices*sizeof(struct node*));
    g->visits = malloc(vertices*sizeof(int));

    for(int i =0; i<vertices; i++)
    {
        g->adjlist[i] = NULL;
        g->visits[i]= 0;
    }
    return g;
}

void addedges (struct graph* g, int u, int v)
{
    struct node *temp=createNode(v);
    if(g->adjlist[u]==NULL)
    {
        g->adjlist[u]=temp;
    }
    else
    {
        struct node *t=g->adjlist[u];
        while(t->next)
        {
            t=t->next;
        }
        t->next=temp;
    }
}

int queueisemtpy(struct queue*ptr)
{
    if(ptr->head == ptr->tail)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int queueisfull(struct queue* ptr)
{
     if((ptr->head == ptr->tail+1) || (ptr->head == 0 && ptr->tail == 9999))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(struct queue*ptr, int k)
{
    if(queueisfull(ptr)!= 1)
    {
        ptr->arr[ptr->tail] = k;
        if(ptr->tail == 9999)
        {
            ptr->tail = 0;
        }
        else
        {
            ptr->tail ++;
        }
    }
}

int dequeue(struct queue* ptr)
{
    if(queueisemtpy(ptr)!= 1)
    {
        int c = ptr->arr[ptr->head];
        if(ptr->head == ptr->size-1)
        {
            ptr->head = 0;
        }
        else
        {
            ptr->head++;
        }
    return c;
    }
}

void bfs(struct graph* G, int sv,int n)
{
    struct queue* Q = createqueue();

    G->visits[sv] = 1;
    enqueue(Q, sv);
    //printf("sv is %d ", sv);

    while(queueisemtpy(Q)!= 1)
    {
        int cv = dequeue(Q);

        struct node *temp = G->adjlist[cv];
        printf("%d ", cv);
        
        while(temp)
        {
            int adjvertex = temp->vertex;

            if(G->visits[adjvertex] == 0)
            {
                G->visits[adjvertex]= 1;
                enqueue(Q, adjvertex);
            }
            temp = temp->next;
        }
    }
}

int main()
{
    int n,k;
    char c;
    scanf("%d", &n);

    struct graph* g = creategraph(n);

    for(int i =0; i<n ;i++)
    {
        scanf("%d%c",&k,&c);
        while(1)
        {
            scanf("%d%c",&k,&c);
            addedges(g,i,k);
           // printf("i n k is %d %d\n", i, k);
            if(c=='\n')
            {
                break;
            }
        }
    }

    bfs(g, 0, n);

    return 0;

}


