
#include "math.h"
#include "stack.h"


/* ( n1 n2 -- sum ) replaces top two stack elements with sum of top two stack elements. */
param_stack_elem add(void) {
  param_stack_elem n2 = pop();
  param_stack_elem n1 = pop();
  push(n1 + n2);
  return 0;
}

/* ( n1 n2 -- difference ) replaces top two stack elements with difference between top two stack elements. */
param_stack_elem subtract(void) {
  param_stack_elem n2 = pop();
  param_stack_elem n1 = pop();
  push(n1 - n2);
  return 0;
}
