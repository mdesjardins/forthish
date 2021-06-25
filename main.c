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

/* Executes a single word */
void execute(char *token) {
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
  int i = 1;
  do {
    char* token = tokens[i];
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
    }

    fprintf(stderr, "compile: %s\n", token);
    i++;
  } while(tokens[i][0] != 0);
}

void process() {
  vm.input_buf[strcspn(vm.input_buf, "\r\n")] = 0;  /* chomp carriage returns */
  char tokens[MAX_WORDS_IN_BUFFER][MAX_WORD_LENGTH];

  tokenize(tokens);

  int i = 0;
  do {
    if (!vm.flags.compiling) {
      execute(tokens[i]);
    } else {
      compile(&tokens[i]);
    }
    i++;
  } while(tokens[i][0] != 0);
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
