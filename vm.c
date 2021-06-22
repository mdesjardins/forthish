
#include <stdlib.h>
#include "constants.h"
#include "typedefs.h"
#include "vm.h"

vm_t vm;

void vm_init() {
  vm.input_buf = (char *)malloc(sizeof(cell) * INPUT_BUFFER_SIZE);

  /* dictionary */
  vm.dict = (word_node *)malloc(sizeof(cell) * DICTIONARY_CELLS);
  vm.dict_start = vm.dict;
  vm.cp = vm.dict;
  vm.dict_end = vm.dict + DICTIONARY_CELLS;

  /* data stack */
  vm.data_stack = (cell *)malloc(sizeof(cell) * DATA_STACK_SIZE);
  vm.sp = vm.data_stack;
  vm.data_stack_start = vm.data_stack;
  vm.data_stack_end = vm.data_stack + DATA_STACK_SIZE;

  /* buffers */
  vm.memory = (cell *)malloc(sizeof(cell) * MEMORY_CELLS);
}
