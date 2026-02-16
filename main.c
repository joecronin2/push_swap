#include "push_swap.h"
#include <libft.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h> // TODO
#include <stdlib.h>
#include <unistd.h>

// expects valid, null terminated int.
bool ft_strtoi(const char *str, int *out) {
  long n;
  int negative;
  int digit;

  n = 0;
  negative = (*str == '-');
  if (*str == '+' || *str == '-')
    str++;
  if (!ft_isdigit(*str))
    return (false);
  while (ft_isdigit(*str)) {
    digit = *str - '0';
    n = n * 10 + digit;
    str++;
  }
  if (*str != '\0')
    return (false);
  if (negative)
    n = -n;
  *out = (int)n;
  return (n >= INT_MIN && n <= INT_MAX);
}

void free_stack(t_stack *stack) {
  if (stack) {
    free(stack->stack);
    free(stack);
  }
}

t_stack *alloc_stack(size_t size) {
  t_stack *stack;

  stack = malloc(sizeof(*stack));
  if (!stack)
    return (NULL);
  stack->stack = malloc(sizeof(int) * size);
  if (!stack->stack)
    return (free(stack), NULL);
  stack->size = 0;
  return (stack);
}

t_stack *init_stack(int *nums, size_t size) {
  t_stack *stack = alloc_stack(size);
  if (!stack)
    return NULL;
  ft_memcpy(stack->stack, nums, size * sizeof(int));
  stack->size = size;
  return (stack);
}

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

t_stack *dup_stack(t_stack *stack) {
  t_stack *new = alloc_stack(stack->size);
  if (!new)
    return NULL;
  ft_memcpy(new->stack, stack->stack, stack->size * sizeof(int));
  new->size = stack->size;
  return new;
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

bool stack_push(t_stack *from, t_stack *to) {
  if (from->size < 1)
    return false;
  int n = from->stack[--from->size];
  to->stack[to->size++] = n;
  return true;
}

bool stack_enqueue(t_stack *from, t_stack *to) {
  if (from->size < 1)
    return false;
  int value = from->stack[--from->size];
  if (to->size > 0)
    ft_memmove(&to->stack[1], &to->stack[0], to->size * sizeof(int));
  to->stack[0] = value;
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

// first becomes last
void stack_rotate_up(t_stack *s) {
  if (s->size < 2)
    return;
  int last = s->stack[s->size - 1];
  ft_memmove(&s->stack[1], &s->stack[0], (s->size - 1) * sizeof(int));
  s->stack[0] = last;
}

// last becomes first
void stack_rotate_down(t_stack *s) {
  if (s->size < 2)
    return;
  int first = s->stack[0];
  ft_memmove(&s->stack[0], &s->stack[1], (s->size - 1) * sizeof(int));
  s->stack[s->size - 1] = first;
}

// 0101

bool intbit(int n, int pos) {
  if (pos > 31)
    return false;
  return ((n >> pos) & 1) == 1;
}

void radix_bit(t_stack *a, t_stack *b, int bit) {
  size_t count = a->size;
  size_t i = 0;
  while (i < count) {
    int atop = a->stack[a->size - 1];
    if (!intbit(atop, bit)) {
      stack_push(a, b);
      write(1, "pb\n", 3);
    } else {
      stack_rotate_up(a);
      write(1, "ra\n", 3);
    }
    i++;
  }
  while (b->size > 0) {
    stack_push(b, a);
    write(1, "pa\n", 3);
  }
}

int stack_max(t_stack *s) {
  int max = INT_MIN;
  size_t i = 0;
  while (i < s->size) {
    if (s->stack[i] > max)
      max = s->stack[i];
    i++;
  }
  return max;
}

int msb_pos_int(int x) {
  if (x == 0)
    return -1;
  return 31 - __builtin_clz((unsigned int)x);
}

// fuck it we ball push_swap aint got shit on me
void radix(t_stack *a, t_stack *b) {
  int i = 0;
  int max = stack_max(a);
  int bits = msb_pos_int(max) + 1;
  while (i < bits) // max
    radix_bit(a, b, i++);
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

#include <assert.h>
// 5 101
// 2 010
// 7 111
// 1 001
// 4 100
// 0 000
// 6 110
// 3 011

// 0b101,0b010,0b111,0b001,0b100,0b000,0b110,0b011

void test_index() {
  t_stack *s = init_stack((int[]){5, 4, 3, 2, 1}, 5);
  // t_stack *i = index_stack(s);
}

void test_radix() {
  t_stack *a = init_stack(
      (int[]){0b101, 0b010, 0b111, 0b001, 0b100, 0b000, 0b110, 0b011}, 8);
  t_stack *b = alloc_stack(8);
  radix(a, b);
  free_stack(a);
  free_stack(b);
}

void test_intbit() {
  int b = 0b10110001;
  assert(intbit(b, 0));
  assert(!intbit(b, 1));
  assert(!intbit(b, 2));
  assert(!intbit(b, 3));
  assert(intbit(b, 4));
  assert(intbit(b, 5));
  assert(!intbit(b, 6));
  assert(intbit(b, 7));
}

bool arr_eq(int *a, int *b, size_t size) {
  for (size_t i = 0; i < size; i++)
    if (a[i] != b[i])
      return false;
  return true;
}

void test_rotate() {
  // {
  //   int orig[] = {1, 2, 3, 4};
  //   t_stack *s = init_stack(orig, sizeof(orig) / sizeof(int));
  //   t_stack *b = init_stack((int[]){5}, 1);
  // stack_enqueue(b, s);
  //   free(s);
  // }
  {
    int orig[] = {1, 2, 3, 4, 5};
    t_stack *s = init_stack(orig, sizeof(orig) / sizeof(int));
    stack_rotate_up(s);
    assert(
        arr_eq((int[]){5, 1, 2, 3, 4}, s->stack, sizeof(orig) / sizeof(int)));
    stack_rotate_down(s);
    assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
    free(s);
  }
  {
    int orig[] = {1, 2};
    t_stack *s = init_stack(orig, sizeof(orig) / sizeof(int));
    stack_rotate_up(s);
    assert(arr_eq((int[]){2, 1}, s->stack, sizeof(orig) / sizeof(int)));
    stack_rotate_down(s);
    assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
    free(s);
  }
  {
    int orig[] = {1};
    t_stack *s = init_stack(orig, sizeof(orig) / sizeof(int));
    stack_rotate_up(s);
    assert(arr_eq((int[]){1}, s->stack, sizeof(orig) / sizeof(int)));
    stack_rotate_down(s);
    assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
    free(s);
  }
  {
    int orig[] = {1, 2, 3, 4};
    t_stack *s = init_stack(orig, sizeof(orig) / sizeof(int));
    stack_rotate_up(s);
    assert(arr_eq((int[]){4, 1, 2, 3}, s->stack, sizeof(orig) / sizeof(int)));
    stack_rotate_down(s);
    assert(arr_eq(orig, s->stack, sizeof(orig) / sizeof(int)));
    free(s);
  }
}

void test_strtoi(void) {
  int i;

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

void test_stack(void) {
  t_stack *stack = init_stack((int[]){5, 4, 3}, 3);
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

void test_duplicates() {
  {
    t_stack *s = init_stack((int[]){1, 2, 3}, 3);
    assert(!has_duplicates(s));
    free(s);
  }
  {
    t_stack *s = init_stack((int[]){1, 2, 2}, 3);
    assert(has_duplicates(s));
    free(s);
  }
  {
    t_stack *s = init_stack((int[]){1, 4, 3, 4}, 4);
    assert(has_duplicates(s));
    free(s);
  }
}

void test() {
  test_duplicates();
  test_radix();
  test_intbit();
  test_rotate();
  test_index();
  test_stack();
  test_strtoi();
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
  radix(a, b);
  return (free_stack(a), free_stack(b), 0);
}
