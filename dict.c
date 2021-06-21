
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "dict.h"
#include "words.h"
#include "constants.h"

word_node* dict_head = NULL;

void dict_init() {
  dict_prepend(word_build(".", pop_stack));
  dict_prepend(word_build(".s", show_stack));
  dict_prepend(word_build("emit", emit));
  dict_prepend(word_build("+", add));
  dict_prepend(word_build("-", subtract));
  dict_prepend(word_build("=", equals));
}

word_node* word_build(const char* name, param_stack_elem (*pf)(void)) {
  word_node* new_word = (word_node *)malloc(sizeof(word_node));
  if (new_word == NULL) {
    /* panic, out of memory */
    fprintf(stderr, "Out of memory.");
    exit(-1);
  }
  new_word->name = strndup(name, MAX_WORD_LENGTH);
  new_word->pf = pf;
  return new_word;
}

void dict_prepend(word_node* node) {
  node->next = dict_head;
  dict_head = node;
}

int dict_word_count() {
  int size = 0;
  word_node* current = dict_head;
  while (current != NULL) {
    size++;
    current = current->next;
  }
  return size;
}

word_node* dict_find(const char* name) {
  word_node* current = dict_head;
  while (current != NULL) {
    if (strncmp(name, current->name, MAX_WORD_LENGTH) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

int eval(const char* name) {
  word_node* word = dict_find(name);
  if (word) {
    return word->pf();
  }
  /* error */
  fprintf(stderr, "%s?", name);
  return -1; /* ?? */
}
