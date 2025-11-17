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


void swap_a(int *a, int len) 
{
	printf("sa\n");
	if (len < 2)
		return;
	int temp = a[0];
	a[0] = a[1];
	a[1] = temp;
}

void swap_b(int *b, int len)
{
	printf("sb\n");
	if (len < 2)
		return;
	int temp = b[0];
	b[0] = b[1];
	b[1] = temp;
}

void swap_multi_stack(int **a, int **b, int len_a, int len_b)
{
	printf("ss\n");
	if (len_a < 2 || len_b < 2)
		return;

	int temp_a = (*a)[0];
	(*a)[0] = (*a)[1];
	(*a)[1] = temp_a;

	int temp_b = (*b)[0];
	(*b)[0] = (*b)[1];
	(*b)[1] = temp_b;
}

