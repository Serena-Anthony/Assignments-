// two key values x and y (x ̸= y) that specify the range of key values, print the key values of the nodes that are in the given
// range(inclusive of x and y)

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	struct node *left, *right;
};

struct tree
{
	struct node* root;
};

struct node* create_node(int k)
{
	struct node* temp = (struct node *)malloc (sizeof(struct node*));
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
	}
	
	return root;
}

void inorder(struct node*ptr, int x, int y)
{
	if(ptr== NULL)
	{
		return ;	
	}

    inorder(ptr->left,x,y);
    if(ptr-> key >=x && ptr->key <= y)
    {
        printf("%d ", ptr->key);
    }
	inorder(ptr->right,x,y);
}

int main()
{
    char A[1000],c;
    int i=0;
    int len=0;
    do
    {
        scanf("%c", &c);
        if(c !=' ')
        {
            A[i++]= c;
            len++;
        }
    } while( c!= '\n');
    A[i]= '\0';

    int x,y;
    scanf("%d %d", &x, &y);

    struct tree*ptr=(struct tree*)malloc(sizeof(struct tree));
    ptr->root =treefromstring(A, 1, len-2);
    inorder(ptr->root,x,y);
}