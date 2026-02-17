#include "utils.h"
#include <limits.h>
#include <unistd.h>

static bool intbit(int n, int pos) {
  if (pos > 31)
    return false;
  return ((n >> pos) & 1) == 1;
}

static void radix_bit(t_stack *a, t_stack *b, int bit) {
  size_t i = 0;
  size_t count = a->size;
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

static int msb_pos_int(int x) {
  int pos;

  if (x == 0)
    return (-1);
  pos = 0;
  while ((unsigned int)x > 1) {
    x >>= 1;
    pos++;
  }
  return (pos);
}

static int stack_max(t_stack *s) {
  int max = INT_MIN;
  size_t i = 0;
  while (i < s->size) {
    if (s->stack[i] > max)
      max = s->stack[i];
    i++;
  }
  return max;
}

void radix(t_stack *a, t_stack *b) {
  int i = 0;
  int max = stack_max(a);
  int bits = msb_pos_int(max) + 1;
  while (i < bits && !stack_is_sorted(a)) // max
    radix_bit(a, b, i++);
}
