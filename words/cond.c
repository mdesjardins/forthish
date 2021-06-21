
#include "../typedefs.h"
#include "../stack.h"

/** Conditionals **/

/* ( n1 n2 -- flag ) replaces top to stack elements with -1 (equal) or 0 (not equal) */
param_stack_elem equals(void) {
  param_stack_elem n2 = pop();
  param_stack_elem n1 = pop();
  if (n1 == n2) {
    push(-1);
  } else {
    push(0);
  }
  return 0;
}
