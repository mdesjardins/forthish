
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

  fprintf(stderr, "2222222\n");
  
  char token[MAX_WORD_LENGTH];
  cell* ip = new_word->data;
  while (next_token(token) && vm.flags.compiling) {
    fprintf(stderr, "3 %s\n", token);

    if (token[0] != '\0') {
      word_node* word = dict_find(token);
      if (word) {
        fprintf(stderr, "4 %s\n", token);

        if (word->flags.precedence) {
          word->code();
        } else {
          fprintf(stderr, "5 %d + %d\n", vm.cp, sizeof(cell));

          // 1. create a dictionary entry with name
          // 2. add the pointer-to-function for... new "run" core fcn?
          // 3. add invoked function to data section.
          // this is sorta gonna depend on whether we're defining a word, variable, or constant.
          data_push(sizeof(cell));
          fprintf(stderr, "6 %d\n", vm.cp);

          allot();
          fprintf(stderr, "7 %d\n", vm.cp);

          cell xt = dict_xt_for(word);
          fprintf(stderr, "8 %s\n", token);

          *ip = xt;         /* add XT to the data section */
          ip++;             /* increment instruction pointer */

          fprintf(stderr, "9 %s\n", token);

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

  /* Add the exit instruction */
#if 0
  word_node* exit = dict_find("exit");
  allot();
  cell xt = dict_xt_for(exit);
  *ip = xt;         /* add XT to the data section */
  ip++;             /* increment instruction pointer */
  fprintf(stderr, "    added to the definition: %s\n", token);
#endif

  fprintf(stderr, "111\n");
  
  /* Add one last "xt" (NULL) that indicates we're at the end for now. */
  data_push(sizeof(cell));
  allot();
  new_word->data = NULL;
  dict_prepend(new_word);

  vm.flags.compiling = 0;
}

