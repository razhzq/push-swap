#include "pushswap.h"

// Max 25 lines, Max 4 args. OK.
static int find_rank(int val, int *sorted, int total)
{
    int j;

    j = 0;
    while (j < total)
    {
        if (val == sorted[j])
            return (j);
        j++;
    }
    return (-1);
}

// Max 25 lines, Max 4 args. OK.
static void	rotate_to_min(t_stacks *stacks, int min_idx)
{
	int i;
	int len_a;

	len_a = *stacks->len_a;
	i = 0;
	if (min_idx <= len_a / 2)
	{
		while (i < min_idx)
		{
			rotate_a(*stacks->a, len_a);
			i++;
		}
	}
	else
	{
		while (i < len_a - min_idx)
		{
			rotate_reverse_a(*stacks->a, len_a);
			i++;
		}
	}
}

// Removed 'total' argument to avoid unused parameter error. Max 25 lines, Max 4 args. OK.
void	small_sort_push(t_stacks *stacks)
{
	int min_val;
	int min_idx;
	int i;

	while (*stacks->len_a > 3)
	{
		min_idx = 0;
		min_val = (*stacks->a)[0];
		i = 1;
		while (i < *stacks->len_a)
		{
			if ((*stacks->a)[i] < min_val)
			{
				min_val = (*stacks->a)[i];
				min_idx = i;
			}
			i++;
		}
		rotate_to_min(stacks, min_idx);
		push_b(stacks->a, stacks->b, stacks->len_a, stacks->len_b);
	}
}

// Max 25 lines, Max 4 args. OK.
static void	exec_chunk_push(t_stacks *s, int *sorted, int total, int *range)
{
	int to_scan;
	int rank;

	to_scan = *s->len_a;
	while (to_scan > 0 && *s->len_a > 3)
	{
		rank = find_rank((*s->a)[0], sorted, total);
		if (rank >= range[0] && rank < range[1])
		{
			push_b(s->a, s->b, s->len_a, s->len_b);
			if (*s->len_b >= 2 && rank < range[0] + (range[1] - range[0]) / 2
				&& (*s->b)[1] > (*s->b)[0])
			{
				rotate_b(*s->b, *s->len_b);
			}
		}
		else
		{
			rotate_a(*s->a, *s->len_a);
		}
		to_scan--;
	}
}

// **CRITICAL LOGIC FIX APPLIED HERE**
// Max 25 lines, Max 4 args. OK.
void	phase1_push_loop(t_stacks *s, int *sorted, int total, int chunk_size)
{
	int chunk;
	int range[2];
	int chunk_count;

	chunk_count = total / chunk_size;
	if (total % chunk_size != 0)
		chunk_count++;
		
	chunk = 0;
	while (chunk < chunk_count)
	{
		range[0] = chunk * chunk_size;
		
		// FIX: Ensures the 3 largest elements remain in stack A
		if (chunk == chunk_count - 1)
			range[1] = total - 3;
		else
			range[1] = (chunk + 1) * chunk_size;
			
		exec_chunk_push(s, sorted, total, range);
		chunk++;
	}
}

// Max 25 lines, Max 4 args. OK.
static int	get_max_b_idx(int *b, int len_b)
{
	int max_idx;
	int max_val;
	int i;

	if (len_b <= 0)
		return (0);
	max_idx = 0;
	max_val = b[0];
	i = 1;
	while (i < len_b)
	{
		if (b[i] > max_val)
		{
			max_val = b[i];
			max_idx = i;
		}
		i++;
	}
	return (max_idx);
}

// Max 25 lines, Max 4 args. OK.
static int	get_insert_a_pos(int *a, int len_a, int max_val)
{
	int insert_pos;
	int min_idx;
	int i;

	insert_pos = 0;
	i = 0;
	while (i < len_a)
	{
		if (max_val > a[i])
			insert_pos = i + 1;
		i++;
	}
	if (insert_pos == len_a)
	{
		min_idx = 0;
		i = 1;
		while (i < len_a)
		{
			if (a[i] < a[min_idx])
				min_idx = i;
			i++;
		}
		return (min_idx);
	}
	return (insert_pos);
}

// Max 25 lines, Max 4 args. (Rotation logic helper)
static void	exec_phase2_rotations(t_stacks *s, int b_cost, int a_cost, int *flags)
{
	int simultaneous;
	int i;

	i = 0;
	if (flags[0] && flags[1]) 
	{
		simultaneous = (b_cost < a_cost) ? b_cost : a_cost;
		while (i++ < simultaneous)
			rotate_multi_stack(s->a, s->b, s->len_a, s->len_b);
		i = 0;
		while (i++ < b_cost - simultaneous)
			rotate_b(*s->b, *s->len_b);
		i = 0;
		while (i++ < a_cost - simultaneous)
			rotate_a(*s->a, *s->len_a);
	}
	else if (!flags[0] && !flags[1]) 
	{
		simultaneous = (b_cost < a_cost) ? b_cost : a_cost;
		while (i++ < simultaneous)
			rotate_reverse_multi_stack(s->a, s->b, s->len_a, s->len_b);
		i = 0;
		while (i++ < b_cost - simultaneous)
			rotate_reverse_b(*s->b, *s->len_b);
		i = 0;
		while (i++ < a_cost - simultaneous)
			rotate_reverse_a(*s->a, *s->len_a);
	}
}

// Max 25 lines, Max 4 args. OK.
static void	exec_mixed_rotations(t_stacks *s, int b_cost, int a_cost, int *flags)
{
	int i;
	
	i = 0;
	if (flags[0]) 
	{
		while (i++ < b_cost)
			rotate_b(*s->b, *s->len_b);
	}
	else 
	{
		while (i++ < b_cost)
			rotate_reverse_b(*s->b, *s->len_b);
	}

	i = 0;
	if (flags[1]) 
	{
		while (i++ < a_cost)
			rotate_a(*s->a, *s->len_a);
	}
	else 
	{
		while (i++ < a_cost)
			rotate_reverse_a(*s->a, *s->len_a);
	}
}

// Removed 'total' and 'sorted' arguments to avoid unused parameter error. Max 25 lines, Max 4 args. OK.
void	phase2_main_loop(t_stacks *s)
{
	int max_idx;
	int insert_pos;
	int b_cost;
	int a_cost;
	int flags[2];

	while (*s->len_b > 0)
	{
		max_idx = get_max_b_idx(*s->b, *s->len_b);
		insert_pos = get_insert_a_pos(*s->a, *s->len_a, (*s->b)[max_idx]);

		flags[0] = (max_idx <= *s->len_b / 2);
		b_cost = flags[0] ? max_idx : (*s->len_b - max_idx);
		
		flags[1] = (insert_pos <= *s->len_a / 2);
		a_cost = flags[1] ? insert_pos : (*s->len_a - insert_pos);

		if (flags[0] == flags[1])
			exec_phase2_rotations(s, b_cost, a_cost, flags);
		else
			exec_mixed_rotations(s, b_cost, a_cost, flags);

		push_a(s->a, s->b, s->len_a, s->len_b);
	}
}

// Max 25 lines, Max 4 args. OK.
void	final_rotation(int *a, int len)
{
	int min_idx;
	int i;

	min_idx = 0;
	i = 1;
	while (i < len)
	{
		if (a[i] < a[min_idx])
			min_idx = i;
		i++;
	}

	i = 0;
	if (min_idx <= len / 2)
	{
		while (i < min_idx)
		{
			rotate_a(a, len);
			i++;
		}
	}
	else
	{
		while (i < len - min_idx)
		{
			rotate_reverse_a(a, len);
			i++;
		}
	}
}