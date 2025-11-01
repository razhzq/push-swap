#include <stdio.h>
#include "pushswap.h"
#include <math.h>
#include <limits.h>

// Global counter for operations
int op_count = 0;

void print_stacks(int *a, int *b, int len_a, int len_b)
{
    printf("Stack A: ");
    for (int i = 0; i < len_a; i++)
        printf("%d ", a[i]);
    printf("\nStack B: ");
    for (int i = 0; i < len_b; i++)
        printf("%d ", b[i]);
    printf("\n\n");
}

void push_swap_sort_b(int *a, int *b, int *len_a, int *len_b, int size)
{
    if (size <= 3)
    {
        printf("Sorting small stack B\n");
        sort_small_stack_b(b, size);
        print_stacks(a, b, *len_a, *len_b);
        int to_push = size;
        for (int i = 0; i < to_push; i++)
        {
            push_a(&a, &b, len_a, len_b);
            print_stacks(a, b, *len_a, *len_b);
        }
        return;
    }

    int pivot = get_median(b, size);
    int pushed = 0;
    int rotated = 0;
    int total = size;
    int i = 0;
    printf("Pivot for B: %d\n", pivot);

    while (i < total)
    {
        if (b[0] > pivot)
        {
            push_a(&a, &b, len_a, len_b);
            pushed++;
        }
        else
        {
            rotate_b(b, *len_b);
            rotated++;
        }
        print_stacks(a, b, *len_a, *len_b);
        i++;
    }
    i = 0;
    while (i < rotated)
    {
        rotate_reverse_b(b, *len_b);
        print_stacks(a, b, *len_a, *len_b);
        i++;
    }

    if (pushed > 3)
        push_swap_sort_a(a, b, len_a, len_b, pushed);
    else if (pushed > 0)
        sort_small_stack_a(a, pushed);

    if (size - pushed > 3)
        push_swap_sort_b(a, b, len_a, len_b, size - pushed);
    else if (size - pushed > 0)
        sort_small_stack_b(b, size - pushed);
}

void push_swap_sort_a(int *a, int *b, int *len_a, int *len_b, int size)
{
    if (size <= 3)
    {
        printf("Sorting small stack A\n");
        sort_small_stack_a(a, size);
        print_stacks(a, b, *len_a, *len_b);
        return;
    }

    int pivot = get_median(a, size);
    int pushed = 0;
    int rotated = 0;
    int total = size;
    int i = 0;
    printf("Pivot for A: %d\n", pivot);

    while (i < total)
    {
        if (a[0] < pivot)
        {
            push_b(&a, &b, len_a, len_b);
            pushed++;
        }
        else
        {
            rotate_a(a, *len_a);
            rotated++;
        }
        print_stacks(a, b, *len_a, *len_b);
        i++;
    }

    i = 0;
    while (i < rotated)
    {
        rotate_reverse_a(a, *len_a);
        print_stacks(a, b, *len_a, *len_b);
        i++;
    }

    if (size - pushed > 3)
        push_swap_sort_a(a, b, len_a, len_b, size - pushed);
    else if (size - pushed > 0)
        sort_small_stack_a(a, size - pushed);

    if (pushed > 3)
        push_swap_sort_b(a, b, len_a, len_b, pushed);
    else if (pushed > 0)
        sort_small_stack_b(b, pushed);
}

// // Helper: find the index of a value in an array
// static int find_index(int *arr, int len, int value) {
//     for (int i = 0; i < len; i++)
//         if (arr[i] == value)
//             return i;
//     return -1;
// }

// // Greedy: find the best element in B to push to A (minimal moves)
// static int find_best_b_to_a(int *b, int len_b) {
//     // For simplicity, just return the max in B (can be improved)
//     int max = b[0];
//     int idx = 0;
//     int i = 0;
//     while (i < len_b)
//     {
//         if (b[i] > max)
//         {
//             max = b[i];
//             idx = i;
//         }
//         i++;
//     }
//     return idx;
// }

// Basic 3-element sorter for stack A
static void sort_3_elements(int *a)
{
    if (a[0] > a[1] && a[1] < a[2] && a[0] < a[2])
    {
        // Case 2 1 3
        swap_a(a, 3);
    }
    else if (a[0] > a[1] && a[1] > a[2])
    {
        // Case 3 2 1
        swap_a(a, 3);
        rotate_reverse_a(a, 3);
    }
    else if (a[0] > a[1] && a[1] < a[2] && a[0] > a[2])
    {
        // Case 3 1 2
        rotate_a(a, 3);
    }
    else if (a[0] < a[1] && a[1] > a[2] && a[0] < a[2])
    {
        // Case 1 3 2
        swap_a(a, 3);
        rotate_a(a, 3);
    }
    else if (a[0] < a[1] && a[1] > a[2] && a[0] > a[2])
    {
        // Case 2 3 1
        rotate_reverse_a(a, 3);
    }
    // Case 1 2 3 is already sorted
}

// Optimized version of pushswap_chunk_sort that uses fewer operations
void pushswap_chunk_sort(int *a, int *b, int *len_a, int *len_b, int chunk_count)
{
    int total = *len_a;

    // For very small arrays (3 or fewer), use specialized sort
    if (total <= 3)
    {
        if (total == 2 && a[0] > a[1])
        {
            swap_a(a, 2);
        }
        else if (total == 3)
        {
            sort_3_elements(a);
        }
        return;
    }

    // Get a sorted copy to determine thresholds
    int *sorted = get_sorted_copy(a, total);
    if (!sorted)
        return;

    // For small arrays (4-15), use optimized small sort
    if (total <= 15)
    {
        // Push all except 3 largest elements to B
        while (*len_a > 3)
        {
            // Find the smallest element and push it to B
            int min_idx = 0;
            int min_val = a[0];

            for (int i = 1; i < *len_a; i++)
            {
                if (a[i] < min_val)
                {
                    min_val = a[i];
                    min_idx = i;
                }
            }

            // Move min to top and push to B
            if (min_idx <= *len_a / 2)
            {
                for (int i = 0; i < min_idx; i++)
                {
                    rotate_a(a, *len_a);
                }
            }
            else
            {
                for (int i = 0; i < *len_a - min_idx; i++)
                {
                    rotate_reverse_a(a, *len_a);
                }
            }

            push_b(&a, &b, len_a, len_b);
        }

        // Sort the remaining 3 elements in A
        sort_3_elements(a);

        // Push everything back from B to A in reverse order (smallest first)
        while (*len_b > 0)
        {
            push_a(&a, &b, len_a, len_b);
        }

        free(sorted);
        return;
    }

    // Simplified chunk algorithm: push to B in chunks
    int chunk_size = total / chunk_count;

    // Phase 1: Push elements to B in chunks (smallest to largest)
    for (int chunk = 0; chunk < chunk_count; chunk++)
    {
        int chunk_min = chunk * chunk_size;
        int chunk_max = (chunk == chunk_count - 1) ? total - 3 : (chunk + 1) * chunk_size;

        // Push all elements in this chunk range
        int initial_len = *len_a;
        for (int scanned = 0; scanned < initial_len && *len_a > 3; scanned++)
        {
            // Find rank of a[0]
            int rank = -1;
            for (int j = 0; j < total; j++)
            {
                if (a[0] == sorted[j])
                {
                    rank = j;
                    break;
                }
            }

            // If in current chunk range, push to B
            if (rank >= chunk_min && rank < chunk_max)
            {
                push_b(&a, &b, len_a, len_b);

                // Rotate B strategically: only if element is small AND next element is larger
                if (*len_b >= 2 && rank < chunk_min + chunk_size / 2 && b[1] > b[0])
                {
                    rotate_b(b, *len_b);
                }
            }
            else
            {
                rotate_a(a, *len_a);
            }
        }
    }

    // Sort remaining 3 in A
    if (*len_a == 3)
        sort_3_elements(a);
    else if (*len_a == 2 && a[0] > a[1])
        swap_a(a, 2);

    // Phase 2: Push everything back from B to A with optimized rotations
    while (*len_b > 0)
    {
        // Find max in B
        int max_idx = 0;
        int max_val = b[0];
        for (int i = 1; i < *len_b; i++)
        {
            if (b[i] > max_val)
            {
                max_val = b[i];
                max_idx = i;
            }
        }

        // Find insertion point in A for max_val
        int insert_pos = 0;
        for (int i = 0; i < *len_a; i++)
        {
            if (max_val > a[i])
                insert_pos = i + 1;
        }

        // Handle wrap-around
        if (insert_pos == *len_a)
        {
            int min_idx = 0;
            for (int i = 1; i < *len_a; i++)
            {
                if (a[i] < a[min_idx])
                    min_idx = i;
            }
            insert_pos = min_idx;
        }

        // Calculate rotation directions and costs
        int b_rotate_forward = (max_idx <= *len_b / 2);
        int b_cost = b_rotate_forward ? max_idx : (*len_b - max_idx);
        int a_rotate_forward = (insert_pos <= *len_a / 2);
        int a_cost = a_rotate_forward ? insert_pos : (*len_a - insert_pos);

        // Perform simultaneous rotations when both go same direction
        if (b_rotate_forward && a_rotate_forward)
        {
            int simultaneous = (b_cost < a_cost) ? b_cost : a_cost;
            for (int i = 0; i < simultaneous; i++)
                rotate_multi_stack(&a, &b, len_a, len_b);
            for (int i = 0; i < b_cost - simultaneous; i++)
                rotate_b(b, *len_b);
            for (int i = 0; i < a_cost - simultaneous; i++)
                rotate_a(a, *len_a);
        }
        else if (!b_rotate_forward && !a_rotate_forward)
        {
            int simultaneous = (b_cost < a_cost) ? b_cost : a_cost;
            for (int i = 0; i < simultaneous; i++)
                rotate_reverse_multi_stack(&a, &b, len_a, len_b);
            for (int i = 0; i < b_cost - simultaneous; i++)
                rotate_reverse_b(b, *len_b);
            for (int i = 0; i < a_cost - simultaneous; i++)
                rotate_reverse_a(a, *len_a);
        }
        else
        {
            // Different directions - rotate separately
            if (b_rotate_forward)
            {
                for (int i = 0; i < b_cost; i++)
                    rotate_b(b, *len_b);
            }
            else
            {
                for (int i = 0; i < b_cost; i++)
                    rotate_reverse_b(b, *len_b);
            }

            if (a_rotate_forward)
            {
                for (int i = 0; i < a_cost; i++)
                    rotate_a(a, *len_a);
            }
            else
            {
                for (int i = 0; i < a_cost; i++)
                    rotate_reverse_a(a, *len_a);
            }
        }

        push_a(&a, &b, len_a, len_b);
    }

    // Rotate to put min at top
    int min_idx = 0;
    for (int i = 1; i < *len_a; i++)
    {
        if (a[i] < a[min_idx])
            min_idx = i;
    }

    if (min_idx <= *len_a / 2)
    {
        for (int i = 0; i < min_idx; i++)
            rotate_a(a, *len_a);
    }
    else
    {
        for (int i = 0; i < *len_a - min_idx; i++)
            rotate_reverse_a(a, *len_a);
    }

    free(sorted);
}

void pushswap(int *a, int len_a)
{
    int *b;
    int len_b;
    int chunk_count;

    if (!a || len_a <= 0)
        return;

    len_b = 0;
    b = malloc(sizeof(int) * len_a);
    if (!b)
    {
        free(a);
        return;
    }
    if (len_a <= 3)
        chunk_count = 1; // Use simple sort for 3 or fewer elements
    else if (len_a <= 10)
        chunk_count = 2; // For small arrays, use 2 chunks
    else if (len_a <= 100)
        chunk_count = 5; // Optimized for 100 elements: 5 chunks gives ~630 operations
    else if (len_a <= 500)
        chunk_count = 10; // For 500 elements: 10 chunks with optimized Phase 2
    else
        chunk_count = (int)(sqrt(len_a) * 1.2); // More chunks for large arrays

    if (len_a <= 3)
        sort_small_stack_a(a, len_a);
    else
    {
        // Use chunk sort for all arrays > 3 elements
        pushswap_chunk_sort(a, b, &len_a, &len_b, chunk_count);
    }

    // Print final sorted stack A for validation
    printf("\nFinal sorted Stack A (len=%d): ", len_a);
    for (int i = 0; i < len_a; i++)
        printf("%d ", a[i]);
    printf("\n");

    printf("Total operations: %d\n", op_count);
    free(a);
    free(b);
}

int main(int argc, char **argv)
{
    int *a;
    int len_a;

    if (argc < 2)
    {
        printf("Error: No arguments provided\n");
        return 1;
    }

    len_a = parse_args(argc, argv, &a);
    if (len_a <= 0 || !a)
    {
        printf("Error: Invalid arguments\n");
        return 1;
    }

    // Debug print
    printf("main: len_a = %d\n", len_a);
    for (int i = 0; i < len_a; i++)
        printf("main: a[%d] = %d\n", i, a[i]);

    pushswap(a, len_a);
    return 0;
}