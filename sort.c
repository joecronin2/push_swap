/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:47:45 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/17 20:47:45 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

void	sort_three(t_stack *s)
{
	int	*n;

	n = s->stack;
	if (n[2] > n[1] && n[2] > n[0])
	{
		stack_rotate_up(s);
		write(1, "ra\n", 3);
	}
	else if (n[1] > n[2] && n[1] > n[0])
	{
		stack_rotate_down(s);
		write(1, "rra\n", 4);
	}
	if (s->stack[2] > s->stack[1])
	{
		stack_swap(s);
		write(1, "sa\n", 3);
	}
}

static size_t	stack_num_index(t_stack *s, int num)
{
	size_t	i;

	i = 0;
	while (i < s->size)
	{
		if (s->stack[i] == num)
			break ;
		i++;
	}
	return (i);
}

static void	push_num(t_stack *a, t_stack *b, int num)
{
	size_t	pos;

	if (a->size == 0)
		return ;
	while (a->stack[a->size - 1] != num)
	{
		pos = stack_num_index(a, num);
		if (pos == a->size)
			return ;
		if (pos >= a->size / 2)
		{
			stack_rotate_up(a);
			write(1, "ra\n", 3);
		}
		else
		{
			stack_rotate_down(a);
			write(1, "rra\n", 4);
		}
	}
	stack_push(a, b);
	write(1, "pb\n", 3);
}

void	sort_five(t_stack *a, t_stack *b)
{
	push_num(a, b, 0);
	push_num(a, b, 1);
	sort_three(a);
	stack_push(b, a);
	write(1, "pa\n", 3);
	stack_push(b, a);
	write(1, "pa\n", 3);
}

void	solve(t_stack *a, t_stack *b)
{
	if (a->size == 3)
		sort_three(a);
	else if (a->size == 5)
		sort_five(a, b);
	else
		radix(a, b);
}
