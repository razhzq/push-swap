#ifndef STACKOPS_H
# define STACKOPS_H

# include "../libft/libft.h"
# include <stdio.h>

void	swap_a(int *a, int len);
void	swap_b(int *b, int len);
void	swap_multi_stack(int **a, int **b, int len_a, int len_b);
void	push_a(int **a, int **b, int *len_a, int *len_b);
void	push_b(int **a, int **b, int *len_a, int *len_b);
void	rotate_a(int *a, int len);
void	rotate_b(int *b, int len);
void	rotate_multi_stack(int **a, int **b, int *len_a, int *len_b);
void	rotate_reverse_a(int *a, int len);
void	rotate_reverse_b(int *b, int len);
void	rotate_reverse_multi_stack(int **a, int **b, int *len_a, int *len_b);

#endif