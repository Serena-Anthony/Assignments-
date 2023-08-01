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

struct tree *PRINT( struct tree *ptr)
{
    printf( "( " );
    if(ptr!=NULL)
    {        
        printf("%d ", ptr->key);
        PRINT(ptr->left);
        PRINT(ptr->right);
    }
    printf(") ");
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
        int k;
        switch(ch)
        {
            case 'i': 
            scanf("%d", &k);
            insert (ptr,k);
            break;

            case 'p':
            PRINT (ptr->root);
            printf("\n");
            break;

            case 'e':
            return -1;
            break;
        }
    }
}

