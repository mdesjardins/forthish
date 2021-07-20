#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include "constants.h"
#include "typedefs.h"

/* Word things */


word_node* word_build(const char* name, void (*pf)(void), bool precedence);

/* Dictionary things */

void dict_init();
void dict_prepend(word_node* node);
int dict_word_count();
word_node* dict_find(const char* name);
cell dict_xt_for(word_node* node);
//void run(word_node* word);

/* TIB Things */

int next_token(char* dest);
void reset_tib(void);


/* VM/Context Things */

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
    cell return_stack[RETURN_STACK_SIZE];
    cell* rsp;
    cell* return_stack_start;
    cell* return_stack_end;
    cell memory[MEMORY_CELLS]; /* general memory buffers, may not need. */
} vm_t;

extern vm_t vm;

void vm_init();

/* Stack Things */

void data_push(cell i);
cell data_pop();
void return_push(cell i);
cell return_pop();

/* Misc Things */

bool is_num(char* input);

#endif /* CORE_H */
