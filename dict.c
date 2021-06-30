
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
  dict_prepend(word_build(".", pop, false));
  dict_prepend(word_build(".s", show, false));
  dict_prepend(word_build("emit", emit, false));
  dict_prepend(word_build("+", add, false));
  dict_prepend(word_build("-", subtract, false));
  dict_prepend(word_build("=", equals, false));
  dict_prepend(word_build(":", define, false));
  dict_prepend(word_build(";", stop_define, true));
}

word_node* word_build(const char* name, void (*pf)(void), bool precedence) {
  word_node* new_word = vm.cp;
  new_word->precedence = precedence;
  new_word->name = strndup(name, MAX_WORD_LENGTH);
  new_word->pf = pf;
  return new_word;
}

/*
 * vm.cp - points to next open spot
 * vm.dict_head - points to "top" of last word.
 * node.next - points to top of next word.
 */
void dict_prepend(word_node* node) {
  /* TODO need a bounds check w/ dict_end */
  /* TODO sizeof won't work when word sizes vary */
  node = (word_node *)memcpy(vm.cp, node, sizeof(word_node));

  /* First word in, next needs to be null */
  if (vm.cp == vm.dict) {
    node->next = NULL;
  } else {
    node->next = vm.dict_head;
  }
  vm.dict_head = node;

  /* TODO sizeof won't work when word sizes vary */
  vm.cp = vm.dict_head + sizeof(node);
}

/* this itself could be a word if we didn't worry about passing params? */
word_node* dict_find(const char* name) {
  word_node* current = vm.dict_head;  /* top of last word */
  while (current >= vm.dict) {
    if (strncmp(name, current->name, MAX_WORD_LENGTH) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

