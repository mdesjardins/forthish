#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <stdbool.h>
#include "stdint.h"

typedef int16_t cell;
typedef int32_t double_cell;
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

typedef void (*word)(void);

#endif /* TYPEDEFS_H */
