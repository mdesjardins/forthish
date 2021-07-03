
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../typedefs.h"
#include "../core.h"
#include "../constants.h"


void stop_compile(void) {
  vm.flags.compiling = 0;
}

void compile(void) {
  vm.flags.compiling = 1;

  char name[MAX_WORD_LENGTH];
  if (!next_token(name)) {
    /* abort */
    return;
  }
  fprintf(stderr, "compiling word: %s\n", name);

  /* allot? */

  int i = 1;
  char token[MAX_WORD_LENGTH];
  while (next_token(token) && vm.flags.compiling) {
    fprintf(stderr, "loop.\n");
    if (token[0] != '\0') {
      fprintf(stderr, " token: %s\n", token);
      word_node* word = dict_find(token);
      if (word) {
        fprintf(stderr, "  found: %s\n", token);
        if (word->precedence) {
          fprintf(stderr, "    executing due to precendence: %s\n", token);
          word->pf();
        } else {
          fprintf(stderr, "    add to the definition: %s\n", token);
        }
      } else if (is_num(token)) {
        /* need to push a literal onto the function list */
      } else {
        fprintf(stderr, "    %s? ", token);
        vm.flags.compiling = 0;  /* move somewhere else */
      }
    }
    fprintf(stderr, "end loop.\n");
  }

  vm.flags.compiling = 0;
}

