#include<stdio.h>
#include<stdlib.h>

struct node
{
char key;
struct node *next;
};

struct LL 
{
struct node *head; 
};

struct node* create_node(char k)
{
    struct node* temp= (struct node*)malloc(sizeof(struct node)); 
    temp->key = k;
    temp->next = NULL; 
    return temp; 
}

void list_insert_front( struct LL *ptr ,char k)
{
    struct node* bleh = create_node(k);
    bleh->next = ptr-> head;
    ptr->head = bleh;
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
    }
}

void list_delete_first(struct LL *ptr)
{
   
    if(ptr->head==NULL)// if no element
    printf("NULL\n");
    
    else
    {
        printf("%c\n", ptr->head->key);
        //free(head);
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
        printf("%c\n", ptr->head->key); 
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
        printf("%c\n",temp->key);
        temp2->next = NULL;
        free(temp);
        temp = NULL;

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
        printf("%c ",selected->key);
        selected= selected->next;
        }
        printf("\n");
    }
}

struct node *list_search(struct LL *ptr,char k)
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

void list_insert_after(struct LL *ptr, char k, char n)
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
        }
        else            //element is not there
        {
            printf("ABSENT\n");
        }
    }
}

void list_insert_before(struct LL *ptr, char k, char n)
{
      struct node* bleh = ptr->head;
      int flag =0;

      if(bleh== NULL)
      {
        printf("NULL\n");
      }

      else if ( bleh->key ==n )
      {
        flag =1;
        struct node* ptr2 = create_node(k);
        ptr2->next = bleh ->next;
        ptr->head = ptr2;
      }

      else
      {
        struct node* ptr1;
        while (bleh != NULL)
        {
            ptr1= bleh;
            bleh = bleh->next;

            if (bleh != NULL && bleh->key == n)
            {
                struct node* ptr2 = create_node(k);
                ptr1->next = ptr2;
                ptr2->next = bleh;
                flag =1;
                break;
            }
        }

        if (flag =0)
        {
            printf( "ABSENT\n");
        }
      }
}

void list_delete(struct LL *ptr,char k)
{
    struct node* bleh = ptr->head;
    struct node* ptr1;

    if (ptr-> head == NULL)
    {
        printf("NULL\n");
    }
    else{
        if(list_search (ptr,k)!=NULL)
        {
            struct node* bleh = ptr->head;
            struct node* ptr1;
            // int flag = 0;

            if (bleh->key ==k)
            {
                bleh = bleh->next;
                printf("%c\n", bleh->key);
                // flag=1;
            }

            else
            {
                while(bleh != NULL)
                {
                    ptr1 = bleh;
                    bleh = bleh->next;
                    if (bleh->key == k)
                    {
                        ptr1->next = bleh->next;
                        if (bleh->next == NULL)
                        {
                            printf("LAST");
                            break;
                        }
                        printf("%c\n", ptr1->next->key);
                        // flag =1;
                        break;
                    }
                }
            }
        }
        else{
            printf("ABSENT\n");
        }
    }
}

int main ()
{
    struct LL *ptr;
    ptr -> head=NULL;

    char ch,k,n;
    while(1)
    { scanf("%c", &ch);

    switch(ch)
        {
            case 'f':
            scanf(" %c", &k);
            list_insert_front(ptr,k);
            break;

            case 't':
            scanf(" %c", &k);
            list_insert_tail(ptr,k);
            break;
            
            case 'a':
            scanf(" %c %c", &k, &n);
            list_insert_after(ptr,k,n);
            break;

            case 'b':
            scanf(" %c %c", &k, &n);
            list_insert_before(ptr,k,n);
            break;

            case 'd':
            scanf(" %c", &k);
            list_delete(ptr,k);
            break;

            case'i':
            list_delete_first(ptr);
            break;

            case'l':
            list_delete_last(ptr);
            break;

            case'p':
            print_list(ptr);
            break;

            case'e':
            return 0;
       
        }
    }
}