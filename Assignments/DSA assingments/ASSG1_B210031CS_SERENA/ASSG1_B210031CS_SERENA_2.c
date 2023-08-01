//Program to count the number of nodes whose grandparent has a child as a leaf node in a given binary tree.

#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
    struct node* p;
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

void preorder(struct node*ptr, struct node *leaf)
{
	if(ptr== NULL)
	{
		return ;	
	}
	
	if( ptr->p != NULL)
	{
        if( ptr->p->p != NULL)
        {
            struct node *temp = ptr->p->p;
            struct node *bleh;
            if(ptr->p == temp->left)
            {
                  bleh = temp->right;
            }
            else
            {
                bleh = temp->left;
            }

            if(bleh != NULL && bleh->left == NULL && bleh->right == NULL)// bleh is a leaf node
            {
                    leaf->key ++;
                    //printf("%d\n",leaf->key);
            }
        }
	}


	preorder(ptr->left, leaf);
	preorder(ptr->right, leaf);
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
        if(root->left!=NULL)
        {
            root->left->p=root;
        }
		root->right = treefromstring(A, index+2, ei-1);
        if(root->right!=NULL)
        {
            root->right->p=root;
        }
	}
	
	return root;
}

int main()
{
    char str[1000],A[1000],c;
    int len=0;
    int i=0;
    scanf("%[^\n]s",str);
    //scanf("%d", &k);
	//remove spaces n convert given to a string
    do
    {
        if(str[i]!=' ')
        {
            A[len++]= str[i];
        }
        i++;
    } while( str[i]!= '\0');
    A[len]= '\0';
	printf("%s", A);

    //struct node*temp=(struct node*)malloc(sizeof(struct node));
    struct tree*ptr=(struct tree*)malloc(sizeof(struct tree));
    struct tree ptr1;
    ptr= &ptr1;
    ptr->root =treefromstring(A, 1, len-2);
    struct node* leaf =create_node(0);
    //printf("completed\n");
    preorder(ptr->root,leaf);
    printf("%d\n", leaf->key);
}
