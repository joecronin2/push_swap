#include <unistd.h>
#include <limits.h>
#include "utils.h"


static bool intbit(int n, int pos) {
  if (pos > 31)
    return false;
  return ((n >> pos) & 1) == 1;
}


static void radix_bit(t_stack *a, t_stack *b, int bit) {
  size_t i = 0;
  // if (stack_is_sorted(a))
  //   return;
  while (i < a->size) {
    int atop = a->stack[a->size - 1];
    if (!intbit(atop, bit)) {
      stack_push(a, b);
      write(1, "pb\n", 3);
      if (b->size > 1 && b->stack[0] < b->stack[1]) {
        stack_rotate_up(b);
        write(1, "rb\n", 3);
      }
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
  if (x == 0)
    return -1;
  return 31 - __builtin_clz((unsigned int)x);
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
  while (i < bits) // max
    radix_bit(a, b, i++);
}

