#ifndef VM_H
#define VM_H

#include "constants.h"
#include "typedefs.h"
#include "dict.h"

typedef struct vm_flags_t {
  unsigned int compiling : 1;
} vm_flags_t;

/* TODO alignment - make arrays instead of heap alloc in vm.c? */
typedef struct vm_t {
    vm_flags_t flags;
    char tib[INPUT_BUFFER_SIZE]; /* text input buffer */
    char* in; /* pointer to current position in input stream >IN */
    word_node dict[DICTIONARY_CELLS];
    word_node* cp;        /* next spot for a word */
    word_node* dict_buf_end;  /* end of word buffer */
    word_node* dict_head; /* last dictionary entry */
    cell data_stack[DATA_STACK_SIZE];
    cell* sp; /* stack pointer */
    cell* data_stack_start;  /* to check for underflows */
    cell* data_stack_end;    /* to check for overflows */
    cell memory[MEMORY_CELLS]; /* general memory buffers, may not need. */
} vm_t;

extern vm_t vm;

void vm_init();

/* not sure this really belongs here, but whatev... stack push/pop */
void data_push(cell i);
cell data_pop();

#endif /* VM_H */
