//program to check functions

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *p;
};

struct tree
{
    struct node *root;
};

struct node*create_node(int k)
{
    struct node* temp= (struct node*)malloc(sizeof(struct node)); 
    temp->key = k;
    temp->left = NULL; 
    temp->right = NULL; 
    temp->p = NULL; 
    return temp; 
}

struct node* insert (struct tree* ptr, int k)
{
    struct node *temp = create_node(k);
    struct node *x = ptr->root;
    struct node *y = NULL;

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

struct node *search ( struct node *ptr ,int k)
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

struct node* minval (struct node* ptr)
{ 
    if(ptr==NULL)
    {
        return NULL;
    }

    else 
    {
        struct node *ptr1=ptr;
        while(ptr1->left!=NULL)
        {
            ptr1=ptr1->left;
        }
        return ptr1;
    }    
}

struct node* maxval(struct node* ptr)
{
    if(ptr==NULL)
    {
        return NULL;
    }

    else 
    {
        struct node *ptr1=ptr;
        while(ptr1->right!=NULL)
        {
            ptr1=ptr1->right;
        }
        return ptr1;
    }
}

void inorder(struct node *ptr)
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

void postorder(struct node *ptr)
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

void preorder(struct node *ptr)
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

struct node * successor(struct node *ptr, int k)
{
    struct node *z = search(ptr, k);

    if(z!= NULL)
    {
        if(z->right != NULL)
        {
            return minval(z->right);
        }
        struct node *y = z->p;
        while (y != NULL && z == y->right)
        {
            z=y;
            y= y->p;
        }
        return y;
    }
    return z;
}

struct node * predecessor(struct node *ptr, int k)
{
    struct node *z = search(ptr, k);

    if(z!= NULL)
    {
        if(z->left != NULL)
        {
            return maxval(z->left);
        }
        struct node *y = z->p;
        while (y != NULL && z == y->left)
        {
            z=y;
            y= y->p;
        }
        return y;
    }
    return z;
}

void transplant(struct tree *ptr, struct node *u, struct node *v)
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

struct node * delete (struct tree* ptr, int k)
{
    struct node *z = search(ptr->root, k);
    struct node *y;
    
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
            y=minval(z->right);
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


int level(struct node *ptr)
{
    int level =1;
    while(ptr->p != NULL)
    {
        level++;
        ptr= ptr->p;
    }
    return level;
}

int main()
{
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    struct tree*ptr=(struct tree*)malloc(sizeof(struct tree));
    struct tree ptr1;
    ptr= &ptr1;
    ptr->root=NULL;

     char ch;
    while(1)
    {
        scanf("%c",&ch);
        int k,i,m;
        switch(ch)
        {
            //  d s l m x r u i p t e
            case 'a': 
            scanf("%d", &k);
            insert (ptr,k);
            break;
            
            case 'd':
            scanf("%d", &k);
            if(search(ptr->root,k)!=NULL)
            {
            temp =delete(ptr,k);
           // printf("%d", temp->key);
            }
            else
            {
                printf("-1\n");
            }
            break;

            case 's':
            scanf("%d", &k);
            if(search(ptr->root,k)==NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("1\n");
            }
            break;

            case 'x':
            temp = maxval(ptr->root);
            if(temp ==NULL)
            {
                printf("-1\n");
            }
            else
            {
            printf ("%d\n" ,temp->key);
            }
            break;
            
            case 'm':
            temp = minval(ptr->root);
            if(temp ==NULL)
            {
                printf("-1\n");
            }
            else
            {
            printf ("%d\n" ,temp->key);
            }
            break;
            
            case 'l':
            scanf("%d",&k );
            struct node *ptr2=search(ptr->root,k);
            if(ptr2!=NULL)
            {
                int bleh =level(ptr2);
                printf("%d \n", bleh );
            }
            else
            {
                printf("-1\n");
            }
            break;
            
            case 'r':
            scanf("%d", &k);
            if(search(ptr->root,k)==NULL)
            {
                printf("-1\n");
            }
            else
            {
                temp =predecessor(ptr->root,k);
                printf("%d \n", temp->key);
            }
            break;

            case 'u':
            scanf("%d", &k);
            if(search(ptr->root,k)==NULL)
            {
                printf("-1\n");
            }
            else
            {
                temp =successor(ptr->root,k);
                printf("%d\n", temp->key);
            }
            break;

            case 'i':
            if(ptr->root==NULL)
            {
                printf("-1\n");
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
                printf("-1\n");
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
                printf("-1\n");
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

