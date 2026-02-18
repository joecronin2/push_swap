/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 02:17:45 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/18 02:17:58 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "push_swap.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_stack
{
	int		*stack;
	size_t	size;
}			t_stack;

bool		ft_strtoi(const char *str, int *out);

bool		stack_is_sorted(t_stack *s);

void		free_stack(t_stack *stack);
t_stack		*alloc_stack(size_t size);
t_stack		*init_stack(int *nums, size_t size);
t_stack		*dup_stack(t_stack *stack);

void		stack_swap(t_stack *s);
bool		stack_push(t_stack *from, t_stack *to);
void		stack_rotate_up(t_stack *s);
void		stack_rotate_down(t_stack *s);

void		radix(t_stack *a, t_stack *b);
t_stack		*index_stack(t_stack *s);
void		solve(t_stack *a, t_stack *b);
