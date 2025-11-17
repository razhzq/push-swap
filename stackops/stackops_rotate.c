/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackops_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:11:58 by muabdul-          #+#    #+#             */
/*   Updated: 2025/11/17 21:12:04 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stackops.h"

void	rotate_reverse_a(int *a, int len)
{
	int	last;
	int	i;

	printf("rra\n");
	if (len < 2)
		return ;
	last = a[len - 1];
	i = len - 1;
	while (i > 0)
	{
		a[i] = a[i - 1];
		i--;
	}
	a[0] = last;
}

void	rotate_reverse_b(int *b, int len)
{
	int	last;
	int	i;

	printf("rrb\n");
	if (len < 2)
		return ;
	last = b[len - 1];
	i = len - 1;
	while (i > 0)
	{
		b[i] = b[i - 1];
		i--;
	}
	b[0] = last;
}

void	rotate_reverse_multi_stack(int **a, int **b, int *len_a, int *len_b)
{
	int	i;
	int	last_a;
	int	last_b;

	printf("rrr\n");
	if (*len_a < 2 || *len_b < 2)
		return ;
	last_a = (*a)[*len_a - 1];
	i = *len_a - 1;
	while (i > 0)
	{
		(*a)[i] = (*a)[i - 1];
		i--;
	}
	(*a)[0] = last_a;
	last_b = (*b)[*len_b - 1];
	i = *len_b - 1;
	while (i > 0)
	{
		(*b)[i] = (*b)[i - 1];
		i--;
	}
	(*b)[0] = last_b;
}
