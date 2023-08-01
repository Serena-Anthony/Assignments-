// print all descendant of x at a distance of k from x in T

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
	struct node* temp = (struct node*)malloc (sizeof(struct node));
    temp->p = NULL;
	temp->key = k;
	temp->left = temp->right = NULL;
	return temp;
}

void preorder(struct node* ptr)
{
    if(ptr!=NULL)
    {
        printf("%d", ptr->key);
        preorder(ptr->left);
        preorder(ptr->right);
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

    if( search(ptr->left,k) == NULL )
    {
    search(ptr->right,k);
    }
}

void descendant(struct node* temp, int k)
{
    if(temp == NULL)
    {
        return ;
    }

      // If we reach a k distant node, print it
      
            if (k==0)
            {
                printf("%d ",temp->key);
            }
            
            descendant(temp->left, k-1);
            descendant(temp->right, k-1);
    
}

//build tree function
int findindex(char a[], int si, int ei)
{
    if(si> ei)
    {
        return -1;
    }

    int count =0;
    for(int i=si; i<=ei; i++)
    {
        if(a[i] == '(')
        {
            count++;
        }
        if(a[i]==')')
        {
            count--;
        }
        if(count== 0)
        {
            return i;
        }

    }
    return -1;
}

struct node* treefromstring( char A[], int si, int ei)
{
    if(si >ei)
    {
        return NULL;
    }
    int num =0;
    // if num has more than 1 digit

    while(si<= ei && A[si]>= '0' && A[ei]<= '9')
    {
        num = num*10;
        num = num + ( A[si] - '0');
        // to make sure we get correct ascii value
        si++;
    }
    struct node *root = create_node(num);
    int index = -1;

    if(si<=ei && A[si] =='(')
    {
        index = findindex( A,si,ei);
    }

    if(index != -1)
    {
        root->left = treefromstring(A, si+1, index -1);
        root->right = treefromstring (A, index+1, ei-1);

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
    char str[1000], a[1000],c;
    int len =0;
    int i=0, k;
    scanf("%[^\n]s", str);
    do
    {
        if (str[i]==' ')
        {
            a[len++]=str[i];    
        }
        i++;
    }
     while (str[i]!= '\0');
    a[len]= '\0';
    printf("%s\n",a);
        int x;
    scanf("%d", &x);
    scanf("%d", &k);
    //struct node*storage = NULL; //to store the address of the node which has x value while creating tree
    struct tree*ptr=(struct tree*)malloc(sizeof(struct tree));
    ptr->root =treefromstring(a, 1, len-2);
    

    //preorder(ptr->root);
    //struct node *temp = search (ptr->root, x);
    //descendant(temp,k);
    
    if((temp == NULL) )
    {
        printf("-1\n");
    }

}