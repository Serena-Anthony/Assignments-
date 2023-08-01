// T and a node with key value k, write a program to print all the ancestors of k in T. Assume unique key values.

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
    struct node *p;
	struct node *left, *right;
};

struct tree
{
	struct node* root;
};

struct node* create_node(int k)
{
	struct node* temp = (struct node*)malloc (sizeof(struct node));
    temp->p = NULL;
	temp->key = k;
	temp->left = temp->right = NULL;
	return temp;
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

void ancestor(struct node *z)
{
    if(z == NULL)
    {
        return ;
    }

    if(z!= NULL)
    {
        if(z->p != NULL)
            {
                int temp = z->p->key;
                printf("%d ", temp);
                ancestor(z->p);
            }
    }
}

// build tree function 

int findindex(char A[], int si, int ei)
{
	if(si> ei)
	{ return -1; }
	
	int count =0;
	
	for( int i = si; i <= ei; i++)
	{
		if(A[i]== '(')
		{
			count++;
		}
		
		if (A[i]== ')')
		{
			count --;
		}

		if(count == 0)
		{ return i; }
	}
	return -1;
}

struct node* treefromstring(char A[], int si, int ei)
{
	if(si>ei)
	{ return NULL; }
	int num =0;
	// if number has more than 1 digit
	
	while(si<= ei && A[si]>= '0' && A[ei]<='9')
	{
		num= num*10;
		num = num+ (A[si] - '0');
		// to make sure we remove acii value n get correct 2nd digit
		si++;
	}
	struct node* root = create_node(num);
	int index = -1;
	
	if(si<= ei && A[si]=='(')
	{
		index= findindex(A,si,ei);
	}
	
	if(index != -1)
	{
		root->left = treefromstring(A, si+1, index-1);
		root->right = treefromstring(A, index+2, ei-1);

        if(root->left != NULL)
        {
            root->left->p = root;
        }

        if(root->right != NULL)
        {
            root->right->p = root;
        }
	}
	return root;
}


int main()
{
    char str[1000],A[1000],c;
    int len=0;
    int i=0,k;
    scanf("%[^\n]s",str);
    scanf("%d", &k);
    do
    {
        if(str[i]!=' ')
        {
            A[len++]= str[i];
        }
        i++;
    } while( str[i]!= '\0');
    A[len]= '\0';

    struct tree* ptr=(struct tree*)malloc(sizeof(struct tree));
    ptr->root =treefromstring(A, 1, len-2);
   
    
    struct node *z = search(ptr->root, k);
    ancestor(z);
    if(z==NULL||z->p==NULL)
    {
        printf("-1\n");
    }
}