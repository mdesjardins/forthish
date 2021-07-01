
#include "../typedefs.h"
#include "../vm.h"
#include "../tibutil.h"
#include "../constants.h"
#include "../dictutil.h"


void define(void) {
  vm.flags.compiling = 1;
}

void stop_define(void) {
  vm.flags.compiling = 0;
}

void create(void) {
  
}
