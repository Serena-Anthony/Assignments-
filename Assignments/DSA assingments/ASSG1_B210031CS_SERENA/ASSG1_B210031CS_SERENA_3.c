// write a program to print the number of subtrees whose sum of the key values is equal to the given sum.

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

int sumsubtree(struct node*ptr)
{
	if(ptr == NULL)
	{
		return 0;
	}

	return (sumsubtree(ptr->left) + sumsubtree(ptr->right) + ptr->key );
}

// given in preorder
void preorder(struct node*ptr, int sum, struct node* sum1)
{
	if(ptr== NULL)
	{
		return ;	
	}
	
	if( (sumsubtree(ptr)) == sum)
	{
		sum1->key = sum1->key + 1;
	}

	preorder(ptr->left, sum, sum1);
	preorder(ptr->right, sum, sum1);
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
    
    int sum;
    scanf("%d", &sum);
    
    struct tree* ptr = (struct tree*)malloc(sizeof(struct tree));
	struct node* sum1 =create_node(0);
    struct node* temp =treefromstring(A, 1, len-2);
    preorder(temp, sum, sum1);

	printf("%d ", sum1->key);
}
