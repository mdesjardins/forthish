
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "typedefs.h"
#include "vm.h"

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

