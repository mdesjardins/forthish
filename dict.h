#ifndef DICT_H
#define DICT_H

#include <stdbool.h>
#include "typedefs.h"

/* Word things */

/* Our dictionary is a linked list of word nodes, probably should align. */
typedef struct word_node {
    bool precedence;
    const char* name;
    param_stack_elem (*pf)(void);
    struct word_node* next;
} word_node;

word_node* word_build(const char* name, param_stack_elem (*pf)(void));

/* Dictionary things */

void dict_init();
void dict_prepend(word_node* node);
int dict_word_count();
word_node* dict_find(const char* name);

interp_result interpret(const char* word);

#endif /* DICT_H */
