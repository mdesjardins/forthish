#include <stdio.h>
#include "../constants.h"
#include "stack.h"
#include "io.h"

/* ( x -- ) displays top of stack as ASCII */
param_stack_elem emit(void) {
  param_stack_elem top = pop();
  if (top < 0 || top > MAX_RENDERABLE_ASCII) {
    fprintf(stderr, "Unable to render character %d", top);
    return -1;
  }
  fprintf(stdout, "%c", (char)top);
  return top;
}
