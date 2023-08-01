#include <stdio.h>
#include <stdlib.h>

struct node {
  int key;
  struct node *left;
  struct node *right;
  int height;
  int num_keys;
};

struct tree
{
    struct node *root;
};


struct node *createnode(int k)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->key = k;
	temp->left = NULL;
	temp->right = NULL;
    temp->height = 1;
	temp->num_keys = 1;
	return temp;
}

int height(struct node *n) 
{
  if (n == NULL)
    {return 0;}
    else
    {
    return n->height;
    }
}

int count(struct node *ptr)
{
	int count=0;
	if(ptr!= NULL)
	{
		while(ptr->left!= NULL)
		{
			count++;
			ptr= ptr->left;
		}

		while(ptr->right != NULL)
		{
			count++;
			ptr= ptr->right;
		}
	}
	count = count+1;
}

int max(int a, int b) 
{
	if(a>b)
	{ return a;}
	else
	{ return b;}
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
	int num;
  // Find the correct position to insertNode the node and insertNode it
  if (ptr == NULL)
    return (createnode(key));

  if (key < ptr->key)
    {
		int num = count(ptr->left);
     ptr->left = insertnode(ptr->left, key);
	 num= num+1;
    }
  else if (key > ptr->key)
  {
	int num = count(ptr->right);
    ptr->right = insertnode(ptr->right, key);
	num = num+1;
  }
  else
    { 
		int num = count(ptr);		
		return ptr;
	}


  // Update the balance factor of each node and
  // Balance the tree
  ptr->height = 1 + max(height(ptr->left),height(ptr->right));
  num= num+1; 

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

void sort(int a[], int n)
{
    for(int i =1; i<n; i++)
    {
        int temp = a[i];
        int j = i-1;
        while(j>=0 && a[j]> temp)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[ j+ 1] = temp ;
    }
}

int main()
{
    int a[1000];
    for(int i=0; i<1000;i++)
    {
        a[i]= 0;
    }
    int i =0;

     char ch;
  while(1)
	{
		scanf("%c",&ch);
		
		if(ch == 'i')
		{
			int m;
			scanf("%d", &m);
      a[i++] = m;
             //insert(ptr,m);
		}
		
		else if(ch == 'g')
		{
            sort(a,i); 
            int median =0; 
            int len = i-1;
            if(len %2 != 0)
            {
                 median =(len)/2;
            }
            else
            {
                median =(len + 1)/2;
            }
            printf("%d\n", a[median]);
		}
		
		else if(ch == 't')
		{
			break;
		}
		
	}
	
}

