#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "dict.h"

#define CHARSIZE 1024
#define MAXWORDS 512

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
void tokenize(char* input, char words[][CHARSIZE]) {
  memset(words, 0, MAXWORDS*CHARSIZE);
  int i = 0;

  const char* delim = " ";
  char* next_token;
  char* token = strtok_r(input, delim, &next_token);
  while (token) {
    strncpy(words[i], token, CHARSIZE);
    token = strtok_r(NULL, delim, &next_token);
    i++;
  }
  //todo multiple spaces?
}

void process(char* input, char words[][CHARSIZE]) {
  input[strcspn(input, "\r\n")] = 0;  /* chomp carriage returns */
  tokenize(input, words);

  int i = 0;
  do {
    /* this needs more work, we need to invoke number word, handle doubles */
    if (is_number(input)) {
      push(atoi(input));
    } else {
      /* need to handle lookahead for things like VARIABLE */
      eval(words[i]);
    }
    i++;
  } while(words[i][0] != 0);
}

/* Main REPL/Input loop */
int main() {
  dict_init();

  bool loop = true ;
  char response[CHARSIZE];
  char words[MAXWORDS][CHARSIZE];

  while (loop) {
    fputs("> ", stdout);
    fgets(response, CHARSIZE, stdin);
    process(response, words);
    fputs("ok.\n", stdout);
  }
}
