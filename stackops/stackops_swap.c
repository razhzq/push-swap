/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackops_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:12:43 by muabdul-          #+#    #+#             */
/*   Updated: 2025/11/17 21:12:46 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stackops.h"

void	swap_a(int *a, int len)
{
	int	temp;

	printf("sa\n");
	if (len < 2)
		return ;
	temp = a[0];
	a[0] = a[1];
	a[1] = temp;
}

void	swap_b(int *b, int len)
{
	int	temp;

	printf("sb\n");
	if (len < 2)
		return ;
	temp = b[0];
	b[0] = b[1];
	b[1] = temp;
}

void	swap_multi_stack(int **a, int **b, int len_a, int len_b)
{
	int	temp_a;
	int	temp_b;

	printf("ss\n");
	if (len_a < 2 || len_b < 2)
		return ;
	temp_a = (*a)[0];
	(*a)[0] = (*a)[1];
	(*a)[1] = temp_a;
	temp_b = (*b)[0];
	(*b)[0] = (*b)[1];
	(*b)[1] = temp_b;
}
