
#include "strTable.h"

StrTable gStrTable;
char gText[TMAX];

void ostNew(StrTable *st, char *text) {
  st->text = text;
  st->textEnd = st->text;
}

char *ostAddn(StrTable *st, char *str, int n) {
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

char *ostAdd(StrTable *st, char *str) {
  return ostAddn(st, str, INT_MAX-1);
}

// ===== work on Global gStrTable =======
void stInit() {
  ostNew(&gStrTable, gText);
}

char *stAddn(char *str, int n) {
  return ostAddn(&gStrTable, str, n);
}

char *stAdd(char *str) {
  return ostAdd(&gStrTable, str);
}
