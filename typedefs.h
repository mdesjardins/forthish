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

/* Our dictionary is a linked list of word nodes, probably should align. */
typedef struct word_node_flags_t {
    unsigned int precedence : 1;
} word_node_flags_t;

typedef struct word_node {
    word_node_flags_t flags;
    const char* name;
    void (*code)(void);
    struct word_node* link;
    cell* data;
} word_node;

#endif /* TYPEDEFS_H */
