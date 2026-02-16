#include "push_swap.h"
#include "utils.h"

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

static void stack_sort(t_stack *s) {
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
