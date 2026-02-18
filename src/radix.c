/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:47:33 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/17 20:48:11 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <unistd.h>

static void	partition_by_bit(t_stack *a, t_stack *b, int bit)
{
	int	atop;

	atop = a->stack[a->size - 1];
	if (!((atop >> bit) & 1))
	{
		stack_push(a, b);
		write(1, "pb\n", 3);
	}
	else
	{
		stack_rotate_up(a);
		write(1, "ra\n", 3);
	}
}

static void	radix_bit(t_stack *a, t_stack *b, int bit)
{
	size_t	size;

	size = a->size;
	while (size--)
		partition_by_bit(a, b, bit);
	while (b->size)
	{
		stack_push(b, a);
		write(1, "pa\n", 3);
	}
}

static int	msb_pos_int(int x)
{
	int	pos;

	if (x == 0)
		return (-1);
	pos = 0;
	while ((unsigned int)x > 1)
	{
		x >>= 1;
		pos++;
	}
	return (pos);
}

static int	stack_max(t_stack *s)
{
	int		max;
	size_t	i;

	max = INT_MIN;
	i = 0;
	while (i < s->size)
	{
		if (s->stack[i] > max)
			max = s->stack[i];
		i++;
	}
	return (max);
}

void	radix(t_stack *a, t_stack *b)
{
	int	i;
	int	max;
	int	bits;

	i = 0;
	max = stack_max(a);
	bits = msb_pos_int(max) + 1;
	while (i < bits && !stack_is_sorted(a))
		radix_bit(a, b, i++);
}
