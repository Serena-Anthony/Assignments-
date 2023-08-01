/*red black tree
1. if tree is empty => create new node ; root node black
2. if tree is not empty => create new node; leafnode red
3. if parent of new node is black then exit
4. if parent of new node is red => check color of uncle of newnode
  a. if uncle => black or null => suitable rotation & recolour
  b. if uncle => red => recolour & check if grandparent of newnode is root
     if grandparent not root node => recolour & recheck

Do following if color of x’s parent is not BLACK or x is not root. 
1. If x’s uncle is RED 
  1.Change color of parent and uncle as BLACK. 
  2.color of grand parent as RED. 
  3.Change x = x’s grandparent, repeat steps 2 and 3 for new x. 
2. If x’s uncle is BLACK, then there can be four configurations for x,
    x’s parent (p) and x’s grandparent
    1. Determine the configuration:
      1.Left Case (p is left child of g and x is left child of p).
      2.Left Right Case (p is left child of g and x is right child of p).
      3.Right Right Case
      4.Right Left Case
    2. Change x = x’s parent, repeat steps 2 and 3 for new x
*/


/*
rbinsert(r,x)
# r is root of subtree with all rb prop except 2 ie root could be red & red root may hav red child

if(x == nil)
return r

else
if(x.key < r.key)
  r.left = rbinsert(r.left, x)
  if(r.left.color == red)
    if(r.left.left.color == red || r.left.right.color == red)
      if (r.right.color== red)
        r.color = red
        r.left.color = black
        r.right.color =black
        return(r)
      if (r.left.right.color == red)
        r.left = leftrotate(r.left)
    else 
      r= rightrotate(r)
      r.right.color = red
      r.color = black
  else
  return(r) 

*/
#include <stdio.h>
#include <stdlib.h>

struct node 
{
  int key;
  struct node *left;
  struct node *right;
  int color;
  // 1- red , 0- black
  //int height;
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
 // temp->height =1;
	temp->color = 1;
	return temp;
}

struct node *rightrotate(struct node *y) 
{
  struct node *x = y->left;
  struct node *T2 = x->right;

  x->right = y;
  y->left = T2;
  return x;
}

struct node *leftrotate(struct node *x) 
{
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;
  return y;
}

struct node* rbinsert (struct node* ptr, struct node*x)
{
    if(ptr == NULL)
    {
      return x;
    }

    else if(x->key < ptr->key)
      {
          ptr->left = rbinsert(ptr->left,x);
          
          if(ptr->left->color == 1)
          {
            if ((ptr->left->left && ptr->left->left->color == 1) || (ptr->left->right && ptr->left->right->color == 1))
            {
                if(ptr->right && ptr->right->color == 1)
                {
                  //uncle is red
                  ptr->color = 1;
                  ptr->left->color = 0;
                  ptr->right->color = 0;
                  return (ptr);
                }
                // node rn is grandparent
                else 
                {
                  //uncle was black

                    //this if is case 2:
                    // convert to case 3
                    if(ptr->left->right && ptr->left->right->color==1)
                    {
                    ptr->left = leftrotate(ptr->left);
                    }

                    //case3:
                    ptr= rightrotate(ptr);
                    ptr->right->color = 1;
                    ptr->color = 0;
                    return(ptr);
                }
            }
          }
      }
      
      //symmetric
      else if(x->key > ptr->key)
      {
          ptr->right = rbinsert(ptr->right, x);

          if(ptr->right->color == 1)
          {
            if((ptr->right->right && ptr->right->right->color == 1) || (ptr->right->left && ptr->right->left->color == 1))
            {
              if(ptr->left && ptr->left->color == 1)
              {
                ptr->color = 1;
                ptr->right->color =0;
                ptr->left->color =0;
                return (ptr);
              }

              else
              {
                if(ptr->right->left && ptr->right->left->color == 1)
                {
                  ptr->right = rightrotate(ptr->right);
                }

                ptr = leftrotate(ptr);
                ptr->left->color = 1;
                ptr->color =0;
                return (ptr);
              }
            }
          }
      }


    return (ptr);    
}

struct node* preorder(struct node* ptr)
{
  printf("( ");

  if(ptr != NULL)
  {
    printf("%d ", ptr->key);
    if (ptr->color == 0)
    {
      printf("B ");
    }
    else
    {
      printf("R ");
    }

    preorder(ptr->left);
    preorder(ptr->right);
  }
  printf(") ");

}

int main()
{
  struct tree *ptr = (struct tree*)malloc(sizeof(struct tree));
  ptr->root = NULL;

  int k;
  char a[100];
  while (1)
  {
    scanf("%s", a);

    if(a[0] == 't')
    {
      break;
    }
    else
    {
      int k = atoi(a);
      struct node* temp = createnode(k);
      ptr->root =rbinsert(ptr->root, temp);
      ptr->root->color = 0;
      preorder(ptr->root);
      printf("\n");
    }
  }
}
