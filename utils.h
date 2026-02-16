#pragma once

#include "push_swap.h"
#include <stdbool.h>
#include <stdlib.h>

bool ft_strtoi(const char *str, int *out);
int *parse_ints(char **strs, size_t size);
bool has_duplicates(t_stack *stack);

bool stack_is_sorted(t_stack *s);

void free_stack(t_stack *stack);
t_stack *alloc_stack(size_t size);
t_stack *init_stack(int *nums, size_t size);
t_stack *dup_stack(t_stack *stack);

void stack_swap(t_stack *s);
bool stack_push(t_stack *from, t_stack *to);
bool stack_enqueue(t_stack *from, t_stack *to);
void stack_rotate_up(t_stack *s);
void stack_rotate_down(t_stack *s);

void radix(t_stack *a, t_stack *b);
t_stack *index_stack(t_stack *s);
void sort_three(t_stack *s);
