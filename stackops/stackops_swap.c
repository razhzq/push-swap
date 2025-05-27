#include "stackops.h"


void swap_a(int *a, int len) 
{
	printf("sa\n");
	if (len < 2)
		return;
	int temp = a[0];
	a[0] = a[1];
	a[1] = temp;
	op_count++;
}

void swap_b(int *b, int len)
{
	printf("sb\n");
	if (len < 2)
		return;
	int temp = b[0];
	b[0] = b[1];
	b[1] = temp;
	op_count++;
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
	
	op_count++;
}

