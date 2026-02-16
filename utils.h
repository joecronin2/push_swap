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
