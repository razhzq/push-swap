#include "pushswap.h"
#include <stdlib.h> 
#include <stdio.h>
#include <limits.h>

// Helper to get a sorted copy of the stack for rank/median calculation
int	*get_sorted_copy(int *arr, int len)
{
	int *sorted;
	int i;
	int j;
	int temp;

	sorted = malloc(sizeof(int) * len);
	if (!sorted)
		return (NULL);
	
	i = 0;
	while (i < len)
	{
		sorted[i] = arr[i];
		i++;
	}
	
	// Sort array using bubble sort (or any stable sort)
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
	return (sorted);
}

// Get the median value from the array
int get_median(int *arr, int len)
{
    int *sorted;
    int median;

    sorted = get_sorted_copy(arr, len);
    if (!sorted)
        return (0);
    
    median = sorted[(len - 1) / 2];
    free(sorted);
    return (median);
}

// Counts numbers in a single string (handles "1 2 3" or just "1")
static int count_numbers_in_string(char *str)
{
    int count = 0;
    char *ptr = str;
    while (*ptr)
    {
        while (*ptr == ' ') // skip spaces
            ptr++;
        if (*ptr)
        {
            count++;
            while (*ptr && *ptr != ' ')
                ptr++;
        }
    }
    return count;
}

// Parses arguments, checks for errors (non-integer, limits, duplicates), and returns length
int parse_args(int argc, char **argv, int **a)
{
    int total = 0;
    int num_count = 0;

    // Pass 1: count total numbers
    for (int i = 1; i < argc; i++)
        num_count += count_numbers_in_string(argv[i]);

    *a = malloc(sizeof(int) * num_count);
    if (!*a)
        return (0);

    // Pass 2: parse numbers and check limits/invalid chars
    for (int i = 1; i < argc; i++)
    {
        char *ptr = argv[i];
        while (*ptr)
        {
            while (*ptr == ' ')
                ptr++;
            if (*ptr == '\0')
                break;

            char *endptr;
            // Use long to check for overflow outside INT_MIN/INT_MAX
            long val = strtol(ptr, &endptr, 10); 

            // Check 1: If strtol read anything AND if the string isn't just a number followed by trash
            if (endptr == ptr || (*endptr != '\0' && *endptr != ' ')) 
            {
                free(*a);
                *a = NULL;
                return (-1); // Invalid char/format
            }

            // Check 2: INT range check
            if (val < INT_MIN || val > INT_MAX) 
            {
                free(*a);
                *a = NULL;
                return (-2); // Integer limits exceeded
            }

            (*a)[total++] = (int)val;
            ptr = endptr;
        }
    }

    // Check 3: Duplicates
    for (int i = 0; i < total; i++)
    {
        for (int j = i + 1; j < total; j++)
        {
            if ((*a)[i] == (*a)[j])
            {
                free(*a);
                *a = NULL;
                return (-3); // Duplicates found
            }
        }
    }

    return (total);
}

// The instruction functions (must write to STDOUT)
// NOTE: You must define these yourself if they are not in a separate instruction.c file.
// Example:
/*
void	swap_a(int *a, int len)
{
    if (len < 2) return;
    int temp = a[0];
    a[0] = a[1];
    a[1] = temp;
    write(1, "sa\n", 3);
}
// ... and so on for all 11 required instructions.
*/