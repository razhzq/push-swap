#include "pushswap.h"
#include <stdlib.h> 
#include <stdio.h>
#include <limits.h>

// Max 25 lines, Max 4 args. OK.
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
	while (i < len) // Converted for to while
	{
		sorted[i] = arr[i];
		i++;
	}
	
	i = 0;
	while (i < len - 1) // Converted for to while
	{
		j = 0;
		while (j < len - i - 1) // Converted for to while
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

// Max 25 lines, Max 4 args. OK.
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

// Max 25 lines, Max 4 args. OK.
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

// NEW HELPER: Pass 1 - Count total numbers (Max 25 lines, 2 args)
static int count_total_numbers(int argc, char **argv)
{
	int num_count;
	int i;

	num_count = 0;
	i = 1;
	while (i < argc) // Converted for to while
	{
		num_count += count_numbers_in_string(argv[i]);
		i++;
	}
	return (num_count);
}

// NEW HELPER: Pass 2 - Parse and validate (Max 25 lines, 3 args)
static int parse_validate_and_fill(int argc, char **argv, int *a)
{
	int		total;
	int		i;
	char	*ptr;
	char	*endptr;
	long	val;

	total = 0;
	i = 1;
	while (i < argc) // Converted for to while
	{
		ptr = argv[i];
		while (*ptr)
		{
			while (*ptr == ' ')
				ptr++;
			if (*ptr == '\0')
				break ;
			val = strtol(ptr, &endptr, 10);
			if (endptr == ptr || (*endptr != '\0' && *endptr != ' '))
				return (-1); // Invalid char/format
			if (val < INT_MIN || val > INT_MAX)
				return (-2); // Integer limits exceeded
			a[total++] = (int)val;
			ptr = endptr;
		}
		i++;
	}
	return (total);
}

// NEW HELPER: Pass 3 - Check duplicates (Max 25 lines, 2 args)
static int check_for_duplicates(int *a, int total)
{
	int i;
	int j;

	i = 0;
	while (i < total) // Converted for to while
	{
		j = i + 1;
		while (j < total) // Converted for to while
		{
			if (a[i] == a[j])
				return (-3); // Duplicates found
			j++;
		}
		i++;
	}
	return (0);
}

// Refactored Wrapper (Max 25 lines, 3 args)
int parse_args(int argc, char **argv, int **a)
{
	int num_count;
	int total;
	int check;

	num_count = count_total_numbers(argc, argv);
	if (num_count == 0)
		return (0);

	*a = malloc(sizeof(int) * num_count);
	if (!*a)
		return (0);

	total = parse_validate_and_fill(argc, argv, *a);
	if (total < 0)
	{
		free(*a);
		*a = NULL;
		return (total);
	}
	
	check = check_for_duplicates(*a, total);
	if (check < 0)
	{
		free(*a);
		*a = NULL;
		return (check);
	}
	return (total);
}