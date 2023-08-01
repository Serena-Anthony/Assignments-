// split into 4 groups 
//h(A) = (Sum of ASCII value of the characters in the first name of ‘A’ + age of ‘A’) % 4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    char name[100];
    char roll[100];
    int age; 
    struct student* next;
    // cuz we creating linked list
};

int hash(char a[], int age)
{
    int sum=0;
    for (int i=0; a[i]!= '\0'; i++)
    {
        sum = sum + a[i];
    }
    int temp =0;
    temp = (sum + age)%4 ;
   // printf(" HASHED\n");
    return temp;
}

void insert(struct student *arr[], struct student* temp, int hash)
{
    // tail insertion of linked list
    // elemnt inserted as next not in between
    struct student* bleh= arr[hash];
    if(bleh != NULL)
    {
        while(bleh->next != NULL)
        {
            bleh = bleh->next;
        }
        bleh->next = temp;
    }
    else
    {
        arr[hash] = temp;
    }
}

void count(int index, struct student *arr[])
{
    struct student* temp = arr[index];
    struct student* bleh = arr[index];
    int num =0;
    
    if(temp != NULL)
    {
        while( temp != NULL)
        {
            num++;
            temp = temp->next;
        }
        printf("%d ", num);
        
        while( bleh != NULL)
        {
        printf("%s ", bleh-> name);
        bleh=bleh->next;
        }
        printf("\n");
    }

    else
    {
        printf("0\n");
    }
}

void compare(struct student *arr[], int grp, char b[] )
{
    struct student* compare = arr[grp];
    int flag =0;

    while(compare!= NULL)
    {
        char cmp[100];
        for(int i =0; i<100; i++)
        {
            cmp[i]= '\0';
        }
        cmp[0] = compare->roll[7];
        cmp[1] = compare->roll[8];

        int COMP = strcmp(b,cmp);

        if (COMP == 0)
        {
            printf("%s ", compare->name);
            flag =1;
        }
        compare = compare->next;
    }
    
    if(flag == 0)
    {
        printf("-1");
    }
    printf("\n");
}

int main()
{
    int n; // no of students in event
    scanf("%d", &n);
    struct student*  arr[4];
    for(int i=0; i<4;i++)
    {
        arr[i]= NULL;
    }

    for(int i=0; i<n;i++)
    {
        struct student* temp = (struct student*)malloc(sizeof(struct student));
        scanf("%s %s %d", temp->name ,temp->roll, &temp->age);
        temp->next = NULL;
       
        int check = hash(temp->name, temp->age); // grp in which they r in 
        insert(arr, temp, check);   
    }

    char ch;
    int k;
    while(1)
    {
        getchar();
        
        scanf("%c", &ch);
        
        if(ch == 'c')
        {
            scanf("%d", &k);
            count(k,arr);
        }
        else if( ch == 'e')
        {
            break;
        }
        else
        {
            int temp;
                    temp = ch -48;
                    // temp is the group number

                    char b[100];
                    for(int i =0; i<100; i++)
                    {
                        b[i]= '\0';
                    }
                    scanf("%s", b);

                    for(int i =0; b[i]!= '\0'; i++)
                    {
                    if( b[i]<=122 && b[i] >=97)
                     // means it is lowercase.. need to sub 32
                     {
                        b[i] = b[i]-32; 
                     }
                     // got char in uppercase
                    }
                    compare(arr, temp , b);
        }
    }
}