#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H


#include "stackops/stackops.h"
#include <stdio.h>
#include <math.h>

int get_median(int *arr, int len);
int parse_args(int argc, char **argv, int **a);
void sort_small_stack_a(int *a, int len);
void sort_small_stack_b(int *b, int len);
void push_swap_sort_a(int *a, int *b, int *len_a, int *len_b, int size);
void push_swap_sort_b(int *a, int *b, int *len_a, int *len_b, int size);
int *get_sorted_copy(int *arr, int len);

#endif