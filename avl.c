#include <stdio.h>
#include <stdlib.h>

// Create node

struct node 
{
  int key;
  struct node *left;
  struct node *right;
  int height;
};

// Calculate height
int height(struct node *N) 
{
  if (N == NULL)
    return 0;
  return N->height;
}

int maxvalue(int a, int b)
{
    if(a>b)
    { return a; }
    else
    { return b; }
}

// Create a node : temp
struct node *newnode(int key) 
{
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = key;
  temp->left = NULL;
  temp->right = NULL;
  temp->height = 1;
  return (temp);
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
        return search(ptr->left,k);
    }
    else if (k> ptr->key)
    {
        return search(ptr->right,k);
    }
}

// Right rotate
struct node *rightR(struct node *y) 
{
  struct node *x = y->left;
  struct node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = maxvalue(height(y->left), height(y->right)) + 1;
  x->height = maxvalue(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
struct node *leftR(struct node *x) 
{
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = maxvalue(height(x->left), height(x->right)) + 1;
  y->height = maxvalue(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct node *N) 
{
  if (N == NULL)
    { return 0; }
  else
  {
  return height(N->left) - height(N->right);
  }
}

// Insert node
struct node *insertnode(struct node *temp, int key) 
{
  // Find the correct position to insertnode the node and insertnode it
  if (temp == NULL)
  {
    return (newnode(key));
  }
  if (key < temp->key)
   { 
      temp->left = insertnode(temp->left, key); 
   }
  else if (key > temp->key)
   { 
     temp->right = insertnode(temp->right, key); 
   }
  else
  {
    return temp;
  }
  // Update the balance factor of each node and
  // Balance the tree
  temp->height = 1 + maxvalue(height(temp->left),height(temp->right));

  int balance = getBalance(temp);
  
  if (balance > 1 && key < temp->left->key)
    { return rightR(temp); }

  else if (balance < -1 && key > temp->right->key)
    { return leftR(temp); }

  else if (balance > 1 && key > temp->left->key) 
  {
    temp->left = leftR(temp->left);
    return rightR(temp);
  }

  else if (balance < -1 && key < temp->right->key) 
  {
    temp->right = rightR(temp->right);
    return leftR(temp);
  }

  /*
    balance = getbalance(temp)

    if(balance > 1)
    {
        if(temp->left->right->height > temp->left->left->height)
        {
          temp->left = leftrotate( temp->left );
        }
        return (rightrotate( temp ));
    }
    
    else if (balance < -1)
    {
      if( temp->right->left->height > temp->right->right->height)
      {
        temp->right = rightrotate ( temp->right);
      }
      return (leftrotate( temp ));
      }

  */

  return temp;
}

struct node *maxnode(struct node *temp) 
{
  struct node *current = temp;

  while (current->right != NULL)
  {
    current = current->right;
  }

  return current;
}

struct node *min(struct node *temp) 
{
  struct node *current = temp;

  while (current->left != NULL)
  {
    current = current->left;
  }

  return current;
}

// Delete a nodes
struct node *deletenode(struct node *root, int key) 
{
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deletenode(root->left, key);

  else if (key > root->key)
    root->right = deletenode(root->right, key);

  else// key is equl to root key 
  {
    if ((root->left == NULL) || (root->right == NULL)) 
    {
      struct node *temp;

      if(root->left == NULL)
      {
         temp = root->right;
      }
      else
      {
         temp = root->left;
      }

      if (temp == NULL) // its a leaf node
      {
        temp = root;
        root = NULL;
      } 
      else
       { 
        *root = *temp; 
       }
      free(temp);
    }

    else 
    {// node with 2 child ->get inorder sucessor 
      struct node *temp = maxnode(root->left);
      root->key = temp->key;
      root->left = deletenode(root->left, temp->key);
    }
  }

  if (root == NULL)
   { return root; }

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + maxvalue(height(root->left), height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) 
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) 
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Print the tree
void preorder(struct node *root) 
{
  printf("( ");
  if (root != NULL) {
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
  }
  printf(") ");
}

int main() 
{
    struct node* root=NULL;
    int k;
    char ch;
    struct  node* x;
while(1)
  {
    scanf("%c",&ch);

        if(ch == 'i')
        {
            int k;
            scanf("%d", &k);
            root = insertnode(root,k);
        }
        else if(ch == 'd')
        {
            int k;
            scanf("%d", &k);
            x= search(root,k);
            if(x!= NULL)
            {
                printf("%d\n", x->key);
                root=deletenode(root,k);
               // printf("%d\n",minValuenode(root));
            }
            else
            {
                printf("FALSE\n");
            }
        }
       
        else if(ch == 'p')
        {
            preorder(root);
            printf("\n");
        }

        else if(ch == 's')
        {
            int k;
            scanf("%d%*c",&k);
            x=search(root,k);
            if(x!=NULL){
                printf("TRUE\n");
            }        
            else{
                printf("FALSE\n");
            }
        }

        else if(ch == 'b')
        {
            int k;
            scanf("%d", &k);
            if(search(root,k) != NULL)
            {
               int temp= getBalance(root);
               printf("%d", temp);
            }
            else
            {
                printf("FALSE");
            }
            printf("\n");
        }

        else if(ch == 'e')
        { break ;}
    }
  return 0;
}

