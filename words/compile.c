
#include "../typedefs.h"
#include "../vm.h"

void define(void) {
  vm.flags.compiling = 1;
}

void stop_define(void) {
  vm.flags.compiling = 0;
}

void create(void) {
  
}
