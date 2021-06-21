#ifndef COND_H
#define COND_H

#include "../typedefs.h"
#include "../stack.h"

/* ( n1 n2 -- flag ) replaces top to stack elements with -1 (equal) or 0 (not equal) */
param_stack_elem equals(void);

#endif /* COND_H */