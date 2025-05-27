#include "pushswap.h"

int get_median(int *arr, int len)
{
    int *sorted;
    int i;
    int j;
    int temp;
    int median;

    sorted = malloc(sizeof(int) * len);
    if (!sorted)
        return 0;
    
    // Copy array to avoid modifying original
    i = 0;
    while (i < len)
    {
        sorted[i] = arr[i];
        i++;
    }
    
    // Sort array using bubble sort
    i = 0;
    while (i < len - 1)
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (sorted[j] > sorted[j + 1])
            {
                temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    
    // Get median
    median = sorted[(len - 1) / 2];
    free(sorted);
    return median;
}

int parse_args(int argc, char **argv, int **a)
{
    int i;
    if (argc < 2)
    {
        *a = NULL;
        return 0;
    }
    *a = malloc(sizeof(int) * (argc - 1));
    if (!*a)
        return 0;
    i = 1;
    while (i < argc)
    {
        (*a)[i - 1] = ft_atoi(argv[i]);
        i++;
    }
    // Debug print
    printf("parse_args: parsed %d numbers: ", argc - 1);
    for (int j = 0; j < argc - 1; j++)
        printf("%d ", (*a)[j]);
    printf("\n");
    return argc - 1;
}

void sort_small_stack_a(int *a, int len)
{
    if (len == 2) {
        if (a[0] > a[1]) {
            swap_a(a, len);
        }
    }
    else if (len == 3) {
        if (a[0] > a[1] && a[1] < a[2] && a[0] < a[2]) {
            swap_a(a, len);
        }
        else if (a[0] > a[1] && a[1] > a[2]) {
            swap_a(a, len);
            rotate_reverse_a(a, len);
        }
        else if (a[0] > a[1] && a[1] < a[2] && a[0] > a[2]) {
            rotate_a(a, len);
        }
        else if (a[0] < a[1] && a[1] > a[2] && a[0] < a[2]) {
            swap_a(a, len);
            rotate_a(a, len);
        }
        else if (a[0] < a[1] && a[1] > a[2] && a[0] > a[2]) {
            rotate_reverse_a(a, len);
        }
    }
}

void sort_small_stack_b(int *b, int len)
{
    if (len == 2) {
        if (b[0] < b[1]) {
            swap_b(b, len);
        }
    }
    else if (len == 3) {
        if (b[0] < b[1] && b[1] > b[2] && b[0] > b[2]) {
            swap_b(b, len);
        }
        else if (b[0] < b[1] && b[1] < b[2]) {
            swap_b(b, len);
            rotate_reverse_b(b, len);
        }
        else if (b[0] < b[1] && b[1] > b[2] && b[0] < b[2]) {
            rotate_b(b, len);
        }
        else if (b[0] > b[1] && b[1] < b[2] && b[0] < b[2]) {
            swap_b(b, len);
            rotate_b(b, len);
        }
        else if (b[0] > b[1] && b[1] < b[2] && b[0] > b[2]) {
            rotate_reverse_b(b, len);
        }
    }
}

// Returns a sorted copy of the array (ascending order)
int *get_sorted_copy(int *arr, int len)
{
    int *sorted = malloc(sizeof(int) * len);
    if (!sorted)
        return NULL;
    for (int i = 0; i < len; i++)
        sorted[i] = arr[i];
    // Bubble sort (can be replaced with better sort if needed)
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    return sorted;
}