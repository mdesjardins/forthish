#include <stdio.h>
#include "../constants.h"
#include "../vm.h"
#include "io.h"

/* ( x -- ) displays top of stack as ASCII */
void emit(void) {
  param_stack_elem top = data_pop();
  if (top < 0 || top > MAX_RENDERABLE_ASCII) {
    fprintf(stderr, "Unable to render character %d", top);
    return;
  }
  fprintf(stdout, "%c", (char)top);
  return;
}
