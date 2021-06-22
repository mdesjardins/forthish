
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dict.h"
#include "words.h"
#include "constants.h"
#include "typedefs.h"
#include "vm.h"

void dict_init() {
  dict_prepend(word_build(".", pop));
  dict_prepend(word_build(".s", show));
  dict_prepend(word_build("emit", emit));
  dict_prepend(word_build("+", add));
  dict_prepend(word_build("-", subtract));
  dict_prepend(word_build("=", equals));
}

word_node* word_build(const char* name, param_stack_elem (*pf)(void)) {
  word_node* new_word = vm.cp;
  new_word->precedence = false;
  new_word->name = strndup(name, MAX_WORD_LENGTH);
  new_word->pf = pf;
  vm.cp = vm.cp + sizeof(new_word);
  return new_word;
}

void dict_prepend(word_node* node) {
  node->next = vm.dict;
  vm.dict = node;
}

/* this itself should be a word */
word_node* dict_find(const char* name) {
  word_node* current = vm.dict;
  while (current != NULL && current <= vm.cp) {
    if (strncmp(name, current->name, MAX_WORD_LENGTH) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

interp_result interpret(const char* name) {
  word_node* word = dict_find(name);
  if (word) {
    /* maybe compile here? no, can't because don't have all words. */
    word->pf();
    return OK;
  }

  /* error */
  fprintf(stderr, "%s?", name);
  return ABORT; /* ?? */
}
