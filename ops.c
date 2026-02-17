#include "libft/libft.h"
#include "push_swap.h"
#include <stdbool.h>

void	stack_swap(t_stack *s)
{
	int	tmp;

	if (s->size < 2)
		return ;
	tmp = s->stack[s->size];
	s->stack[s->size] = s->stack[s->size - 1];
	s->stack[s->size - 1] = tmp;
}

bool	stack_push(t_stack *from, t_stack *to)
{
	int	n;

	if (from->size < 1)
		return (false);
	n = from->stack[--from->size];
	to->stack[to->size++] = n;
	return (true);
}

bool	stack_enqueue(t_stack *from, t_stack *to)
{
	int	value;

	if (from->size < 1)
		return (false);
	value = from->stack[--from->size];
	if (to->size > 0)
		ft_memmove(&to->stack[1], &to->stack[0], to->size * sizeof(int));
	to->stack[0] = value;
	return (true);
}

// first becomes last
void	stack_rotate_up(t_stack *s)
{
	int	last;

	if (s->size < 2)
		return ;
	last = s->stack[s->size - 1];
	ft_memmove(&s->stack[1], &s->stack[0], (s->size - 1) * sizeof(int));
	s->stack[0] = last;
}

// last becomes first
void	stack_rotate_down(t_stack *s)
{
	int	first;

	if (s->size < 2)
		return ;
	first = s->stack[0];
	ft_memmove(&s->stack[0], &s->stack[1], (s->size - 1) * sizeof(int));
	s->stack[s->size - 1] = first;
}
