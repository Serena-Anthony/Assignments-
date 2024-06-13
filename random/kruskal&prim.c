#include<stdio.h>
#include<stdlib.h>
#define MAX 1050
#define MAXER 10005
struct graph {
    int vtotal ;
    int adj[MAX][MAX];
};

struct graph *creategraph(int n){
    struct graph* create = (struct graph*)malloc(sizeof(struct graph));
    create -> vtotal = n ;
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++){
                create -> adj[i][j] = 0 ;
        }
    }
    return create ;
}

struct sortarr{
    int u ,v , we ;
};

void makeset(int par[], int rank[], int n){
    for(int i = 0 ; i < n ; i++){
        par[i]= i ;
        rank[i]= 0 ;
    }
}

int findparent(int par[], int comp){
    if(par[comp]== comp){
        return comp ;
    }
    return par[comp]= findparent(par , par[comp]);
}

void unionofthem(int par[], int rank[], int u , int v){
    u = findparent(par , u);
    v = findparent(par , v);
    if(rank[u]< rank[v]){
        par[u]= v ;
    }
    else if(rank[u]> rank[v]){
        par[v]= u ;
    }
    else{
        par[v]= u ;
        rank[u] = rank[u] + 1;
    }
}

void swap(struct sortarr *a , struct sortarr *b){
    struct sortarr* c = (struct sortarr*)malloc(sizeof(struct sortarr)) ;
    c -> we = a -> we;
    c -> u = a -> u ;
    c -> v = a -> v ;

    a -> we = b -> we;
    a -> u = b -> u ; 
    a -> v = b -> v ;

    b -> we = c -> we ;
    b -> u = c -> u ;
    b -> v = c -> v ;
}

int partition(struct sortarr *S[], int low , int high){
    int pivot = S[high]-> we ;
    int i = (low - 1);
    for(int j = low ; j < high ; j++){
        if(S[j]-> we <= pivot){
            i++;
            swap(S[i], S[j]);
        }
    }
    swap(S[i+1], S[high]);
    return (i+1);
}

void quicksort(struct sortarr *S[], int low , int high){
    if(low < high){
        int pi = partition(S , low , high);
    quicksort(S , low , pi-1 );
    quicksort(S , pi + 1 , high);
    }
}

void kruskal(struct sortarr *S[], int n , int count){
    quicksort(S , 0 , count-1);
    int par[n];
    int rank[n];
    makeset(par , rank , n);
    int mincost = 0 ;
   // printf("Following are the edges in the constructed MST\n");
    for(int i = 0 ; i < n ; i++){
        int u = findparent(par , S[i]-> u);
        int v = findparent(par , S[i]-> v);
        int weight = S[i]-> we ;
        if(weight != 0 ){
        if(u != v){
            unionofthem(par , rank , u , v);
            mincost = mincost + weight ;
            //printf("%d %d %d\n", S[i]-> u , S[i]-> v , weight);
        }
        }
    }
    printf("%d\n", mincost);
}
int minkey(int visited[], int key[],int n){
    int min = MAXER ;
    int i , mindex ;
    for(i = 0 ; i < n ; i++){
        if(visited[i]==0 && key[i]< min){
            min = key[i];
            mindex = i ;
        }
    }
    return mindex ;
}

void prim(struct graph *graph, int n ){
    int i , j , mincost = 0 ;
    int k ;
    int key[n];
    int visited[n];
    for(i =0 ; i < n ; i++){
        key[i]= MAXER;
        visited[i]= 0 ;
    }
    key[0]= 0 ;

    int par[n];
    par[0]= -1;
    for(i = 0 ; i < n-1 ; i++){
        int u = minkey(visited, key , n);
        visited[u]= 1 ;
        mincost = mincost + key[u];
        for(j = 0 ; j < n ; j++){
            if(graph -> adj[u][j] && visited[j]== 0 && graph -> adj[u][j] < key[j]){
                key[j]= graph -> adj[u][j];
                par[j]= u ;
            }
        }
    }
    printf("%d\n", mincost);
}

int main(){
    char Q ;
    scanf("%c",&Q);
    char ch ;
    int n , i , j ;
    int fir , sec ;
    scanf("%d",&n);
    struct graph *create = creategraph(n);
    for(i = 0 ; i < n ; i++){
        scanf("%d%c",&fir , &ch);
        while(ch != '\n'){
            scanf("%d%c",&sec ,&ch);
            create -> adj[fir][sec] = MAXER;
        }
    }
    int we ;
    for(i = 0 ; i < n ; i++){
        scanf("%d%c",&fir , &ch);
        while(ch != '\n'){
            scanf("%d%c",&we ,&ch);
            for(j = 0 ; j < n ; j++){
                if(create -> adj[fir][j]==MAXER){
                    create -> adj[fir][j]= we ;
                    break ;
                }
            }
        }
    }
    // for(i = 0 ; i < n ; i++){
    //     for(j = 0 ; j < n ; j++){
    //         printf("%d ", create -> adj[i][j]);
    //     }
    //     printf("\n");
    // }
    int N = (n*(n-1))/2 ;
    
    struct sortarr *sortedarr[N];
    //printf("%d\n",N);
  
    int count = 0 ;
    for(i = 0 ; i < n ; i++){
        for(j = i + 1 ; j < n ; j++){
            if(create -> adj[i][j]!= 0){
            //printf("%di %dj ",i ,j );
            sortedarr[count]= (struct sortarr*)malloc(sizeof(struct sortarr));
            sortedarr[count] -> u = i ;
            sortedarr[count] -> v = j ;
            sortedarr[count] -> we = (create -> adj[i][j]);
            //printf("%dcount\n",count);
            count++;
            }
        }
    }
    // printf("%d\n",count);
    
    // quicksort(sortedarr, 0 , count-1);
    
    // for(i = 0 ; i < count ; i++){
    //     printf("%d %d %d\n", sortedarr[i] -> we , sortedarr[i]-> u , sortedarr[i]-> v);
    // }
    if(Q == 'a'){
    kruskal(sortedarr, n + 1, count);
    }

    if(Q == 'b'){
        prim(create,n+1);
    }

}