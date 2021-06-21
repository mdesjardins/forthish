#ifndef STACK_H
#define STACK_H

#include "typedefs.h"

int push(int i);
param_stack_elem pop();
int show();
param_stack_elem* get_stack();
int get_stack_depth();

#endif  /* STACK_H */
