#include <stdio.h>
#include <stdlib.h>

struct node
{
  int key;
  struct node *left;
  struct node *right;
  int height;
};

struct tree
{
    struct node *root;
};

int height(struct node *n) 
{
  if (n == NULL)
    {return 0;}
  return n->height;
}

int max(int a, int b) 
{
	if(a>b)
	{ return a;}
	else
	{ return b;}
}

struct node *createnode(int k)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = k;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;
	return temp;
}

struct node *rightrotate(struct node *y) 
{
  struct node *x = y->left;
  struct node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct node *leftrotate(struct node *x) 
{
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getbalancefactor(struct node *n) 
{
  if (n == NULL)
    {return 0;}
    else
  {
    return height(n->left) - height(n->right);
  }
}

struct node *insertnode(struct node *ptr, int key) 
{
  // Find the correct position to insertNode the node and insertNode it
  if (ptr == NULL)
    return (createnode(key));

  if (key < ptr->key)
    {
     ptr->left = insertnode(ptr->left, key);
    }
  else if (key > ptr->key)
  {
    ptr->right = insertnode(ptr->right, key);
  }
  else
    { return ptr; }

  // Update the balance factor of each node and
  // Balance the tree
  ptr->height = 1 + max(height(ptr->left),height(ptr->right));

  int balance = getbalancefactor(ptr);
  if (balance > 1 && key <  ptr->left->key)
    { return rightrotate(ptr); }

  if (balance < -1 && key >  ptr->right->key)
    { return leftrotate(ptr); }

  if (balance > 1 && key > ptr->left->key) 
  {
    ptr->left = leftrotate(ptr->left);
    return rightrotate(ptr);
  }

  if (balance < -1 && key < ptr->right->key) 
  {
    ptr->right = rightrotate(ptr->right);
    return leftrotate(ptr);
  }

  return ptr;
}

struct node *delete(struct node *temp, int k)
{
    if (temp==NULL)
    {
        return NULL;
    }
    if(temp->key > k)
    {
        temp->left = delete(temp->left, k);
    }
    else if(temp->key<k)
    {
        temp->right = delete(temp->right, k);
    }
    else
    {
      // ie temp->key == k therefore replace with sucessor
        struct node *temp1 = NULL;
        if(temp->right!=NULL)
        {
            temp1=temp->right;
            while(temp1->left!=NULL)
            {
                temp1=temp1->left;
            }
            temp->key=temp1->key;
            // then do next step to delete the value duplication at temp 1 location eg 10 10 in both location
            temp->right = delete(temp->right, temp1->key);
        }
        else
        {
            return temp->left;
        }
    }
    return temp;

  // Update the balance factor of each node and
  // Balance the tree
  temp->height = 1 + max(height(temp->left),height(temp->right));

  int balance = getbalancefactor(temp);
  if (balance > 1 && k <  temp->left->key)
    { return rightrotate(temp); }

  if (balance < -1 && k >  temp->right->key)
    { return leftrotate(temp); }

  if (balance > 1 && k > temp->left->key) 
  {
    temp->left = leftrotate(temp->left);
    return rightrotate(temp);
  }

  if (balance < -1 && k < temp->right->key) 
  {
    temp->right = rightrotate(temp->right);
    return leftrotate(temp);
  }

  return temp;
}

int countNodesGreaterThanK(struct node* ptr, int k) 
{
	while (ptr != NULL) 
	{
	    
	    if(ptr->key > k)
	    {
	    	return (1+countNodesGreaterThanK(ptr->left,k)+countNodesGreaterThanK(ptr->right,k));
	    }
	    else
	    {
	    return (countNodesGreaterThanK(ptr->left,k)+countNodesGreaterThanK(ptr->right,k));
	    }
	} 
	
}

void inorder(struct node *ptr, int k)
{
    if(ptr!=NULL)
    {
        
        inorder(ptr->left,k);
        if(ptr->key >k)
        {
        printf("%d ",ptr->key);
        }
        inorder(ptr->right,k);
    }
    else
    {
        return ;
    }
}


int main()
{
struct tree *ptr = (struct tree*)malloc(sizeof(struct tree));
ptr->root = NULL;

//struct node*count = createnode(0);

char ch;
while(1)
	{
		scanf("%c",&ch);
		
		if(ch == 'i')
		{
			int m;
			scanf("%d", &m);
			ptr->root = insertnode(ptr->root,m);
		}
		
		else if(ch == 'c')
		{
			int k;
			scanf("%d", &k);
			printf("%d\n", countNodesGreaterThanK(ptr->root, k) );
			inorder(ptr->root, k);
		   printf("\n");
		}

    else if(ch =='d')
    {
      int k;
      scanf("%d", k);
      int temp =delete(ptr->root, k);
      printf("%d", temp);
    }
		
		else if(ch == 'e')
		{
			break;
		}
		
	}
	
}


