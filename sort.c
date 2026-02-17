#include "utils.h"
#include <unistd.h>

void	sort_three(t_stack *s)
{
	int	a;
	int	b;
	int	c;

	a = s->stack[2];
	b = s->stack[1];
	c = s->stack[0];
	if (a > b && b < c && a < c)
	{
		stack_swap(s);
		write(1, "sa\n", 3);
	}
	else if (a > b && b > c)
	{
		stack_swap(s);
		write(1, "sa\n", 3);
		stack_rotate_down(s);
		write(1, "rra\n", 3);
	}
	else if (a > b && b < c && a > c)
	{
		stack_rotate_up(s);
		write(1, "ra\n", 3);
	}
	else if (a < b && b > c && a < c)
	{
		stack_swap(s);
		write(1, "sa\n", 3);
		stack_rotate_up(s);
		write(1, "ra\n", 3);
	}
	else if (a < b && b > c && a > c)
	{
		stack_rotate_down(s);
		write(1, "rra\n", 3);
	}
}
