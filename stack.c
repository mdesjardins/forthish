
#include "stack.h"
#include "constants.h"
#include <stdio.h>

param_stack_elem stack[DATA_STACK_SIZE];
int stack_depth = 0;

/* For now this is a ridiculous fixed array... will make it alloc eventually */

int push(int i) {
  if (stack_depth >= DATA_STACK_SIZE) {
    fprintf(stderr, "Stack overflow.\n");
  }
  stack[stack_depth] = i;
  return stack_depth++;
}

param_stack_elem pop() {
  return stack[--stack_depth];
}

int show() {
  for (int i=0; i<stack_depth; i++) {
    fprintf(stdout, "%d ", stack[i]);
  }
  fprintf(stdout, "\n");
  return 0;
}

// allows mutation!
param_stack_elem* get_stack() {
  return stack;
}

int get_stack_depth() {
  return stack_depth;
}
