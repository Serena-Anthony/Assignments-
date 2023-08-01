#include<stdio.h>

struct heap
{
    int a[100000];
    int len;
};

int decrease_key(struct heap *H, int z, int y)
{
    int i;
    for (i = 0; i < H->len; i++)
    {
        if (H->a[i] == z)
        {
            H->a[i] = y;
            //printf("%d\n", y);
            break;
        }
    }
    if(y >= z)
    {
       // printf("-1\n");
       return 2;
    }
    //printf("%d", i);
    while (i > 0 && H->a[(i - 1) / 2] > H->a[i])
    {
        int temp = H->a[(i - 1) / 2];
        H->a[(i - 1) / 2] = H->a[i];
        H->a[i] = temp;
        i = (i - 1) / 2;
    }
}

void insert(struct heap *H, int k)
{
    H->a[H->len] = k;
    int ptr = H->len;
    H->len++;

    while (ptr > 0 && H->a[(ptr - 1) / 2] > H->a[ptr])
    {
        int temp = H->a[ptr];
        H->a[ptr] = H->a[(ptr - 1) / 2];
        H->a[(ptr - 1) / 2] = temp;
        ptr = (ptr - 1) / 2;
    }
}

void min_heapify(struct heap *H, int index)
{
    int smallest = index;
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    if (left < H->len && H->a[left] < H->a[smallest])
    {
        smallest = left;
    }
    if (right < H->len && H->a[right] < H->a[smallest])
    {
        smallest = right;
    }
    if (smallest != index)
    {
        int temp = H->a[smallest];
        H->a[smallest] = H->a[index];
        H->a[index] = temp;
        min_heapify(H, smallest);
    }
}

int find_min(struct heap *H)
{
    return H->a[0];
}

int extract_min(struct heap *H)
{
    int min = H->a[0];
    H->a[0] = H->a[H->len - 1];
    H->len--;
    min_heapify(H, 0);
    return min;
}

int delete(struct heap *H, int key)
{
    decrease_key(H, key, -100000);
    extract_min(H);
   // printf("%d\n", temp);
}

void print_heap(struct heap *H)
{
    for (int i = 0; i < H->len; i++)
    {
        printf("%d ", H->a[i]);
    }
    printf("\n");
}

int main()
{
    struct heap *H,h;
    H= &h;
    H->len = 0;

    for (int i = 0; i < 100000; i++)
    {
        H->a[i] = '\0';
    }

    while (1)
    {
        char ch;
        scanf("%c", &ch);

        if (ch == 'i')
        {
            int k;
            scanf("%d", &k);
            insert(H, k);
        }
        if (ch == 'p')
        {
            print_heap(H);
        }
        if (ch == 'x')
        {
            extract_min(H);
            print_heap(H);
        }
        if (ch == 'r')
        {
            int y,z;
            scanf("%d%d", &z, &y);
            int temp = decrease_key(H, z, y);
            if(temp != 2)
            {
                printf("%d\n", y);
            }
            else
            {
                printf("-1\n");
            }
        }
        if (ch == 'd')
        {
            int k;
            scanf("%d", &k);
            delete (H, k);
            printf("%d\n", k);
        }
        if (ch == 'g')
        {
            int temp = find_min(H);
            printf("%d\n", temp);
        }
        if (ch == 'e')
        {
            break;
        }
    }
}