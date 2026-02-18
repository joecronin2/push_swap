/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcronin <jcronin@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 20:47:22 by jcronin           #+#    #+#             */
/*   Updated: 2026/02/17 20:47:22 by jcronin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <libft.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>

// void pss(t_stack *a, t_stack *b) {
//   for (ssize_t i = a->size - 1; i > 0; i--)
//     printf("%zu: %7d %7d\n", i, a->stack[i], b->stack[i]);
// }
//
// void ps(t_stack *stack) {
//   for (ssize_t i = stack->size - 1; i >= 0; i--)
//     printf("%zu: %i\n", i, stack->stack[i]);
// }
//
// void psb(t_stack *stack) {
//   for (ssize_t i = stack->size - 1; i >= 0; i--)
//     printf("%zu: %08b\n", i, stack->stack[i]);
//   putchar('\n');
// }

int	*parse_ints(char **strs, size_t size)
{
	int		*nums;
	size_t	i;

	nums = malloc(size * sizeof(int));
	if (!nums)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (!ft_strtoi(strs[size - i - 1], &nums[i]))
			return (free(nums), NULL);
		i++;
	}
	return (nums);
}

bool	has_duplicates(t_stack *stack)
{
	long	j;
	t_stack	*dup;
	size_t	i;
	int		key;

	dup = dup_stack(stack);
	if (!dup)
		return (true);
	i = 1;
	while (i < dup->size)
	{
		key = dup->stack[i];
		j = i - 1;
		while (j >= 0 && dup->stack[j] > key)
		{
			dup->stack[j + 1] = dup->stack[j];
			j--;
		}
		if (j >= 0 && dup->stack[j] == key)
			return (free_stack(dup), true);
		dup->stack[j + 1] = key;
		i++;
	}
	return (free_stack(dup), false);
}

bool	stack_is_sorted(t_stack *s)
{
	size_t	i;

	i = 0;
	while (i < s->size - 1)
	{
		if (s->stack[i] < s->stack[i + 1])
			return (false);
		i++;
	}
	return (true);
}

t_stack	*prepare_stack(int *nums, size_t size)
{
	t_stack	*a;
	t_stack	*indexed;

	a = init_stack(nums, size);
	if (!a || has_duplicates(a))
		return (free_stack(a), NULL);
	indexed = index_stack(a);
	free_stack(a);
	return (indexed);
}

int	main(int argc, char **argv)
{
	t_stack	*b;
	t_stack	*a;
	int		*nums;

	if (argc < 2)
		return (write(1, "Error\n", 6), 0);
	nums = parse_ints(&argv[1], argc - 1);
	if (!nums)
		return (write(1, "Error\n", 6), 0);
	a = prepare_stack(nums, argc - 1);
	free(nums);
	if (!a)
		return (write(1, "Error\n", 6), 0);
	if (stack_is_sorted(a))
		return (free_stack(a), 0);
	b = alloc_stack(a->size);
	if (!b)
		return (free_stack(a), write(1, "Error\n", 6), 0);
	solve(a, b);
	return (free_stack(a), free_stack(b), 0);
}
