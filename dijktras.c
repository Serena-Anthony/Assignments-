#include<stdio.h>
#include<stdlib.h>
#define MAX 1050
#define MAXER 10005
struct graph {
    int vtotal ;
    int adj[MAX][MAX];
};
struct graph *creategraph(int n){
    struct graph *create = (struct graph*)malloc(sizeof(struct graph));
    create -> vtotal = n ;
    for(int i = 0 ; i < n ; i++) {
        for(int j = 0 ; j < n ; j++){
                create -> adj[i][j] = 0 ;
        }
    }
    return create ;
}

int minkey(int visited[], int key[],int n){
    int min = MAXER ;
    int i , mindex ;
    for(i = 0 ; i < n ; i++){
        if(visited[i]==0 && key[i] < min ){
            min = key[i];
            mindex = i ;
        }
    }
    return mindex ;
}

void apsp_dijkstra(struct graph *graph, int src , int n){
    int i , j , mincost = 0 ;
    int k ;
    int key[n];
    int visited[n];
    for(i =0 ; i < n ; i++){
        key[i]= MAXER;
        visited[i]= 0 ;
    }
    key[src]= 0 ;
    //printf("%d ",mincost);
    for(i = 0 ; i < n-1 ; i++){
        int u = minkey(visited, key , n);
        visited[u]= 1 ;
        mincost = mincost + key[u];
        //printf("%d ",key[u]);
        for(j = 0 ; j < n ; j++){
            if( visited[j]== 0 && graph -> adj[u][j] && key[u] != MAXER && key[u] + graph -> adj[u][j] < key[j]){
                key[j] = key[u] + graph -> adj[u][j];
                //par[j]= u ;
            }
        }
    }
    for(i = 0 ; i < n ; i++){
        if(key[i]==MAXER){
            printf("INF ");
        }
        else{
        printf("%d ", key[i]);
        }
    }
    printf("\n");
    //return key[n-1];
    //printf("%d\n", mincost);
}

void sssp_dijkstra(struct graph *graph,int n , int src , int desc){
    int i , j , mincost = 0 ;
    int k ;
    int key[n];
    int visited[n];
    for(i =0 ; i < n ; i++){
        key[i]= MAXER;
        visited[i]= 0 ;
    }
    key[src]= 0 ;
    //printf("%d ",mincost);
    for(i = 0 ; i < n-1 ; i++){
        int u = minkey(visited, key , n);
        visited[u]= 1 ;
        mincost = mincost + key[u];
        //printf("%d ",key[u]);
        for(j = 0 ; j < n ; j++){
            if( visited[j]== 0 && graph -> adj[u][j] && key[u] != MAXER && key[u] + graph -> adj[u][j] < key[j]){
                key[j] = key[u] + graph -> adj[u][j];
                //par[j]= u ;
            }
        }
    }
    // for(i = 0 ; i < n ; i++){
    //     printf("%d ", key[i]);
    // }
    if(key[desc-1]== MAXER){
        printf("UNREACHABLE\n");
    }
    else{
    printf("%d\n", key[desc-1]);
    }
}


int main(){
    char ch ;
    int n , i , j ;
    int fir , sec ;
    scanf("%d",&n);
    struct graph *create = creategraph(n);
    for(i = 0 ; i < n ; i++){
        scanf("%d%c",&fir , &ch);
        while(ch != '\n'){
            scanf("%d%c",&sec ,&ch);
            create -> adj[fir][sec] = MAXER ;
        }
    }
    // for(i = 0 ; i < n ; i++){
    //     for(j = 0 ; j < n ; j++){
    //         printf("%d ", create -> adj[i][j]);
    //     }
    //     printf("\n");
    // }
    int we ;
    for(i = 0 ; i < n ; i++){
        scanf("%d%c",&fir , &ch);
        while(ch != '\n'){
            scanf("%d%c",&we ,&ch);
            j = 0 ;
            for(j = 0 ; j < n ; j++){
                if(create -> adj[fir][j] == MAXER){
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
    while(1){
    char mystring[5];
    scanf("%s",mystring);
    //scanf("%c%c%c%c",&mystring[0],&mystring[1],&mystring[2],&mystring[3]);
    //printf("%s\n",mystring);
    int src ;
    int tar ;
    if(mystring[0] == 'a' && mystring[1] == 'p' && mystring[2] == 's' && mystring[3] == 'p' && mystring[4] == '\0' ){
        scanf("%d",&src);
        apsp_dijkstra(create, src , n);
    }
    else if(mystring[0] == 's' && mystring[1] == 's' && mystring[2] == 's' && mystring[3] == 'p'&& mystring[4] == '\0' ){
        scanf("%d %d", &src ,&tar);
        //if(src<tar){
;
            sssp_dijkstra(create , n ,src , tar+1);
            
        //printf("%d\n",cost);
        //}
        // else{
        //     int value = sssp_dijkstra(create , tar , src+1);
        // printf("%d\n",value);
        // }
    }
    else if(mystring[0] == 's' && mystring[1] == 't' && mystring[2] == 'o' && mystring[3] == 'p' && mystring[4] == '\0'){
        break;
    }
    }
    // apsp_dijkstra(create, 0, n);
    // printf("\n");
    // int value = sssp_dijkstra(create , 0 , 6+1);
    // printf("%d\n",value);
}



// void sssp_dijkstra(struct graph *graph, int n, int src , int desc){
//  int i , j , mincost = 0 ;
//     int k ;
//     int key[n];
//     int visited[n];
//     int par[n];
//     for(i =0 ; i < n ; i++){
//         par[src]= -1;
//         key[i]= MAXER;
//         visited[i]= 0 ;
//     }
//     key[src]= 0 ;
//     //printf("%d ",mincost);
//     for(i = 0 ; i < n-1 ; i++){
//         int u = minkey(visited, key , n);
//         visited[u]= 1 ;
//         mincost = mincost + key[u];
//         //printf("%d ",key[u]);
//         for(j = 0 ; j < n ; j++){
//             if( visited[j]== 0 && graph -> adj[u][j]>=0 && key[u] != MAXER && key[u] + graph -> adj[u][j] < key[j]){
//                 key[j] = key[u] + graph -> adj[u][j];
//                 par[j]= u ;
//             }
//         }
//     }


//     if(key[desc]==MAXER){
//         printf("UNREACHABLE\n");
//         return;
//     }
//     printf("%d\n", key[desc]);
//     // for(i = 0 ; i < n ; i++){
//     //     printf("%d ", key[i]);
//     // }
//     //return mincost;
//     //return key[n-1];
//     //printf("%d\n", mincost);
// }