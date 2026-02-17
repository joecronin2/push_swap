
// 5 101
// 2 010
// 7 111
// 1 001
// 4 100
// 0 000
// 6 110
// 3 011

// 0b101,0b010,0b111,0b001,0b100,0b000,0b110,0b011

void	test_index(void)
{
	t_stack	*s;

	s = init_stack((int[]){5, 4, 3, 2, 1}, 5);
	(void)s;
	// t_stack *i = index_stack(s);
}

void	test_radix(void)
{
	t_stack	*a;
	t_stack	*b;

	a = init_stack((int[]){0b101, 0b010, 0b111, 0b001, 0b100, 0b000, 0b110,
			0b011}, 8);
	b = alloc_stack(8);
	radix(a, b);
	free_stack(a);
	free_stack(b);
}

void	test_intbit(void)
{
	int	b;

	b = 0b10110001;
	assert(intbit(b, 0));
	assert(!intbit(b, 1));
	assert(!intbit(b, 2));
	assert(!intbit(b, 3));
	assert(intbit(b, 4));
	assert(intbit(b, 5));
	assert(!intbit(b, 6));
	assert(intbit(b, 7));
}

bool	arr_eq(int *a, int *b, size_t size)
{
	for (size_t i = 0; i < size; i++)
		if (a[i] != b[i])
			return (false);
	return (true);
}

void	test_rotate(void)
{
		int orig[] = {1, 2, 3, 4, 5};
	t_stack	*s;
		int orig[] = {1, 2};
	t_stack	*s;
		int orig[] = {1};
	t_stack	*s;
		int orig[] = {1, 2, 3, 4};
	t_stack	*s;

	// {
	//   int orig[] = {1, 2, 3, 4};
	//   t_stack *s = init_stack(orig, sizeof(orig) / sizeof(int));
	//   t_stack *b = init_stack((int[]){5}, 1);
	// stack_enqueue(b, s);
	//   free(s);
	// }
	{
		s = init_stack(orig, sizeof(orig) / sizeof(int));
		stack_rotate_up(s);
		assert(arr_eq((int[]){5, 1, 2, 3, 4}, s->stack, sizeof(orig)
				/ sizeof(int)));
		stack_rotate_down(s);
		assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
		free(s);
	}
	{
		s = init_stack(orig, sizeof(orig) / sizeof(int));
		stack_rotate_up(s);
		assert(arr_eq((int[]){2, 1}, s->stack, sizeof(orig) / sizeof(int)));
		stack_rotate_down(s);
		assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
		free(s);
	}
	{
		s = init_stack(orig, sizeof(orig) / sizeof(int));
		stack_rotate_up(s);
		assert(arr_eq((int[]){1}, s->stack, sizeof(orig) / sizeof(int)));
		stack_rotate_down(s);
		assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
		free(s);
	}
	{
		s = init_stack(orig, sizeof(orig) / sizeof(int));
		stack_rotate_up(s);
		assert(arr_eq((int[]){4, 1, 2, 3}, s->stack, sizeof(orig)
				/ sizeof(int)));
		stack_rotate_down(s);
		assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
		free(s);
	}
}

void	test_strtoi(void)
{
	int	i;

	i = 0;
	assert(ft_strtoi("123", &i));
	assert(i == 123);
	assert(ft_strtoi("-123", &i));
	assert(i == -123);
	assert(ft_strtoi("0", &i));
	assert(i == 0);
	assert(ft_strtoi("-0", &i));
	assert(i == 0);
	assert(ft_strtoi("-00", &i));
	assert(i == 0);
	assert(ft_strtoi("-2147483648", &i));
	assert(i == -2147483648);
	assert(ft_strtoi("2147483647", &i));
	assert(i == 2147483647);
	assert(!ft_strtoi("2147483648", &i));
}

void	test_stack(void)
{
	t_stack	*stack;

	stack = init_stack((int[]){5, 4, 3}, 3);
	assert(!has_duplicates(stack));
	free(stack);
	stack = init_stack((int[]){1, 2, 3}, 3);
	assert(!has_duplicates(stack));
	free(stack);
	stack = init_stack((int[]){1, 2, 2, 3}, 4);
	assert(has_duplicates(stack));
	free(stack);
	stack = init_stack((int[]){1, 2, 3, 2, 4}, 5);
	assert(has_duplicates(stack));
	free(stack);
}

void	test_duplicates(void)
{
	t_stack	*s;
	t_stack	*s;
	t_stack	*s;

	{
		s = init_stack((int[]){1, 2, 3}, 3);
		assert(!has_duplicates(s));
		free(s);
	}
	{
		s = init_stack((int[]){1, 2, 2}, 3);
		assert(has_duplicates(s));
		free(s);
	}
	{
		s = init_stack((int[]){1, 4, 3, 4}, 4);
		assert(has_duplicates(s));
		free(s);
	}
}

void	test(void)
{
	test_duplicates();
	test_radix();
	test_intbit();
	test_rotate();
	test_index();
	test_stack();
	test_strtoi();
}
