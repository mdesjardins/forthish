
#include <strings.h>
#include <ctype.h>
#include "constants.h"
#include "vm.h"
#include "tib.h"

void reset_tib() {
  memset(vm.tib, 0, INPUT_BUFFER_SIZE);
  vm.in = vm.tib;
}

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
