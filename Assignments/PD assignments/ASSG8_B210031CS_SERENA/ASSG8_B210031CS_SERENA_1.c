#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *p;
};

struct tree_root
{
    struct tree *root;
};

struct tree *create_node(int k)
{
    struct tree* temp= (struct tree*)malloc(sizeof(struct tree)); 
    temp->key = k;
    temp->left = NULL; 
    temp->right = NULL; 
    temp->p = NULL; 
    return temp; 
}

struct tree* insert (struct tree_root* ptr, int k)
{
    struct tree *temp = create_node(k);
    struct tree *x = ptr->root;
    struct tree *y = NULL;

    while (x != NULL)
    {
        y=x ;
        if (k < x->key)
        {
            x= x->left;
        }
        else
        {
            x = x->right;
        }
    }

    temp->p =y;

    if(y== NULL)
    {
        ptr->root = temp;
    }
    else if(temp->key<y->key)
    {
        y->left=temp;
    }
    else
    {
        y->right=temp;
    }
}

struct tree *search ( struct tree *ptr ,int k)
{
    if(ptr== NULL)
    {
     return NULL;
    }

    else if(k==ptr->key)
    {
        return ptr;
    }

    else if (k< ptr->key)
    {
       search (ptr->left, k);
    }

    else if (k> ptr->key)
    {
      search ( ptr->right, k);
    }
   
}

int find_min (struct tree_root* ptr)
{ 
    if(ptr->root==NULL)
    {
        return 0;
    }

    else 
    {
        struct tree *ptr1=ptr->root;
        while(ptr1->left!=NULL)
        {
            ptr1=ptr1->left;
        }
        return ptr1->key;
    }    
}

int find_max (struct tree_root* ptr)
{
    if(ptr->root==NULL)
    {
        return 0;
    }

    else 
    {
        struct tree *ptr1=ptr->root;
        while(ptr1->right!=NULL)
        {
            ptr1=ptr1->right;
        }
        return ptr1->key;
    }
}

void inorder(struct tree *ptr)
{
    if(ptr!=NULL)
    {
        inorder(ptr->left);
        printf("%d ",ptr->key);
        inorder(ptr->right);
    }
    else
    {
        return ;
    }
}

void postorder(struct tree *ptr)
{
    if(ptr!=NULL)
    {
        postorder(ptr->left);
        postorder(ptr->right);
        printf("%d ",ptr->key);
    }
    else
    {
        return ;
    }
}

void preorder(struct tree *ptr)
{
    if(ptr!=NULL)
    {
        printf("%d ",ptr->key);
        preorder(ptr->left);
        preorder(ptr->right);
    }
    else
    {
        return ;
    }
}

int main()
{
    struct tree_root *ptr=(struct tree_root*)malloc(sizeof(struct tree_root));
    struct tree_root ptr1;
    ptr= &ptr1;
    ptr->root=NULL;
 
    char ch;
    while(1)
    {
        scanf("%c",&ch);
        int k,i,m;
        switch(ch)
        {
            case 'a': 
            scanf("%d", &k);
            insert (ptr,k);
            break;
            
            case 's':
            scanf("%d", &k);
            if(search(ptr->root,k)!=NULL)
            {
                printf("Found\n");
            }
            else
            {
                printf("NotFound\n");
            }
            break;
            
            case 'x':
            m = find_max(ptr);
            if(m==0)
            {
                printf("NIL");
            }
            else
            {
            printf ("%d\n" ,m);
            }
            break;
            
            case 'n':
             m = find_min(ptr);
            if(m==0)
            {
                printf("NIL");
            }
            else
            {
            printf ("%d\n" ,m);
            }
            break;
            
            case 'i':
            if(ptr->root==NULL)
            {
                printf("NIL\n");
            }
            else
            {
                inorder(ptr->root);
                printf("\n");
            }          
            break;
            
            case 'p':
            if(ptr->root==NULL)
            {
                printf("NIL\n");
            }
            else
            {
                preorder(ptr->root);
                printf("\n");
            }   
            break;
            
            case 't':
            if(ptr->root==NULL)
            {
                printf("NIL\n");
            }
            else
            {
                postorder(ptr->root);
                printf("\n");
            }   
            break;
            
            case 'e':
            return -1;
            break;
        }
    }    
}
