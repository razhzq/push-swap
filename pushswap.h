#ifndef PUSHSWAP_H
# define PUSHSWAP_H

# include <stdlib.h> // For malloc, free
# include <unistd.h> // For write
# include <stdio.h>  // For fprintf (only in main for Error)


// Utility functions
int		parse_args(int argc, char **argv, int **a);
int		*get_sorted_copy(int *arr, int len);
int		get_median(int *arr, int len);

// Main sorting function
void	pushswap(int *a, int len_a);
void	pushswap_chunk_sort(int *a, int *b, int *len_a, int *len_b, int chunk_count);

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

#endif