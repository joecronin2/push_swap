#include "push_swap.h"
#include "utils.h"
#include "libft/libft.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h> // TODO
#include <stdlib.h>
#include <unistd.h>


int *parse_ints(char **strs, size_t size) {
  int *nums = malloc(size * sizeof(int));
  if (!nums)
    return NULL;
  size_t i = 0;
  while (i < size) {
    if (!ft_strtoi(strs[size - i - 1], &nums[i]))
      return (free(nums), NULL);
    i++;
  }
  return nums;
}

bool has_duplicates(t_stack *stack) {
  long j;
  t_stack *dup = dup_stack(stack);
  if (!dup)
    return true;
  size_t i = 1;
  while (i < dup->size) {
    int key = dup->stack[i];
    j = i - 1;
    while (j >= 0 && dup->stack[j] > key) {
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

bool stack_is_sorted(t_stack *s) {
  size_t i = 0;
  while (i < s->size - 1) {
    if (s->stack[i] < s->stack[i + 1])
      return false;
    i++;
  }
  return true;
}


void pss(t_stack *a, t_stack *b) {
  for (ssize_t i = a->size - 1; i > 0; i--)
    printf("%zu: %7d %7d\n", i, a->stack[i], b->stack[i]);
}

void ps(t_stack *stack) {
  for (ssize_t i = stack->size - 1; i >= 0; i--)
    printf("%zu: %i\n", i, stack->stack[i]);
}

void psb(t_stack *stack) {
  for (ssize_t i = stack->size - 1; i >= 0; i--)
    printf("%zu: %08b\n", i, stack->stack[i]);
  putchar('\n');
}

void sort_three(t_stack *s) {
  int a = s->stack[2];
  int b = s->stack[1];
  int c = s->stack[0];

  if (a > b && b < c && a < c) {
    stack_swap(s);
    write(1, "sa\n", 3);
  } else if (a > b && b > c) {
    stack_swap(s);
    write(1, "sa\n", 3);
    stack_rotate_down(s);
    write(1, "rra\n", 3);
  } else if (a > b && b < c && a > c) {
    stack_rotate_up(s);
    write(1, "ra\n", 3);
  } else if (a < b && b > c && a < c) {
    stack_swap(s);
    write(1, "sa\n", 3);
    stack_rotate_up(s);
    write(1, "ra\n", 3);
  } else if (a < b && b > c && a > c) {
    stack_rotate_down(s);
    write(1, "rra\n", 3);
  }
}

void swap_int(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void stack_swap(t_stack *s) {
  if (s->size < 2)
    return;
  swap_int(&s->stack[s->size], &s->stack[s->size - 1]);
}

void stack_sort(t_stack *s) {
  size_t i, j;
  i = 0;
  while (i < s->size) {
    j = 0;
    while (j < s->size - 1) {
      if (s->stack[j] > s->stack[j + 1])
        swap_int(&s->stack[j], &s->stack[j + 1]);
      j++;
    }
    i++;
  }
}

int get_rank(int value, t_stack *sorted_tmp) {
  size_t j;
  j = 0;
  while (j < sorted_tmp->size) {
    if (value == sorted_tmp->stack[j])
      return ((int)j);
    j++;
  }
  return (-1);
}

t_stack *index_stack(t_stack *s) {
  t_stack *new;
  t_stack *tmp;
  size_t i;

  new = alloc_stack(s->size);
  if (!new)
    return NULL;
  tmp = dup_stack(s);
  if (!tmp)
    return (free_stack(new), NULL);
  new->size = s->size;
  stack_sort(tmp);
  i = 0;
  while (i < s->size) {
    new->stack[i] = get_rank(s->stack[i], tmp);
    i++;
  }
  free_stack(tmp);
  return (new);
}

int error() {
  write(1, "Error\n", 6);
  return 1;
}

t_stack *prepare_stack(int *nums, size_t size) {
  t_stack *a, *indexed;
  a = init_stack(nums, size);
  if (!a || has_duplicates(a))
    return (free_stack(a), NULL);
  indexed = index_stack(a);
  free_stack(a);
  return indexed;
}

int main(int argc, char **argv) {
  t_stack *b;
  t_stack *a;
  // test();

  if (argc < 2)
    return error();
  int *nums = parse_ints(&argv[1], argc - 1);
  if (!nums)
    return error();
  a = prepare_stack(nums, argc - 1);
  free(nums);
  if (!a)
    return error();
  if (stack_is_sorted(a))
    return 0;
  b = alloc_stack(a->size);
  if (!b)
    return (free_stack(a), error());
  if (a->size == 3)
    sort_three(a);
  else
    radix(a, b);
  return (free_stack(a), free_stack(b), 0);
}

// TODO:
// 2 1 0: 2 or 3 ops
// 1 5 2 4 3: 12 ops
// 5 random: 12 ops
// 100: 700 ops
// 500: 5500 ops
