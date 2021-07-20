
#include <stdlib.h>
#include "../typedefs.h"
#include "../constants.h"
#include "../core.h"
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
  cell xt = (cell)data_pop();
  word_node* word = (word_node *)(vm.dict + xt);
  word->code();
}

void allot(void) {
  cell bytes = data_pop();
  vm.cp += bytes;
}


/**** ARGH ****/


/*
  I need a generic way to invoke a word using the return stack instead of this
  nonsense. Right now I'm trying to make the "address interpreter" do stuff that
  maybe needs to be done for every invocation.

  1. Implement exit
    a. check the return stack depth
    b. if there's anything there, push the XT onto the stack and execute it. Else, invoke QUIT.
  2. Implement QUIT
    a. print OK basically... quit is basically "back to the loop"

  If we wrote QUIT in forth it'd be
  : QUIT  BEGIN
      (clear return stack)
      (accept input)
      INTERPRET
      ." ok " CR
     AGAIN ;

  How do we make a word "escape" all the way back up to main? Just return? Perhaps RUN just
  stays in a loop until QUIT gets invoked? Or maybe until the return stack is empty?

 */

/*
 * This is the word that gets put into a compiled dictionary entry as the "code" pointer that
 * gets executed. In the main loop, the dictionary entry that is being executed is pushed onto
 * return stack for every word that is run. So we need to pop the return stack and offset
 * into the dictionary entry to the data section, which contains a list of XTs for words that
 * need to be executed. Those words themselves may invoke other words, so we need to push
 * those onto the stack as well.
 */
void run(void) {
  /* pop the XT, that's us */
  cell xt = (cell)return_pop();
  word_node* word = (word_node *)(vm.dict + xt);
  cell* ip = word->data;
  while (ip++ != NULL) {
    return_push(*ip); /* these two instructions are basically the R@ word */
    data_push(*ip);
    execute();
  }
}

void exit(void) {
  cell xt = (cell)return_pop();
  
}
