
#include "strTable.h"

StrTable gStrTable;
char gText[1000*1000];

void stNew(StrTable *st, char *text) {
  st->text = text;
  st->textEnd = st->text;
}

char *stPutn(StrTable *st, char *str, int n) {
  char *sp = str, *tp = st->textEnd;
  char *begin = st->textEnd;
  for (int i=0; i<n; i++) {
    if (*sp == '\0') break;
    *tp++ = *sp++;
  }
  *tp ++ = '\0'; 
  st->textEnd = tp;
  return begin;
}

char *stPut(StrTable *st, char *str) {
  return stPutn(st, str, INT_MAX-1);
}

// ===== work on Global gStrTable =======
void stInit() {
  stNew(&gStrTable, gText);
}

char *stAddn(char *str, int n) {
  return stPutn(&gStrTable, str, n);
/*
  char *sp = str, *tp = textEnd;
  char *begin = textEnd;
  for (int i=0; i<n; i++) {
    if (*sp == '\0') break;
    *tp++ = *sp++;
  }
  *tp ++ = '\0'; 
  textEnd = tp;
  return begin;
*/
}

char *stAdd(char *str) {
  return stPut(&gStrTable, str);
//  return stAddn(str, INT_MAX-1);
}
