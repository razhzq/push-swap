#include "pushswap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


static void	do_sort_3(int *a)
{
	int	v0;
	int	v1;
	int	v2;

	v0 = a[0];
	v1 = a[1];
	v2 = a[2];
	if (v0 > v1 && v1 < v2 && v0 < v2)
		swap_a(a, 3);
	else if (v0 > v1 && v1 > v2)
	{
		swap_a(a, 3);
		rotate_reverse_a(a, 3);
	}
	else if (v0 > v1 && v1 < v2 && v0 > v2)
		rotate_a(a, 3);
	else if (v0 < v1 && v1 > v2 && v0 < v2)
	{
		swap_a(a, 3);
		rotate_a(a, 3);
	}
	else if (v0 < v1 && v1 > v2 && v0 > v2)
		rotate_reverse_a(a, 3);
}


void	sort_3_elements(int *a, int len)
{
	if (len < 2)
		return ;
	if (len == 2)
	{
		if (a[0] > a[1])
			swap_a(a, 2);
	}
	else if (len == 3)
	{
		do_sort_3(a);
	}
}

// The core sorting flow, previously inside pushswap_chunk_sort (Max 25 lines,
	4 args)
void	pushswap_core_sort(t_stacks *stacks, int total, int *sorted,
		int chunk_count)
{
	int	chunk_size;

	if (total <= 15)
	{
		small_sort_push(stacks);
		return ;
	}
	chunk_size = total / chunk_count;
	// Phase 1: Push chunks to B
	phase1_push_loop(stacks, sorted, total, chunk_size);
	// Sort remaining 3 in A
	sort_3_elements(*stacks->a, *stacks->len_a);
	// Phase 2: Push back to A
	phase2_main_loop(stacks);
	// Final rotation
	final_rotation(*stacks->a, *stacks->len_a);
}

// New signature for pushswap_chunk_sort (Max 25 lines, 4 args)
void	pushswap_chunk_sort(int *a, int *b, int *len_a, int *len_b)
{
	int			total;
	int			*sorted;
	t_stacks	stacks;
	int			chunk_count;

	total = *len_a + *len_b;
	stacks = (t_stacks){&a, &b, len_a, len_b};
	sorted = get_sorted_copy(a, total);
	if (!sorted)
		return ;
	// Determine chunk count (must be copied here from pushswap to reduce its line count)
	if (total <= 15)
		chunk_count = 1;
	else if (total <= 100)
		chunk_count = 5;
	else if (total <= 500)
		chunk_count = 10;
	else
		chunk_count = 20;
	pushswap_core_sort(&stacks, total, sorted, chunk_count);
	free(sorted);
}

// Main function (Max 25 lines, 2 args)
void	pushswap(int *a, int len_a)
{
	int	*b;
	int	len_b;

	if (!a || len_a <= 0)
		return ;
	len_b = 0;
	b = malloc(sizeof(int) * len_a);
	if (!b)
	{
		free(a);
		return ;
	}
	pushswap_chunk_sort(a, b, &len_a, &len_b);
	free(a);
	free(b);
}

// Main entry point (Max 25 lines, 2 args)
int	main(int argc, char **argv)
{
	int *a;
	int len_a;

	if (argc < 2)
	{
		return (0);
	}

	len_a = parse_args(argc, argv, &a);

	if (len_a <= 0 || !a)
	{
		fprintf(stderr, "Error\n");
		return (1);
	}

	pushswap(a, len_a);
	return (0);
}
