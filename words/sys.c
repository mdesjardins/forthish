
#include "../typedefs.h"
#include "../vm.h"
#include "../dict.h"
#include "sys.h"


void execute(void) {
  /* problem - a pointer to a function is larger than a cell. */
  /* we won't be able to use addresses as our  execution token? */
  word xt = (word)data_pop();
  xt();
}

void tick(void) {
  
}
