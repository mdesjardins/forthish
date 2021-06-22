#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <stdbool.h>
#include "stdint.h"

/* We have 32 bit cells, which is a bit unconventional I guess. */
typedef int32_t cell;
typedef int64_t double_cell;
typedef cell param_stack_elem;
typedef cell return_stack_elem;

typedef enum {
  INTERPRET,
  COMPILE
} mode;

typedef enum {
  OK,
  ABORT,
  COMPILE_MODE,
  INTERPRET_MODE
} interp_result;

typedef bool compile_result;

#endif /* TYPEDEFS_H */
