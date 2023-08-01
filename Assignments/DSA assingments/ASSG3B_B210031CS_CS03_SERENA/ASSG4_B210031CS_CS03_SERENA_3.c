// DFS algorithm in C
#include <stdio.h>
#include <stdlib.h>

struct node 
{
  int vertex;
  struct node* next;
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

struct graph* creategraph(int vertices)
{
    struct graph * g = malloc(sizeof(struct graph));
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

void printGraph(struct graph* g) 
{
  int v;
  for (v = 0; v < g->numofvert; v++) 
  {
    struct node* temp = g->adjlist[v];
   // printf("\n Adjacency list of vertex %d\n ", v);
    while (temp && g->visits[v]== 1) 
    {
      printf("%d ", temp->vertex);
      temp = temp->next;
    }
    //printf("\n");
  }
}

void dfs(struct graph* G, int vertex)
{
  printf("%d ",vertex);
    struct node* adjlist = G->adjlist[vertex];
    struct node* temp = adjlist;

    G->visits[vertex] =1;
    
    while(temp!=NULL)
    {
        int connctvertex = temp->vertex;
        // printf("%d ", connctvertex);
        if(G->visits[connctvertex]== 0)
        {
            dfs(G, connctvertex);
        }
        temp= temp->next;
    }
   // printGraph(G);
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
  
    dfs(g, 0);
    return 0;
}