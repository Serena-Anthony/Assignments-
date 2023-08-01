#include<stdio.h>
#include<stdlib.h>
struct stack{
    char* array;
    int top;
    
};

void push(struct stack *S,char data){
    S->top=S->top+1;
    S->array[S->top]=data;
}

struct node{
    int key;
    int csum;
    struct node *left;
    struct node *right;
    struct node *p;

};
struct node *createnode(int key,int sum){
    struct node *new;
    new=(struct node *)malloc(sizeof(struct node));
    new->key=key; 
    new->csum=sum;    
    new->left=NULL;
    new->right=NULL;
    new->p=NULL;
    return new;
    
    }
int findindex(char *arr,int start,int end){
    if(start>=end)
        return -1;
    int ob=0;
    int cb=0;
    while((start<=end)){
        if(arr[start]=='(')
            ++ob;
        if(arr[start]==')')
        {
            ++cb;
            if(ob==cb)
                return start;
        }
        ++start;
    }
}
struct node* buildtree(struct node **ptr,char *arr,int start,int end,int sum){
    if(start>=end)
        return NULL;
    if(arr[start]=='('){
        start++;
        if(arr[start]==')')
            return NULL;
        int num=0;
        while(start<end&&arr[start]>='0'&&arr[start]<='9'){
            num=num*10+arr[start]-'0';
            start++;
        }
        sum=sum+num;
        struct node *root=createnode(num,sum);
        int index=-1;
        if(arr[start]=='(')
            index=findindex(arr,start,end);
        if(index!=-1){
            root->left=buildtree(ptr,arr,start,index,sum);
            root->right=buildtree(ptr,arr,index+1,end-1,sum);
        }
        if(root->left!=NULL){
            root->left->p=root;
            //root->left->csum=root->key+root->left->key;
        }
        if(root->right!=NULL){
            root->right->p=root;
            //root->right->csum=root->key+root->right->key;
        }
        if(root->left!=NULL)
            if(root->left->csum>(*ptr)->csum)
                *ptr=root->left;
        if(root->right!=NULL)
            if(root->right->csum>=(*ptr)->csum)
                *ptr=root->right;
        return root;
    }
    
}
void printpath(struct node *ptr,struct stack *S){
   while(ptr->p!=NULL){
    if(ptr->p->left==ptr)
        push(S,'L');
    else    
        push(S,'R');
    ptr=ptr->p;
   } 
}

int main(){
    char a;
    char arr[10000];
    int start=0;
    int sum=0;

    while((a=getchar())!='\n'){
        if(a!=' ')
            arr[start++]=a;

    }
    arr[start]='\0';
    struct stack S;
    S.top=-1;
    struct node *ptr=createnode(0,0);
    S.array=(char*)malloc(1000*sizeof(char));
    struct node*root=buildtree(&ptr,arr,0,start-1,sum);

    printpath(ptr,&S);

    while(S.top!=-1){
        printf("%c",S.array[S.top]);
        S.top--;
    }
    if(ptr->csum!=0)
        printf(" %d ",ptr->csum);
    else
        printf(" %d ",root->key);
    return 0;
}