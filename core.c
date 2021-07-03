
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "core.h"
#include "words.h"
#include "constants.h"
#include "typedefs.h"


/************** Dictionary ***************/


void dict_init() {
  dict_prepend(word_build(".", pop, false));
  dict_prepend(word_build(".s", show, false));
  dict_prepend(word_build("emit", emit, false));
  dict_prepend(word_build("+", add, false));
  dict_prepend(word_build("-", subtract, false));
  dict_prepend(word_build("=", equals, false));
  dict_prepend(word_build(":", compile, false));
  dict_prepend(word_build(";", stop_compile, true));
  dict_prepend(word_build("'", tick, false));
  dict_prepend(word_build("execute", execute, false));
}

word_node* word_build(const char* name, void (*pf)(void), bool precedence) {
  word_node* new_word = vm.cp;
  new_word->precedence = precedence;
  new_word->name = strndup(name, MAX_WORD_LENGTH);
  new_word->pf = pf;
  return new_word;
}

/*
 * vm.cp - points to next open spot
 * vm.dict_head - points to "top" of last word.
 * node.next - points to top of next word.
 */
void dict_prepend(word_node* node) {
  /* TODO need a bounds check w/ dict_end */
  /* TODO sizeof won't work when word sizes vary */
  node = (word_node *)memcpy(vm.cp, node, sizeof(word_node));

  /* First word in, next needs to be null */
  if (vm.cp == vm.dict) {
    node->next = NULL;
  } else {
    node->next = vm.dict_head;
  }
  vm.dict_head = node;

  /* TODO sizeof won't work when word sizes vary */
  vm.cp = vm.dict_head + sizeof(node);
}

/* this itself could be a word if we didn't worry about passing params? */
word_node* dict_find(const char* name) {
  word_node* current = vm.dict_head;  /* top of last word */
  while (current >= vm.dict) {
    if (strncmp(name, current->name, MAX_WORD_LENGTH) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

/* Generates an execution token (xt) for a dict entry. In our implementation,
   the xt is an offset from the start of the dictionary to the start of our
   word definition */
cell dict_xt_for(word_node* node) {
  return (cell)(node - vm.dict);
}


/************** TIB ***************/

void reset_tib() {
  memset(vm.tib, 0, INPUT_BUFFER_SIZE);
  vm.in = vm.tib;
}

/* Needs a little work - adjacent delimiters, overflow? */
int next_token(char* dest) {
  int n = MAX_WORD_LENGTH - 1;
  char c;
  if (*vm.in == '\0') {
    return 0;
  }
  while (n--) {
    c = *vm.in++;
    if (isspace(c)) {
      break;
    }
    *dest++ = c;
  }
  *dest++ = '\0';
  return n;
}


/************** VM/Context ****************/

vm_t vm;

void vm_init() {
  vm.flags.compiling = 0;
  vm.in = vm.tib;

  /* dictionary */
  vm.cp = vm.dict_head = vm.dict;
  vm.dict_buf_end = vm.dict + DICTIONARY_CELLS;

  /* data stack */
  vm.sp = vm.data_stack;
  vm.data_stack_start = vm.data_stack;
  vm.data_stack_end = vm.data_stack + DATA_STACK_SIZE;

  /* todo - memset to 0? */
}


/************** Stack ********************/

/* maybe these could be macros? or use inline? */

void data_push(cell i) {
  if (vm.sp >= vm.data_stack_end) {
    fprintf(stderr, "Stack overflow.\n");
  }
  *vm.sp = i;
  vm.sp++;
  return;
}

cell data_pop() {
  if (vm.sp <= vm.data_stack_start) {
    fprintf(stderr, "Stack underflow.\n");
  }
  vm.sp--;
  return *vm.sp;
}

/************** Misc. Utils ***************/


/* todo fix */
bool is_num(char* input) {
  int i = 0;
  if (input[0] == '\0') {
    return false;
  }

  while (!iscntrl(input[i])) {
    if (!isdigit(input[i])) {
      return false;
    }
    i++;
  }
  return true;
}


