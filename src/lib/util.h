#ifndef __UTIL_H__
#define __UTIL_H__

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdarg.h>

extern int readText(char *fileName, char *text, int size);
extern void argHandle(int argc, char *argv[], int argMin, char *msg);
extern void hexDump16(uint16_t *words, int len);
extern int  error(char *msg);
extern void replace(char *str, char *set, char t);
extern void cstr2text(char *cstr, char *text);
extern void ltrim(char *str, char *trimStr, char *set);
extern void rtrim(char *str, char *trimStr, char *set);
extern void trim(char *str, char *trimStr, char *set);
extern void htob(char* hex, char* binary);
extern void itob(int i, char* binary);
extern int  btoi(char* binary);
extern void format(char *buf, char *fmt, char *args[]);

#define NMAX 100
#define SMAX 1000
#define TMAX 1000000

#define BIT(var, pos) ((var) & (1<<(pos)))
#define eq(x,y) (strcmp((x),(y))==0)
#define debug(...) { if (isDebug) printf(__VA_ARGS__); }
#define min(x,y) (((x)<(y)) ? (x) : (y))
#define max(x,y) (((x)>(y)) ? (x) : (y))
#define member(c, set) strchr(set, c)
#define error(...) { printf(__VA_ARGS__); assert(0); }

extern char isDebug, *argOut;
extern char isFlag[];

#endif
