
#include <stdio.h>
#include "../typedefs.h"
#include "../vm.h"

/*
 * should probably look more like this:
 * .s <1> 2  ok
 */
void show(void) {
  cell* current = vm.data_stack_start;
  do {
    fprintf(stdout, "%d ", *current);
  } while (++current < vm.sp);
  fprintf(stdout, "\n");
  return;
}

void pop(void) {
  data_pop();
}
