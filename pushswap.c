#include "pushswap.h"
#include <limits.h>
#include <stdio.h> 
#include <stdlib.h>



static void	sort_3_elements(int *a, int len)
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
		int v0 = a[0];
		int v1 = a[1];
		int v2 = a[2];

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
}

void	pushswap_chunk_sort(int *a, int *b, int *len_a, int *len_b,
		int chunk_count)
{
	int	total;
	int	*sorted;
	int	min_idx;
	int	min_val;
	int	chunk_size;
	int	chunk_min;
	int	chunk_max;
	int	rank;
	int	max_idx;
	int	max_val;
	int	insert_pos;
	int	b_rotate_forward;
	int	b_cost;
	int	a_rotate_forward;
	int	a_cost;
	int	simultaneous;

	total = *len_a;
	if (total <= 3)
	{
		sort_3_elements(a, total);
		return ;
	}
	
	sorted = get_sorted_copy(a, total);
	if (!sorted)
		return ;

	// For small arrays (4-15), use optimized small sort (push all but 3 largest to B)
	if (total <= 15)
	{
		while (*len_a > 3)
		{
			min_idx = 0;
			min_val = a[0];
			for (int i = 1; i < *len_a; i++)
			{
				if (a[i] < min_val)
				{
					min_val = a[i];
					min_idx = i;
				}
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
			push_b(&a, &b, len_a, len_b);
		}
		sort_3_elements(a, *len_a);
		while (*len_b > 0)
			push_a(&a, &b, len_a, len_b);
		free(sorted);
		return ;
	}

	chunk_size = total / chunk_count;
	for (int chunk = 0; chunk < chunk_count; chunk++)
	{
		chunk_min = chunk * chunk_size;
		chunk_max = (chunk == chunk_count - 1) ? total - 3 : (chunk + 1) * chunk_size;

		int to_scan = *len_a;
		while (to_scan > 0 && *len_a > 3)
		{
			rank = -1;
			for (int j = 0; j < total; j++)
			{
				if (a[0] == sorted[j])
				{
					rank = j;
					break ;
				}
			}
			// If in current chunk range, push to B
			if (rank >= chunk_min && rank < chunk_max)
			{
				push_b(&a, &b, len_a, len_b);
				// Rotate B strategically
				if (*len_b >= 2 && rank < chunk_min + chunk_size / 2
					&& b[1] > b[0])
				{
					rotate_b(b, *len_b);
				}
			}
			else
			{
				rotate_a(a, *len_a);
			}
			to_scan--;
		}
	}
	
	sort_3_elements(a, *len_a);
	
	// Phase 2: Push everything back from B to A with optimized rotations
	while (*len_b > 0)
	{
		// Find max in B
		max_idx = 0;
		max_val = b[0];
		for (int i = 1; i < *len_b; i++)
		{
			if (b[i] > max_val)
			{
				max_val = b[i];
				max_idx = i;
			}
		}
		
		// Find insertion point in A
		insert_pos = 0;
		for (int i = 0; i < *len_a; i++)
		{
			if (max_val > a[i])
				insert_pos = i + 1;
		}
		
		// Handle wrap-around (find smallest element in A if max_val is the largest overall)
		if (insert_pos == *len_a)
		{
			min_idx = 0;
			for (int i = 1; i < *len_a; i++)
			{
				if (a[i] < a[min_idx])
					min_idx = i;
			}
			insert_pos = min_idx;
		}
		
		// Calculate rotation costs
		b_rotate_forward = (max_idx <= *len_b / 2);
		b_cost = b_rotate_forward ? max_idx : (*len_b - max_idx);
		a_rotate_forward = (insert_pos <= *len_a / 2);
		a_cost = a_rotate_forward ? insert_pos : (*len_a - insert_pos);
		
		// Perform rotations (prioritizing simultaneous rr/rrr)
		if (b_rotate_forward && a_rotate_forward)
		{
			simultaneous = (b_cost < a_cost) ? b_cost : a_cost;
			for (int i = 0; i < simultaneous; i++)
				rotate_multi_stack(&a, &b, len_a, len_b);
			for (int i = 0; i < b_cost - simultaneous; i++)
				rotate_b(b, *len_b);
			for (int i = 0; i < a_cost - simultaneous; i++)
				rotate_a(a, *len_a);
		}
		else if (!b_rotate_forward && !a_rotate_forward)
		{
			simultaneous = (b_cost < a_cost) ? b_cost : a_cost;
			for (int i = 0; i < simultaneous; i++)
				rotate_reverse_multi_stack(&a, &b, len_a, len_b);
			for (int i = 0; i < b_cost - simultaneous; i++)
				rotate_reverse_b(b, *len_b);
			for (int i = 0; i < a_cost - simultaneous; i++)
				rotate_reverse_a(a, *len_a);
		}
		else
		{
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
	
	// Final rotation to put min element at top of A
	min_idx = 0;
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

void	pushswap(int *a, int len_a)
{
	int	*b;
	int	len_b;
	int	chunk_count;

	if (!a || len_a <= 0)
		return ;
	len_b = 0;
	b = malloc(sizeof(int) * len_a);
	if (!b)
	{
		free(a);
		return ;
	}

	// Determine chunk count based on size for optimization
	if (len_a <= 15)
		chunk_count = 1; 
	else if (len_a <= 100)
		chunk_count = 5;
	else if (len_a <= 500)
		chunk_count = 10;
	else
		chunk_count = 20;
	
	pushswap_chunk_sort(a, b, &len_a, &len_b, chunk_count);
	
	free(a);
	free(b);
}

int	main(int argc, char **argv)
{
	int *a;
	int len_a;

	if (argc < 2)
	{
		// No output for no arguments, as required by the subject
		return (0); 
	}

	len_a = parse_args(argc, argv, &a);
	
	// Error handling: output "Error" to stderr if parsing failed
	if (len_a <= 0 || !a)
	{
		fprintf(stderr, "Error\n"); 
		return (1);
	}
	
	pushswap(a, len_a);
	return (0);
}