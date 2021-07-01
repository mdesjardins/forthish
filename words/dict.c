
#include "../typedefs.h"
#include "../constants.h"
#include "../dictutil.h"
#include "../tibutil.h"
#include "../vm.h"
#include "dict.h"

void tick(void) {
  char name[MAX_WORD_LENGTH];
  if (next_token(name)) {
    word_node* word = dict_find(name);
    if (word) {
      data_push(dict_xt_for(word));
    }
  } else {
    /* need to abort */
  }
}

void execute(void) {
  /* problem - a pointer to a function is larger than a cell. */
  /* we won't be able to use addresses as our  execution token? */
  cell xt = (cell)data_pop();
  word_node* word = (word_node *)(vm.dict + xt);
  word->pf();
}
