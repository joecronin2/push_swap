/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:48:01 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/17 20:48:02 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "push_swap.h"
#include "utils.h"

void	free_stack(t_stack *stack)
{
	if (stack)
	{
		free(stack->stack);
		free(stack);
	}
}

t_stack	*alloc_stack(size_t size)
{
	t_stack	*stack;

	stack = malloc(sizeof(*stack));
	if (!stack)
		return (NULL);
	stack->stack = malloc(sizeof(int) * size);
	if (!stack->stack)
		return (free(stack), NULL);
	stack->size = 0;
	return (stack);
}

t_stack	*init_stack(int *nums, size_t size)
{
	t_stack	*stack;

	stack = alloc_stack(size);
	if (!stack)
		return (NULL);
	ft_memcpy(stack->stack, nums, size * sizeof(int));
	stack->size = size;
	return (stack);
}

t_stack	*dup_stack(t_stack *stack)
{
	t_stack	*new;

	new = alloc_stack(stack->size);
	if (!new)
		return (NULL);
	ft_memcpy(new->stack, stack->stack, stack->size * sizeof(int));
	new->size = stack->size;
	return (new);
}
