#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"
#include "dict.h"
#include "typedefs.h"
#include "constants.h"
#include "tib.h"
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

/* Compiles a new definition */
void compile(char tokens[][MAX_WORD_LENGTH]) {
  char* name = tokens[0];

  /* allot? */

  int i = 1;
  do {
    char* token = tokens[i];
    vm.in = token;
    word_node* word = dict_find(token);
    fprintf(stderr, "word: %s\n", token);
    if (word) {
      if (word->precedence) {
        word->pf();
      } else {
        fprintf(stderr, "add to the definition: %s\n", token);
      }
    } else if (is_number(token)) {
      /* need to push a literal onto the function list */
    } else {
      fprintf(stderr, "%s? ", token);
      vm.flags.compiling = 0;  /* move somewhere else */
    }

    fprintf(stderr, "compile: %s\n", token);
    i++;
  } while(tokens[i][0] != 0);
}

void interpret() {
  vm.tib[strcspn(vm.tib, "\r\n")] = 0;  /* chomp carriage returns (should probably deal w/ elsewhere) */

  char token[MAX_WORD_LENGTH];
  int i = 0;
  while (next_token(token)) {
    //vm.in = tokens[i];
    if (!vm.flags.compiling) {
      process(token);
    } else {
      compile(&token);
    }
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
