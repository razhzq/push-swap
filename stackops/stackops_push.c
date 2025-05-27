#include "stackops.h"

void push_a(int **a, int **b, int *len_a, int *len_b)
{
    printf("pa\n");
    int temp;
    int i;
    if (*len_b == 0)
        return;

    // Save the value to be pushed
    temp = (*b)[0];
    
    // Shift elements in stack B
    i = 0;
    while (i < *len_b - 1)
    {
        (*b)[i] = (*b)[i + 1];
        i++;
    }
    
    // Shift elements in stack A to make room
    i = *len_a;
    while (i > 0)
    {
        (*a)[i] = (*a)[i - 1];
        i--;
    }
    
    // Place the value at the top of stack A
    (*a)[0] = temp;
    
    // Update lengths
    (*len_a)++;
    (*len_b)--;
    op_count++;
}

void push_b(int **a, int **b, int *len_a, int *len_b)
{
    printf("pb\n");
    int temp;
    int i;
    if (*len_a == 0)
        return;

    // Save the value to be pushed
    temp = (*a)[0];
    
    // Shift elements in stack A
    i = 0;
    while (i < *len_a - 1)
    {
        (*a)[i] = (*a)[i + 1];
        i++;
    }
    
    // Shift elements in stack B to make room
    i = *len_b;
    while (i > 0)
    {
        (*b)[i] = (*b)[i - 1];
        i--;
    }
    
    // Place the value at the top of stack B
    (*b)[0] = temp;
    
    // Update lengths
    (*len_b)++;
    (*len_a)--;
    op_count++;
}

void rotate_a(int *a, int len)
{
    printf("ra\n");
    int first;
    int i;
    if (len < 2)
        return;

    first = a[0];
    i = 0;
    while (i < len - 1)
    {
        a[i] = a[i + 1];
        i++;
    }
    a[len - 1] = first;
    op_count++;
}

void rotate_b(int *b, int len)
{
    printf("rb\n");
    int first;
    int i;
    if (len < 2)
        return;

    first = b[0];
    i = 0;
    while (i < len - 1)
    {
        b[i] = b[i + 1];
        i++;
    }
    b[len - 1] = first;
    op_count++;
}

void rotate_multi_stack(int **a, int **b, int *len_a, int *len_b)
{
    printf("rr\n");
    if (*len_a < 2 || *len_b < 2)
        return;
        
    // Rotate stack A
    int first_a = (*a)[0];
    int i = 0;
    while (i < *len_a - 1)
    {
        (*a)[i] = (*a)[i + 1];
        i++;
    }
    (*a)[*len_a - 1] = first_a;
    
    // Rotate stack B
    int first_b = (*b)[0];
    i = 0;
    while (i < *len_b - 1)
    {
        (*b)[i] = (*b)[i + 1];
        i++;
    }
    (*b)[*len_b - 1] = first_b;
    
    op_count++;
}
