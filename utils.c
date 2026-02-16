#include "libft/libft.h"
#include "utils.h"
#include <limits.h>

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
