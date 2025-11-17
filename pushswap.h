#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h> 
# include <unistd.h> 
# include <stdio.h>  
# include <limits.h>

extern int op_count;

typedef struct s_stacks
{
	int		**a;
	int		**b;
	int		*len_a;
	int		*len_b;
}	t_stacks;

// Utility functions (assuming these are in utils.c or libft)
int		parse_args(int argc, char **argv, int **a);
int		*get_sorted_copy(int *arr, int len);

// // Helper function prototypes for utility functions (moved logic out of parse_args)
// static int	parse_validate_and_fill(int argc, char **argv, int *a);
// static int	check_for_duplicates(int *a, int total);
// static int	count_total_numbers(int argc, char **argv);

// Instruction functions (must print the instruction to STDOUT)
void	swap_a(int *a, int len);
void	swap_b(int *b, int len);
void	push_a(int **a, int **b, int *len_a, int *len_b);
void	push_b(int **a, int **b, int *len_a, int *len_b);
void	rotate_a(int *a, int len);
void	rotate_b(int *b, int len);
void	rotate_multi_stack(int **a, int **b, int *len_a, int *len_b);
void	rotate_reverse_a(int *a, int len);
void	rotate_reverse_b(int *b, int len);
void	rotate_reverse_multi_stack(int **a, int **b, int *len_a, int *len_b);

// Main sorting functions
void	pushswap(int *a, int len_a);
void	pushswap_chunk_sort(int *a, int *b, int *len_a, int *len_b); 
void	pushswap_core_sort(t_stacks *stacks, int total, int *sorted, int chunk_count);

// Helper functions for small sort
// static void	do_sort_3(int *a);
void	sort_3_elements(int *a, int len);

// Helper functions for chunk sort (all <= 25 lines, <= 4 args)
void	small_sort_push(t_stacks *stacks);
void	phase1_push_loop(t_stacks *stacks, int *sorted, int total, int chunk_size);
void	phase2_main_loop(t_stacks *stacks);
void	final_rotation(int *a, int len);

#endif