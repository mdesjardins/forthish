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
#include "words/stack.h"

mode current_mode = INTERPRET;

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

/* Mutates words! */
void tokenize(char words[][MAX_WORD_LENGTH]) {
  memset(words, 0, MAX_WORDS_IN_BUFFER*MAX_WORD_LENGTH);
  int i = 0;

  const char* delim = " ";
  char* next_token;
  char* token = strtok_r(vm.input_buf, delim, &next_token);
  while (token) {
    strncpy(words[i], token, MAX_WORD_LENGTH);
    token = strtok_r(NULL, delim, &next_token);
    i++;
  }
  //todo multiple spaces?
}

void process() {
  vm.input_buf[strcspn(vm.input_buf, "\r\n")] = 0;  /* chomp carriage returns */
  char words[MAX_WORDS_IN_BUFFER][MAX_WORD_LENGTH];

  tokenize(words);

  int i = 0;
  do {
    /* this needs more work, we need to invoke number word, handle doubles */
    if (current_mode == INTERPRET) {
      /* TODO fix backward order here */
      if (is_number(words[i])) {
        push(atoi(words[i]));
      } else {
        /* need to handle lookahead for things like VARIABLE */
        interp_result result = interpret(words[i]);
        if (result == COMPILE_MODE) {
          current_mode = COMPILE;
        }
      }
    } else {
      //      compile(words)
      fputs("compile.\n", stdout);
    }
    i++;
  } while(words[i][0] != 0);
}

/* Main REPL/Input loop */
int main() {
  vm_init();
  dict_init();

  bool loop = true ;

  while (loop) {
    fputs("> ", stdout);
    fgets(vm.input_buf, INPUT_BUFFER_SIZE, stdin);
    process();
    fputs("ok.\n", stdout);
  }
}
