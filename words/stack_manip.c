
#include <stdio.h>
#include "../typedefs.h"
#include "../stack.h"

/** Stack Manipulation **/

/*
 * should probably look more like this:
 * .s <1> 2  ok
 */
param_stack_elem show_stack(void) {
  int stack_depth = get_stack_depth();
  for (int i=0; i<stack_depth; i++) {
    fprintf(stdout, "%d ", get_stack()[i]);
  }
  fprintf(stdout, "\n");
  return 0;
}

param_stack_elem pop_stack(void) {
  return pop();
}
