#ifndef __STRTABLE_H__
#define __STRTABLE_H__

#include <string.h>
#include <limits.h>
#include "util.h"

#define stPrint(...) ({ char stTemp[SMAX]; sprintf(stTemp, __VA_ARGS__); char *p=stAdd(stTemp); p; })
extern void stInit();
extern char *stAdd(char *str);
extern char *stAddn(char *str, int n);

#endif
