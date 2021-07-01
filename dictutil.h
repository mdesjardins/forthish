#ifndef DICTUTIL_H
#define DICTUTIL_H

#include <stdbool.h>
#include "typedefs.h"

/* Word things */

/* Our dictionary is a linked list of word nodes, probably should align. */
typedef struct word_node {
    bool precedence;
    const char* name;
    void (*pf)(void);
    struct word_node* next;
} word_node;

word_node* word_build(const char* name, void (*pf)(void), bool precedence);

/* Dictionary things */

void dict_init();
void dict_prepend(word_node* node);
int dict_word_count();
word_node* dict_find(const char* name);
cell dict_xt_for(word_node* node);

#endif /* DICTUTIL_H */
