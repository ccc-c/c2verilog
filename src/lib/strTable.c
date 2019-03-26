
#include "strTable.h"

char strTable[1000*1000], *strTableEnd = strTable;

void stInit() {
  strTableEnd = strTable;
}

char *stAddn(char *str, int n) {
  char *sp = str, *tp = strTableEnd;
  char *begin = strTableEnd;
  for (int i=0; i<n; i++) {
    if (*sp == '\0') break;
    *tp++ = *sp++;
  }
  *tp ++ = '\0'; 
  strTableEnd = tp;
  return begin;
}

char *stAdd(char *str) {
  return stAddn(str, INT_MAX-1);
}
