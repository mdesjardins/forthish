#ifndef VM_H
#define VM_H

#include "constants.h"
#include "typedefs.h"
#include "dict.h"

/* TODO alignment */
typedef struct vm_t {
    char* input_buf;
    word_node* dict;
    word_node* dict_start;
    word_node* dict_end;
    word_node* cp; /* next dictionary entry */
    cell* sp; /* stack pointer */
    cell* data_stack;
    cell* data_stack_start;  /* to check for underflows */
    cell* data_stack_end;    /* to check for overflows */
    cell* memory; /* general memory buffers, may not need. */
} vm_t;

extern vm_t vm;

void vm_init();

#endif /* VM_H */
