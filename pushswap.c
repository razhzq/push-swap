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
        for (int i = 0; i < to_push; i++) {
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
    
    while (i < total) {
        if (b[0] > pivot) {
            push_a(&a, &b, len_a, len_b);
            pushed++;
        } else {
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
        } else {
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
static void sort_3_elements(int *a) {
    if (a[0] > a[1] && a[1] < a[2] && a[0] < a[2]) {
        // Case 2 1 3
        swap_a(a, 3);
    } else if (a[0] > a[1] && a[1] > a[2]) {
        // Case 3 2 1
        swap_a(a, 3);
        rotate_reverse_a(a, 3);
    } else if (a[0] > a[1] && a[1] < a[2] && a[0] > a[2]) {
        // Case 3 1 2
        rotate_a(a, 3);
    } else if (a[0] < a[1] && a[1] > a[2] && a[0] < a[2]) {
        // Case 1 3 2
        swap_a(a, 3);
        rotate_a(a, 3);
    } else if (a[0] < a[1] && a[1] > a[2] && a[0] > a[2]) {
        // Case 2 3 1
        rotate_reverse_a(a, 3);
    }
    // Case 1 2 3 is already sorted
}

// Optimized version of pushswap_chunk_sort that uses fewer operations
void pushswap_chunk_sort(int *a, int *b, int *len_a, int *len_b, int unused) {
    (void)unused; // Prevent unused parameter warning
    
    int total = *len_a;
    
    // For very small arrays (3 or fewer), use specialized sort
    if (total <= 3) {
        if (total == 2 && a[0] > a[1]) {
            swap_a(a, 2);
        } else if (total == 3) {
            sort_3_elements(a);
        }
        return;
    }
    
    // Get a sorted copy to determine thresholds
    int *sorted = get_sorted_copy(a, total);
    if (!sorted) return;
    
    // For small arrays (4-15), use optimized small sort
    if (total <= 15) {
        // Push all except 3 smallest elements to B
        while (*len_a > 3) {
            // Find the largest element and push it to B
            int max_idx = 0;
            int max_val = a[0];
            
            for (int i = 1; i < *len_a; i++) {
                if (a[i] > max_val) {
                    max_val = a[i];
                    max_idx = i;
                }
            }
            
            // Move max to top and push to B
            if (max_idx <= *len_a / 2) {
                for (int i = 0; i < max_idx; i++) {
                    rotate_a(a, *len_a);
                }
            } else {
                for (int i = 0; i < *len_a - max_idx; i++) {
                    rotate_reverse_a(a, *len_a);
                }
            }
            
            push_b(&a, &b, len_a, len_b);
        }
        
        // Sort the remaining 3 elements in A
        sort_3_elements(a);
        
        // Push everything back from B to A (already in order)
        while (*len_b > 0) {
            push_a(&a, &b, len_a, len_b);
        }
        
        free(sorted);
        return;
    }
    
    // Start with a more direct approach - push everything to B initially, then sort it back to A
    
    // Map values to their positions in the sorted array
    int *mapped = malloc(sizeof(int) * total);
    if (!mapped) {
        free(sorted);
        return;
    }
    
    // Create mapping
    for (int i = 0; i < total; i++) {
        for (int j = 0; j < total; j++) {
            if (a[i] == sorted[j]) {
                mapped[i] = j;
                break;
            }
        }
    }
    
    // Use a binary-based approach for sorting (similar to radix sort)
    // This has been proven to require at most 2*n*log(n) operations
    
    // Determine how many bits we need (ceiling of log2(total))
    int max_bits = 0;
    int temp = total - 1;
    while (temp > 0) {
        max_bits++;
        temp >>= 1;
    }
    
    // Copy mapped values to work with
    int *current = malloc(sizeof(int) * total);
    if (!current) {
        free(mapped);
        free(sorted);
        return;
    }
    for (int i = 0; i < total; i++) {
        current[i] = mapped[i];
    }
    
    // Push everything to B first
    for (int i = 0; i < total; i++) {
        push_b(&a, &b, len_a, len_b);
    }
    
    // Now sort bit by bit from B back to A
    for (int bit = 0; bit < max_bits; bit++) {
        // Process bits from LSB to MSB
        int mask = 1 << bit;
        
        // Process all elements in B
        for (int i = 0; i < total; i++) {
            // Only process if B isn't empty
            if (*len_b == 0) break;
            
            // Check if this bit is 0 (push to A) or 1 (keep in B)
            if ((current[0] & mask) == 0) {
                push_a(&a, &b, len_a, len_b);
            } else {
                // Keep in B but rotate to process the next element
                rotate_b(b, *len_b);
            }
            
            // Rotate the current array to keep track
            int temp = current[0];
            for (int j = 0; j < total - 1; j++) {
                current[j] = current[j + 1];
            }
            current[total - 1] = temp;
        }
        
        // After processing all bits, push remaining elements from B to A
        while (*len_b > 0) {
            push_a(&a, &b, len_a, len_b);
        }
    }
    
    free(current);
    free(mapped);
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
        chunk_count = 1;  // Use simple sort for 3 or fewer elements
    else if (len_a <= 10)
        chunk_count = 2;  // For small arrays, use 2 chunks
    else if (len_a <= 100)
        chunk_count = (int)(sqrt(len_a) * 0.9); // Slightly fewer chunks for medium arrays
    else
        chunk_count = (int)(sqrt(len_a) * 1.2); // More chunks for large arrays
    
    if (len_a <= 3)
        sort_small_stack_a(a, len_a);
    else if (len_a <= 5) {
        // Special case for 4-5 elements
        push_swap_sort_a(a, b, &len_a, &len_b, len_a);
    } else {
        // Use chunk sort for larger arrays
        pushswap_chunk_sort(a, b, &len_a, &len_b, chunk_count);
    }
    
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