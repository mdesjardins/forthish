
#include "../typedefs.h"
#include "../vm.h"

/* ( n1 n2 -- flag ) replaces top to stack elements with -1 (equal) or 0 (not equal) */
void equals(void) {
  param_stack_elem n2 = data_pop();
  param_stack_elem n1 = data_pop();
  if (n1 == n2) {
    data_push(-1);
  } else {
    data_push(0);
  }
  return;
}
