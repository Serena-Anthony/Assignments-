#include<stdio.h>
#include<stdlib.h>

struct node
{
struct node *prev;
int key;
struct node *next;

};

struct LL 
{
struct node *head; 
};

struct node* create_node(int k)
{
    struct node* temp= (struct node*)malloc(sizeof(struct node)); 
    temp->key = k;
    temp->next = NULL; 
    temp->prev = NULL;
    return temp; 
}

struct node *list_search(struct LL *ptr,int k)
{
    struct node* bleh = ptr->head;
    while(bleh != NULL)
    {
        if(bleh->key == k)
        {
            return bleh;
        }
              
     bleh = bleh->next;
    }
    return NULL;
}

void list_insert_front( struct LL *ptr ,int k)
{
    struct node* bleh = create_node(k);
    if (ptr->head==NULL){
        ptr->head=bleh;
    }
    else{
        bleh->next = ptr-> head;
        ptr->head->prev = bleh;
        ptr->head = bleh;
    }
}

void list_insert_tail (struct LL *ptr,char k)
{
    struct node* select= create_node(k);
    
    if (ptr-> head == NULL) // if empty list
    {
        ptr->head = select;
    }
    
    else if (ptr-> head -> next == NULL)
    {
        ptr->head->next = select;
        select->prev = ptr->head;

    }

    else // atleast 1 elemnt
    {
        struct node *ptr2;
        ptr2 = ptr-> head;
        while (ptr2-> next != NULL)
        {
            ptr2 = ptr2->next;
        }
        ptr2->next = select;
        select->prev = ptr2;
    }
}

void list_delete_first(struct LL *ptr)
{
   
    if(ptr->head==NULL)// if no element
    printf("NULL\n");
    
    else
    {
        printf("%d\n", ptr->head->key);
        //free(head);
        ptr->head->prev = NULL;
        ptr->head = ptr->head->next;
    }
}

void list_delete_last(struct LL *ptr)
{
    if (ptr->head == NULL)// if no element
    {
        printf("NULL\n");
    }

    else if (ptr->head->next == NULL)// if only one present
    {
        printf("%d\n", ptr->head->key); 
        free (ptr->head);
        ptr->head = NULL;
    }

    else
    {
        struct node *temp = ptr->head;
        struct node *temp2 = ptr->head;

        while (temp->next != NULL)
        {
            temp2= temp;
            temp = temp->next;
        }
        printf("%d\n",temp->key);
        temp2->prev->next = NULL;
       // free(temp);
        //temp = NULL;

    }
}

void print_list(struct LL *ptr)
{
    struct node* selected= ptr->head;
    if(selected== NULL)
    {
        printf("NULL\n");
    }

    else
    {
        while(selected!=NULL)
        {
        printf("%d ",selected->key);
        selected= selected->next;
        }
        printf("\n");
    }
}

void print_reverse(struct LL *ptr, int n)
{
    struct node* bleh = list_search(ptr,n);
    struct node* selected= ptr->head;
    if(selected== NULL)
    {
        printf("NULL\n");
    }
    else if(bleh==NULL)
    {
        printf("ABSENT\n");
    }
    else
    {
        struct node *bleh1;
        while(bleh!=NULL)
        {
            printf("%d ",bleh->key);
            bleh=bleh->prev;
        }
        printf("\n");
    }
}



void list_insert_after(struct LL *ptr, int k, int n)
{
    struct node* bleh = ptr->head;
    struct node* ptr1;
    if(bleh == NULL)        //if list is empty
    {
        printf("NULL\n");
    }
    else
    {
        ptr1= list_search (ptr,n);
        if (ptr1 != NULL)
        {
            struct node* ptr2 = create_node(k);
            ptr2->next = ptr1->next;
            ptr1->next = ptr2;
            ptr2->prev = ptr1;
            if (ptr1->next !=NULL){
                ptr2->next->prev = ptr2;
            }
        }
        else            //element is not there
        {
            printf("ABSENT\n");
        }
    }
}

void list_insert_before(struct LL *ptr, int k, int n)
{
      struct node* bleh = ptr->head;
      struct node* ptr2 = create_node(k);

      if(bleh== NULL)// no element present
      {
        printf("NULL\n");
      }

      else if ( bleh->key ==n ) 
      {
        ptr2->next = bleh;
        bleh->prev= ptr2;
        ptr->head = ptr2;
        
      }

      else
      {
        struct node* ptr1 = list_search(ptr, n);
        ptr2->prev = ptr1->prev;
        ptr1->prev->next = ptr2;
        ptr2->next = ptr1;
        ptr1->prev = ptr2;


        if (ptr1==NULL)
        {
            printf( "ABSENT\n");
        }
      }
}

void list_delete(struct LL *ptr,int k)
{
    struct node* bleh = ptr->head;
    struct node* stuff = list_search(ptr,k);
    struct node* ptr1= bleh, *ptr2;

    if(bleh== NULL)// list is empty
    {
        printf("NULL\n");
    }
    else // list not empty
    {
        if (stuff== NULL)
        {
            printf("ABSENT\n");
        }

        else  if (bleh == stuff)
        {
         
                printf("FIRST\n");
                if(ptr->head->next!=NULL)
                {
                    ptr->head->next->prev=NULL;
                }
                ptr->head=NULL;
                free(stuff);
                stuff= NULL;

            
        }

        //for intermediate elements delete
        
        else
        {
            while(ptr1->next != stuff)
            {
                ptr1=ptr1->next;
            }
            printf("%d\n",ptr1->key);
            ptr2=stuff->next;
            if(ptr2!=NULL)
            {
                ptr2->prev=ptr1;
            }
            ptr1->next=ptr2;
            
        }


   }
}

int main ()
{
    struct LL *ptr;
    ptr=(struct LL*)malloc(sizeof(struct LL));
    ptr -> head=NULL;

    char ch;
    int k,n;
    while(1)
    { scanf("%c", &ch);

    switch(ch)
        {
            case 'f':
            scanf(" %d", &k);
            list_insert_front(ptr,k);
            break;

            case 't':
            scanf(" %d", &k);
            list_insert_tail(ptr,k);
            break;
            
            case 'a':
            scanf(" %d %d", &k, &n);
            list_insert_after(ptr,k,n);
            break;

            case 'b':
            scanf(" %d %d", &k, &n);
            list_insert_before(ptr,k,n);
            break;

            case 'd':
            scanf(" %d", &k);
            list_delete(ptr,k);
            break;

            case'i':
            list_delete_first(ptr);
            break;

            case'l':
            list_delete_last(ptr);
            break;

            case'r':
            scanf(" %d", &n);
            print_reverse(ptr,n);
            break;

            case 'p':
            print_list(ptr);
            break;

            case'e':
            return 0;
       
        }
    }
}