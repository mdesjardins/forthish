#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"
#include "dictutil.h"
#include "typedefs.h"
#include "constants.h"
#include "tibutil.h"
#include "words/stack.h"

bool is_number(char* input) {
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

/* Executes a single word */
void process(char *token) {
  word_node* word = dict_find(token);
  if (word) {
    word->pf();
  } else if (is_number(token)) {
    /* this needs more work, we need to invoke number word, handle doubles */
    data_push(atoi(token));
  } else {
    fprintf(stderr, "%s? ", token);
  }
}

void interpret() {
  vm.tib[strcspn(vm.tib, "\r\n")] = 0;  /* chomp carriage returns (should probably deal w/ elsewhere) */

  char token[MAX_WORD_LENGTH];
  int i = 0;
  while (next_token(token)) {
    //vm.in = tokens[i];
    //if (!vm.flags.compiling) {
      process(token);
      //} else {
      //compile(&token);
      //}
    i++;
  } // while(tokens[i][0] != 0);
}

/* Main REPL/Input loop */
int main() {
  vm_init();
  dict_init();

  bool loop = true ;

  while (loop) {
    fputs("> ", stdout);
    fgets(vm.tib, INPUT_BUFFER_SIZE, stdin);
    interpret();
    reset_tib();
    fputs("ok.\n", stdout);
  }
}
