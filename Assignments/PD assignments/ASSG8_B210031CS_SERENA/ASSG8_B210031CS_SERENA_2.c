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
void insert (struct tree_root* ptr, int k)
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

struct tree * find_min (struct tree* ptr)
{ 
    if(ptr==NULL)
    {
        return NULL;
    }

    else 
    {
        struct tree *ptr1=ptr;
        while(ptr1->left!=NULL)
        {
            ptr1=ptr1->left;
        }
        return ptr1;
    }    
}

struct tree * find_max (struct tree* ptr)
{
    if(ptr==NULL)
    {
        return NULL;
    }

    else 
    {
        struct tree *ptr1=ptr;
        while(ptr1->right!=NULL)
        {
            ptr1=ptr1->right;
        }
        return ptr1;
    }
}

struct tree* search ( struct tree *ptr ,int k)
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

void transplant(struct tree_root *ptr, struct tree *u, struct tree *v)
{
    if (u->p == NULL)
    {
        ptr->root = v;
    }
    else if (u == u->p->left) // u is lchild of parent 
    {
        u->p->left = v;
    }
    else 
    {
        u->p->right =v;
    }

    if(v != NULL)
    {
        v->p = u ->p;
    }
}

struct tree * delete (struct tree_root* ptr, int k)
{
    struct tree *z = search(ptr->root, k);
    struct tree *y;
    
    if(z!=NULL)
    {   
        
        if(z->left==NULL)
        {
            transplant(ptr,z,z->right);
        }
        else if(z->right==NULL)
        {
            transplant(ptr,z,z->left);
        }
        else
        {
            y=find_min(z->right);
            if(y->p!=z)
            {
                transplant(ptr,y,y->right);
                y->right=z->right;
                y->right->p=y;
            }
            transplant(ptr,z,y);
            y->left=z->left;
            y->left->p=y;
        }
    }
return z;
}

struct tree * successor(struct tree *ptr, int k)
{
    struct tree *z = search(ptr, k);

    if(z!= NULL)
    {
        if(z->right != NULL)
        {
            return find_min(z->right);
        }
        struct tree *y = z->p;
        while (y != NULL && z == y->right)
        {
            z=y;
            y= y->p;
        }
        return y;
    }

    return z;
}

struct tree * predecessor(struct tree *ptr, int k)
{
    struct tree *z = search(ptr, k);

    if(z!= NULL)
    {
        if(z->left != NULL)
        {
            return find_max(z->left);
        }
        struct tree *y = z->p;
        while (y != NULL && z == y->left)
        {
            z=y;
            y= y->p;
        }
        return y;
    }

    return z;
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

            case 'd':
            scanf("%d", &k);
            struct tree *z=delete(ptr,k);
            if (z != NULL)
            {
                printf("%d\n",z->key);
            }
            else
            {
                printf ("NotFound\n");
            }
            break;

            case 'c':
            scanf("%d", &k);
            
            if (successor(ptr->root,k) != 0)
            {
                printf("%d\n", successor(ptr->root,k)->key);
            }
            else
            {
                printf("NotFound\n");
            }
            break;

            case 'r':
            scanf("%d", &k);
            
            if (predecessor(ptr->root,k) != 0)
            {
                printf("%d\n", predecessor(ptr->root,k)->key);
            }
            else
            {
                printf("NotFound\n");
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

            case 'e':
            return -1;
            break;

        }
    }
}
