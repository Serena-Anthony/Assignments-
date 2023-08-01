#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    int rank;
    struct node* parent;
};

struct node* makeset(int x)
{
    struct node* temp = (struct node*)malloc (sizeof(struct node));
    temp->data = x;
    temp->rank =0;
    temp->parent = temp;
   // printf("created\n");
    return temp;
}

struct node* findset(struct node* x, int *c)
{
    if(x!= NULL)
    {
        (*c)++;                   // *c = *c +1
        if(x->parent == x)
        {
            return x;
        }
        else
        {
            return findset(x->parent, c);
        }
    }
}

struct node* findset_pathcomp(struct node* x, int *c)
{
    if(x!= NULL)
    {
        (*c)++;                   // *c = *c +1
        if(x->parent == x)
        {
            return x;
        }
        else
        {
            x->parent = findset_pathcomp(x->parent, c);
            return x->parent;
        }
    }
}

struct node* link (struct node*a, struct node*b)
{
   // struct node*y,z;
   // z is made parent of y 
    b->parent = a;
    return a;
  //  printf("LINKED \n");
}

struct node* ranked_link(struct node*a, struct node* b)
{
    if (b->rank > a->rank)
    {
        a->parent = b;
        return b;
    }
    else
    {
        b->parent = a;
        if(a->rank == b->rank)
        {
            a->rank = a->rank +1 ;
        }
        return a;
    }
}

struct node* union_worst(struct node*x, struct node*y, int *ca)
{
    return link(findset(x,ca), findset(y,ca));
}

struct node* union_rank(struct node*x, struct node* y, int* cb)
{
    return ranked_link(findset(x,cb), findset(y,cb));
}

struct node* union_pathcomp(struct node*x, struct node* y, int* cc)
{
    return link(findset_pathcomp(x,cc), findset_pathcomp(y,cc));
}

struct node* union_both(struct node*x, struct node* y, int *cd)
{
    return ranked_link(findset_pathcomp(x,cd), findset_pathcomp(y,cd));
}

int main()
{
    struct node* A[10001];
    struct node* B[10001];
    struct node* C[10001];
    struct node* D[10001];

    int ca = 0;
    int cb = 0;
    int cc = 0;
    int cd = 0;
        
      while (1)
    {
        char ch;
        scanf("%c", &ch);

        if (ch == 'm')
        {
            int k;
            scanf("%d", &k);
            if(A[k] == NULL && B[k]==NULL && C[k]==NULL && D[k]==NULL)
            {
            A[k]= makeset(k);
            B[k]= makeset(k);
            C[k]= makeset(k);
            D[k]= makeset(k);
            printf("%d\n", k);
            }
            else
            {
                printf("-1\n");
            }
        }

        if (ch == 'u')
        {
            int a,b;
            scanf("%d %d", &a, &b);

            struct node* temp1, *temp2, *temp3, *temp4;
            temp1 = union_worst(A[a],A[b],&ca);
            temp2 = union_rank(B[a],B[b],&cb);
            temp3 = union_pathcomp(C[a],C[b],&cc);
            temp4 = union_both(D[a],D[b],&cd);

            printf("%d %d %d %d", temp1->data, temp2->data, temp3->data, temp4->data );
            printf("\n");
        }

        if (ch == 'f')
        {
            int k;
            scanf("%d", &k);
            struct node* temp1, *temp2, *temp3, *temp4;
            temp1 = findset(A[k], &ca);
            temp2 = findset(B[k], &cb);
            temp3 = findset_pathcomp(C[k], &cc);
            temp4 = findset_pathcomp(D[k], &cd);

            printf("%d %d %d %d ", temp1->data, temp2->data, temp3->data, temp4->data );
            printf("\n");
        }
           if (ch == 's')
        {
            printf("%d %d %d %d", ca, cb, cc, cd);
            break;
        }
    }
}