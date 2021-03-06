/* Aubrey McIntosh, PhD
   git@github.com:a-mcintosh/git-an-IPv6.git

   calculate unrouted IPv6 address from git commit ID
   e.g. git-an-IPv6 `git rev-parse --short HEAD`
   ----
   inputs: a sequence of hex digits and ":"
   outputs sets of 4 hex digits separated by ':' with zero or 1 "::"

$Id: d99cf0aeb3eec5aed19235d51d2a7ecdecee7f32 $

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Adapted without permission from
https://www.cs.princeton.edu/courses/archive/fall07/cos217/lectures/02CharacterIO-2x2.pdf
*/


enum Statetype {DOCU,NEXTARG,PREFIX,NORMAL,AFTER,DOUBLE,EOI,DOCU2,DONE};
int newline;

char goodch(char *k, int *i) {
  char ch;
  int good;

  k[*i] = tolower(k[*i]);
  ch = k[*i];
  if (ch=='n') {newline = 1;}
  good = (('a' <= ch) && (ch <= 'f')) | (('0' <= ch) && (ch <= '9')) \
    | (ch==0x0) | (ch==':');
  while (good == 0) {
    ch = k[++*i];
    if (ch=='n') {newline = 1;}
    good = (('a' <= ch) && (ch <= 'f')) | (('0' <= ch) && (ch <= '9')) \
      | (ch==0x0) | (ch==':');
  }
  return ch;
}

enum Statetype handlePrefixState(char *k, int *i, int *j) {
    putchar('f');
    putchar('d');
    *j=2;
    *i=0;
    if (goodch(k,i) == 'f') {++*i;}
    if (goodch(k,i) == 'd') {++*i;}
    return NORMAL;
}

int quantum (int blocks) {
    int ceil;
    ceil = blocks/4 + (blocks % 4 != 0);
    return ceil * (4);
}


enum Statetype handleNormalState(char *k, enum Statetype *laststate, int *i, int *j) {
    enum Statetype state;
    char ch;

    state = NORMAL;
    ch = goodch(k,i);

    if (ch != 0) {
      if (ch == ':') {*j=quantum(*j); state = AFTER;}
      else {
        if ((*j % 4)==0) {putchar(':');}
        putchar(ch);
        ++*j;
      }
      ++*i;
      ch = goodch(k,i);
    }
    if (ch==0) {*laststate = state; state = NEXTARG;}
    if (*j >= 32) {state = DOCU2;}
    return state;
}

enum Statetype handleAfterState(char *k, int *i, int *j) {
    enum Statetype state;
    if (goodch(k,i) == ':') {putchar(':'); ++*i; *j=quantum(*j); state = DOUBLE;}
    else                    {state = NORMAL;}
    return state;
}


enum Statetype handleDoubleState(char *k, int *i, int *j) {
    enum Statetype state;
    if (goodch(k,i) == ':') {++*i; ++j;  state = DOUBLE;}
    else              {*j = quantum(*j); state = NORMAL;}
    return state;
}


enum Statetype handleEoiState(int *j) {
    enum Statetype state;
    *j = quantum(*j);
    if (*j < 25) {putchar(':'); *j = 24;}
    if (*j < 29) {putchar(':'); *j = 28;}
    if (*j < 32) {putchar('1'); *j++;}
    state = DONE;
    if (++*j >= 32) {state = DOCU2;}
    return state;
}


enum Statetype handleDoneState(int *j) {
    return DONE;
}

void PrintState(enum Statetype this) {
  switch (this) {
    case DOCU: fprintf(stderr, "DOCU"); break;
    case NEXTARG: fprintf(stderr, "NEXTARG"); break;
    case PREFIX: fprintf(stderr, "PREFIX"); break;
    case NORMAL: fprintf(stderr, "NORMAL"); break;
    case AFTER: fprintf(stderr, "AFTER"); break;
    case DOUBLE: fprintf(stderr, "DOUBLE"); break;
    case EOI: fprintf(stderr, "EOI"); break;
    case DOCU2: fprintf(stderr, "DOCU2"); break;
    case DONE: fprintf(stderr, "DONE"); break;
 }
}

int main(int argc, char *argv[]) {

  int arg=0;
  enum Statetype state = DOCU;
  int i,j;
  enum Statetype laststate;
  int haddouble=0;
  newline = 0;
/* ----meaningless assignments to quiet the compiler------ */
  char *k=0;
/* ------------------------------------------------------- */
  while (state != DONE) {
    switch (state) {
      case DOCU:
        laststate = PREFIX;
        state = NEXTARG;
        break;
      case NEXTARG:
        arg++;
        i = 0;
        if (arg < argc) {k = argv[arg]; state = laststate;}
        else {state = EOI;}
        break;
      case PREFIX:
        state = handlePrefixState(k, &i, &j);
        break;
      case NORMAL:
        state = handleNormalState(k, &laststate, &i, &j);
        break;
      case AFTER:
      	state = handleAfterState( k, &i, &j);
        break;
      case DOUBLE:
        haddouble = 1;
        state = handleDoubleState( k, &i, &j);
        break;
      case EOI: 
        if (haddouble == 1) {j=29;}
	if (j==0)  {putchar('f'); j++;}
	if (j==1)  {putchar('d'); j++;}
        state = handleEoiState(&j);
        break;
      case DOCU2:
        state = DONE;
	break;
      case DONE:
	break;
    }
  }
putchar(0x0);
if (newline==1) {printf("\nDone.\n");}
return 0;
}


