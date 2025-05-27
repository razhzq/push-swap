#include "stackops.h"

void rotate_reverse_a(int *a, int len)
{
    printf("rra\n");
    int last;
    int i;

    if (len < 2)
        return;

    last = a[len - 1];
    i = len - 1;
    while (i > 0)
    {
        a[i] = a[i - 1];
        i--;
    }
    a[0] = last;
    op_count++;
}

void rotate_reverse_b(int *b, int len)
{
    printf("rrb\n");
    int last;
    int i;

    if (len < 2)
        return;

    last = b[len - 1];
    i = len - 1;
    while (i > 0)
    {
        b[i] = b[i - 1];
        i--;
    }
    b[0] = last;
    op_count++;
}

void rotate_reverse_multi_stack(int **a, int **b, int *len_a, int *len_b)
{
    printf("rrr\n");
    if (*len_a < 2 || *len_b < 2)
        return;
        
    // Rotate reverse stack A
    int last_a = (*a)[*len_a - 1];
    int i = *len_a - 1;
    while (i > 0)
    {
        (*a)[i] = (*a)[i - 1];
        i--;
    }
    (*a)[0] = last_a;
    
    // Rotate reverse stack B
    int last_b = (*b)[*len_b - 1];
    i = *len_b - 1;
    while (i > 0)
    {
        (*b)[i] = (*b)[i - 1];
        i--;
    }
    (*b)[0] = last_b;
    
    op_count++;
}