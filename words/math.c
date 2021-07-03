
#include "math.h"
#include "stack.h"
#include "../core.h"

/* ( n1 n2 -- sum ) replaces top two stack elements with sum of top two stack elements. */
void add(void) {
  param_stack_elem n2 = data_pop();
  param_stack_elem n1 = data_pop();
  data_push(n1 + n2);
  return;
}

/* ( n1 n2 -- difference ) replaces top two stack elements with difference between top two stack elements. */
void subtract(void) {
  param_stack_elem n2 = data_pop();
  param_stack_elem n1 = data_pop();
  data_push(n1 - n2);
  return;
}
