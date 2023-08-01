#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    int degree;
    struct node* child;
    struct node* sibling;
    struct node* parent;
};

struct heap
{
    struct node* head;
};

struct node* createnode(int k)
{
    struct node* temp = (struct node*)malloc (sizeof(struct node));
    temp->data = k;
    temp->degree =0;
    temp->child = NULL;
    temp->sibling = NULL;
    temp->parent = NULL;
 //   printf("created\n");
    return temp;
}

struct heap* make_heap()
{
    struct heap* temp = (struct heap*)malloc (sizeof(struct heap));
    temp ->head = NULL;
    return temp;
}

void print_binomial(struct heap* H)
{
    struct node* temp = NULL;
    if(H== NULL)
    {
        return ;
    }
    temp = H->head;
    while(temp!= NULL)
    {
        printf("%d ", temp->data);
        temp = temp->sibling;
    }
    printf("\n");
}

// link 2 nodes of same degree
void link (struct node*y, struct node*z)
{
   // struct node*y,z;
   // z is made parent of y 
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
//    printf("LINKED \n");
}

struct heap* binomial_merge(struct heap* H1, struct heap* H2) // ensure 2 tree of same degree are adjacent to each other
{
    struct heap* H= make_heap();
    struct node* temp1 = H1->head;
    struct node* temp2 = H2->head;
   // struct node *initial=NULL;
    struct node* pointer =NULL;
  
    if(temp1 != NULL)
    {
        if(temp2!=NULL && temp1->degree <= temp2->degree)
        {
            H->head = temp1;
            temp1 = temp1->sibling;
        }
        else if(temp2!=NULL && temp1->degree > temp2->degree)
        {
            H->head = temp2;
            temp2= temp2->sibling;
        }
        else  //temp2 = null
        {
            H->head = temp1;
            temp1 = temp1->sibling;
        }
    }
    else
    {
        H->head = temp2;
        temp2 = temp2->sibling;
    }

      pointer = H->head;
    while(temp1!= NULL && temp2!=NULL)
    {
        if(temp1->degree >= temp2->degree)
        {
            pointer->sibling = temp2;
            temp2= temp2->sibling;
        }
        else
        {
            pointer->sibling = temp1;
            temp1 = temp1->sibling;
        }
        pointer = pointer->sibling;
    }
    
    if(temp1!= NULL)
    {
        pointer->sibling = temp1;
    }
    if(temp2!= NULL)
    {
        pointer->sibling = temp2;
    }
    return H;
}

/*
binomial union = 2 phases 
phase 1: call binomial merge = merge h1,h2 into h tht is sorted by degree in acsending order
phase 2:perform link operation thus atmax one node of same degree
*/
struct heap* heap_union (struct heap* H1, struct heap *H2)
{
    struct heap * H = make_heap();
    H= binomial_merge(H1,H2);
   // printf("called merged\n");
    free(H1);
    free(H2);
    if(H->head == NULL)
    {
  //      printf("entered here cuz head is null \n");
        return H;
    }

    struct node* x = H->head;
    struct node* prev = NULL;                   //6
    struct node* next = x->sibling;             //7
   // printf("gonna enter while\n");
    while(next != NULL)
    {
      //  printf("entered while \n");
        if ((x->degree != next->degree) || ((next->sibling != NULL) && (((next->sibling)->degree) == x->degree)))
            {
                prev = x;                        // 11 case 1 n 2
                x= next;                         // 12 cases 1 n 2
            }
        else 
        {
                if (x->data <= next->data)                      // 13
            { 
                x->sibling = next->sibling;                        //13  case 3
                link(next, x);                                        
            }

        else
           {
                if (prev == NULL)               //case 4
                {
                    H->head = next;
                }
                else
                {
                    prev->sibling = next;
                }
                    link(x, next);
                    x= next;
           }
       }
        next= x->sibling;
    }
 //   printf("union completed\n");
    return H;
}

struct heap *insert (struct heap* H, struct node *x)
{
    struct heap* H1 = make_heap();
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1->head = x;
    H = heap_union(H, H1);
   // printf("INSERTED\n");
    return H ;
}

struct node* search(struct node* ptr, int k)
{

   // printf("entered searching \n");
    struct node *x = ptr;
    struct node *bleh = NULL;
    if (x->data == k)
    {
        bleh = x;
        return bleh;
    }
    if (x->child != NULL && bleh == NULL)
    {
        bleh = search(x->child, k);
    }

    if (x->sibling != NULL && bleh == NULL)
    {
        bleh = search(x->sibling, k);
    }
    return bleh;

}

int minimum(struct heap* ptr)
{
   // printf("entered to find min \n");
    struct node* x = ptr->head;
    struct node*y = NULL;
    if(x== NULL)
    {
        return 0;
    }

    int min = x->data;
    while(x->sibling!= NULL)
    {
        if(x->sibling->data < min)
        {
            min = x->sibling->data;
           // y= x;
        }
        x = x->sibling;
    }
    return min;
}

int decrease_key(struct heap *H,int x, int k )
{
   // printf("entered decrease key\n");
    //struct node* temp = search(H->head,x);
    struct node* temp ;
    temp = search(H->head, x);
   // struct node* bleh= NULL;
    int temp1;

    if(temp == NULL)
    {
      //  printf("value not in list\n");
        return 1000001;
    }
    if(temp !=NULL)
    {
       // printf("element is present\n");
        if(k > temp->data)
        { 
            //printf("value not valid\n");
            return 1000001;
        }

        else if(k <temp->data)
        {
            //printf("enters to be replaced\n");
            temp->data = k;
            struct node* y = temp;
            struct node* z = temp->parent;
            while(z!= NULL && y->data < z->data)
            {
                temp1 = y->data;
                y->data = z->data;
                z->data = temp1;
                z= y;
                y = z->parent ;
            }
            return k;
        }
    }
   // printf("key has been reduced\n");
}

struct node* rev_list(struct heap* ptr, struct node* x)
{
    if(x->sibling != NULL)
    {
        rev_list(ptr, x->sibling);
        (x->sibling)->sibling = x;
    }
    else
    {
        ptr->head = x;
    }
    return x;
}

struct heap* binomialheap_extract_min(struct heap* H1)
{
   // struct node * MIN= minimum(H);
  // printf("entered the function extract\n");
    struct node* ptr= NULL;   
    struct node* MIN = NULL;
    struct heap* h_rev = make_heap();
    struct node* temp ;
    ptr= H1->head;
    
   // printf("the min to be extracted is %d\n", MIN->data);
    //struct heap* new = make_heap();

    if(ptr == NULL)
    {
      //  printf("heap is emtpy nothign to be extracted\n");
        return NULL;
    }

    int min = ptr->data;
    temp = ptr;
    while(temp->sibling != NULL)
    {
        if(temp->sibling->data < min)
        {
            min = temp->sibling->data;
            MIN = temp;
            ptr = temp->sibling;
        }
        temp = temp->sibling;
    }
   // printf("found min\n");

    if(MIN == NULL && ptr->sibling == NULL)
    {
        H1->head = NULL;
    }
    else if(MIN == NULL)
    {
        H1->head = ptr->sibling;
    }
    else if(MIN->sibling == NULL)
    {
        MIN = NULL;
    }
    else
    {
        MIN->sibling = ptr->sibling ;
    }

    if(ptr->child != NULL)
    {
        struct node* bleh = rev_list(h_rev,ptr->child);
        bleh->sibling = NULL;
        (ptr->child)->sibling= NULL;
    }

    H1=heap_union(H1, h_rev);
    printf("%d\n", min);
    return H1;
}
   
struct heap* delete(struct heap* H, int k)
{   
    decrease_key(H,k, -10000000);
    H= binomialheap_extract_min(H);
    return H;
}

int main()
{
   // struct heap * ptr, p;
   // ptr= &p;
    struct node* temp = NULL;
    struct heap *H= make_heap();
    struct heap *H1= make_heap();
    struct heap *H2= make_heap();

   // ptr = H1->head;

    //struct heap*ptr1= NULL;
    while (1)
    {
        char ch;
        scanf("%c", &ch);

        if (ch == 'i')
        {
            int k;
            scanf("%d", &k);
                temp = createnode(k);
            //temp = search(H1->head, k);
            H1 = insert(H1,temp);
            //printf("INSERTED in heap 1\n");
        }

        if (ch == 'j')
        {
            int k;
            scanf("%d", &k);
            temp = createnode(k);
            H2 = insert(H2,temp);
            //printf("INSERTED in heap 2\n");
        }
        if (ch == 'p')
        {
            int k;
            scanf("%d", &k);

            if(k == 1) // print heap 1
            {
                //struct heap* ptr1= H1->head;
                print_binomial(H1);
            }
            else if(k == 2) // print heap 2
            {
               // struct heap* ptr2 = H2->head;
                print_binomial(H2);
            }
        }

        if (ch == 'm')
        {
         int min = minimum(H1);
         printf("%d\n", min);
        }

        if (ch == 'x')
        {
           // printf("calling extract min\n");
            H1 = binomialheap_extract_min(H1);
        }

          if (ch == 'r')
        {
            int y, z;
            scanf("%d %d", &y, &z);
            int bleh = decrease_key(H1,y,z);

            if(bleh == 1000001)
            {
                printf("-1");
            }
            else if(bleh != 1000001)
            {
                printf("%d", bleh);
            }
            printf("\n");
        }

         if (ch == 'u')
        {
            H1 = heap_union(H1, H2);
            print_binomial(H1);
        }

        if (ch == 'd')
        {
            int k;
            scanf("%d", &k);
            delete(H1,k);
        }

        if (ch == 'e')
        {
            break;
        }
    }
}