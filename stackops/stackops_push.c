/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackops_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdul- <muabdul-@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 21:07:17 by muabdul-          #+#    #+#             */
/*   Updated: 2025/11/17 21:08:25 by muabdul-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stackops.h"

void	push_a(int **a, int **b, int *len_a, int *len_b)
{
	int	temp;
	int	i;

	printf("pa\n");
	if (*len_b == 0)
		return ;
	temp = (*b)[0];
	i = 0;
	while (i < *len_b - 1)
	{
		(*b)[i] = (*b)[i + 1];
		i++;
	}
	i = *len_a;
	while (i > 0)
	{
		(*a)[i] = (*a)[i - 1];
		i--;
	}
	(*a)[0] = temp;
	(*len_a)++;
	(*len_b)--;
}

void	push_b(int **a, int **b, int *len_a, int *len_b)
{
	int	temp;
	int	i;

	printf("pb\n");
	if (*len_a == 0)
		return ;
	temp = (*a)[0];
	i = 0;
	while (i < *len_a - 1)
	{
		(*a)[i] = (*a)[i + 1];
		i++;
	}
	i = *len_b;
	while (i > 0)
	{
		(*b)[i] = (*b)[i - 1];
		i--;
	}
	(*b)[0] = temp;
	(*len_b)++;
	(*len_a)--;
}

void	rotate_a(int *a, int len)
{
	int	first;
	int	i;

	printf("ra\n");
	if (len < 2)
		return ;
	first = a[0];
	i = 0;
	while (i < len - 1)
	{
		a[i] = a[i + 1];
		i++;
	}
	a[len - 1] = first;
}

void	rotate_b(int *b, int len)
{
	int	first;
	int	i;

	printf("rb\n");
	if (len < 2)
		return ;
	first = b[0];
	i = 0;
	while (i < len - 1)
	{
		b[i] = b[i + 1];
		i++;
	}
	b[len - 1] = first;
}

void	rotate_multi_stack(int **a, int **b, int *len_a, int *len_b)
{
	int	first_a;
	int	i;
	int	first_b;

	printf("rr\n");
	if (*len_a < 2 || *len_b < 2)
		return ;
	first_a = (*a)[0];
	i = 0;
	while (i < *len_a - 1)
	{
		(*a)[i] = (*a)[i + 1];
		i++;
	}
	(*a)[*len_a - 1] = first_a;
	first_b = (*b)[0];
	i = 0;
	while (i < *len_b - 1)
	{
		(*b)[i] = (*b)[i + 1];
		i++;
	}
	(*b)[*len_b - 1] = first_b;
}
