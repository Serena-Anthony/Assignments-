#include<stdio.h>

struct student
{
    char name[100];
    int mark;
};

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapp(char str1[], char str2[])
{
    int temp[50];
    int count=0;
    
    for(int j=0;str2[j] !='\0'; j++)
    {
        for( int i=0; str1[i]!='\0'; i++)
        {
            temp[i] = str1[count] ;
            str1[count] = str2[count];
            str2[count] = temp[i];
            count++;
        }
    }
}

char compare(char a[],char b[])  
{  
    int flag=0, i=0; 
    while(a[i]!='\0' && b[i]!='\0')   
    {  
      if(a[i]!=b[i])  
      {  
          flag=1;  
          break;  
      }  
      i++;  
    }  
    if(flag==0)  
    return 0;  
    else  
    return 1;  
}

void partition (struct student s[],int index, int low, int high)
 {

    int i= low-1;
    int pivot = s[index].mark;
    
    for(int j=low; j<high; j++)
    {
        if (s[j].mark<=pivot && j!=index)
        {
            i++;
            if(i==index)
            { index= j;}
            
            swap(&s[i].mark, &s[j].mark);
            swapp(s[i].name, s[j].name);
      }
    }
    swap(&s[i+1].mark, &s[index].mark);
    swapp(s[i+1].name, s[index].name);
 }

int main()
{
    int n;
    scanf("%d", &n);
    struct student s[n];
   
    for (int i=0; i<n; i++)
    {
        scanf("%s %d", s[i].name, &s[i].mark);
    }

    char CR[30];
    scanf("%s", CR);
    int index;
    
        for (int i=0; i<n; i++)
    {
        int c= compare(s[i].name,CR);
        if (c==0)
        {
            index =i;
            break;
        } 
    }
    
 partition(s,index, 0, n);

 for (int i = 0; i < n; i++)
    {printf("%s ", s[i].name);}
    return 0;
}