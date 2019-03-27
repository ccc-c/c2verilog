#ifndef __STRTABLE_H__
#define __STRTABLE_H__

#include <string.h>
#include <limits.h>
#include "util.h"

typedef struct {
  char *text;
  char *textEnd;
} StrTable;

extern void ostNew(StrTable *st, char *text);
extern char *ostAddn(StrTable *st, char *str, int n);
extern char *ostAdd(StrTable *st, char *str);
// 以下作用在全域變數 gStrTable 上。
extern void stInit();
extern char *stAdd(char *str);
extern char *stAddn(char *str, int n);
#define stPrint(...) ({ char stTemp[SMAX]; sprintf(stTemp, __VA_ARGS__); char *p=stAdd(stTemp); p; })

#endif
