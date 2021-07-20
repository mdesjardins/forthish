
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../typedefs.h"
#include "../core.h"
#include "../constants.h"
#include "../words.h"

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

  /* invoke create instead? */
  word_node* new_word = word_build(name, NULL, false);
  new_word->code = run;

  char token[MAX_WORD_LENGTH];
  cell* ip = new_word->data;
  while (next_token(token) && vm.flags.compiling) {
    if (token[0] != '\0') {
      word_node* word = dict_find(token);
      if (word) {
        if (word->flags.precedence) {
          word->code();
        } else {
          // 1. create a dictionary entry with name
          // 2. add the pointer-to-function for... new "run" core fcn?
          // 3. add invoked function to data section.
          // this is sorta gonna depend on whether we're defining a word, variable, or constant.
          data_push(sizeof(cell));
          allot();
          cell xt = dict_xt_for(word);
          *ip = xt;         /* add XT to the data section */
          ip++;             /* increment instruction pointer */
          fprintf(stderr, "    added to the definition: %s\n", token);
        }
      } else if (is_num(token)) {
        /* need to push a literal onto the function list */
      } else {
        fprintf(stderr, "    %s? ", token);
        vm.flags.compiling = 0;  /* move somewhere else */
      }
    }
  }

  /* Add one last "xt" (NULL) that indicates we're at the end for now. */
  data_push(sizeof(cell));
  allot();
  new_word->data = NULL;
  dict_prepend(new_word);

  vm.flags.compiling = 0;
}

