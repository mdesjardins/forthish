
#include <stdio.h>
#include "../typedefs.h"
#include "../vm.h"

/** Stack Manipulation **/

/*
 * should probably look more like this:
 * .s <1> 2  ok
 */
param_stack_elem show(void) {
  cell* current = vm.data_stack_start;
  do {
    fprintf(stdout, "%d ", *current);
  } while (++current < vm.sp);
  fprintf(stdout, "\n");
  return 0;
}

void push(cell i) {
  if (vm.sp >= vm.data_stack_end) {
    fprintf(stderr, "Stack overflow.\n");
  }
  *vm.sp = i;
  vm.sp++;
  return;
}

cell pop() {
  if (vm.sp <= vm.data_stack_start) {
    fprintf(stderr, "Stack underflow.\n");
  }
  vm.sp--;
  return *vm.sp;
}
