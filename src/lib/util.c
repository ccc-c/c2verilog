#include "util.h"

char isDebug = 0;
char isFlag[128], *argOut = NULL;

void argHandle(int argc, char *argv[], int argMin, char *msg) {
  if (argc < argMin) {
    printf("%s\n", msg);
    exit(1);
  }
  memset(isFlag, 0, sizeof(isFlag));
  char isOut = 0;
  for (int i=0; i<argc; i++) {
    char *a=argv[i];
    if (*a == '-') {
      a++;
      isFlag[(int) *a] = 1;
      isOut = (*a == 'o')? 1 : 0;
    } else if (isOut) {
      argOut = a;
    }
  }
  isDebug = isFlag['d'];
}

int readText(char *fileName, char *text, int size) {
  FILE *file = fopen(fileName, "r");
  if (file == NULL) return -1;
  int len = fread(text, 1, size, file);
  text[len] = '\0';
  fclose(file);
  return len;
}

#define ARG_MAX 10

void format(char *buf, char *fmt, char *args[]) {
  char *fp=fmt, *bp = buf;;
  while (*fp != '\0') {
    if (strncmp(fp, "${", 2)==0) {
      int ai = 0;
      sscanf(fp, "${%1d}", &ai);
      strcpy(bp, args[ai]);
      bp += strlen(args[ai]);
      fp += 4;
    } else {
      *bp++ = *fp++;
    }
  }
  *bp = '\0';
}

// ================= Binary ==================
static char* h2b[] = {
  "0000", "0001", "0010", "0011",
  "0100", "0101", "0110", "0111", 
  "1000", "1001", "1010", "1011",
  "1100", "1101", "1110", "1111"};

static char hexDigits[] = "0123456789ABCDEF";

char *nextToken(char *str, char *spliter, char *sp) {
  char *p = str;
  while (!strchr(spliter, *p)) p++;
  *sp = *p;
  *p = '\0';
  return str;
}

void hexDump16(uint16_t *words, int len) {
  for (int i=0; i<len; i++) {
    printf("%04X", words[i]);
  }
}

void replace(char *str, char *set, char t) {
  for (char *p = str; *p!= '\0'; p++) {
    if (strchr(set, *p) != NULL) *p = t;
  }
}

void cstr2text(char *cstr, char *text) {
  char *s = cstr, *t = text;
  while (*s != '\0') {
    if (*s == '\\') {
      s++;
      switch (*s) {
        case 'n': *t = '\n'; break;
        case 't': *t = '\t'; break;
        case 'r': *t = '\r'; break;
        case '\\': *t = '\\'; break;
        default: error("cstr2text \\%c not support!", *s);
      }
      s++;
      t++;
    } else {
      *t++ = *s++;
    }
  }
  *t = '\0';
}

void ltrim(char *str, char *trimStr, char *set) {
  char *p = str;
  while (strchr(set, *p)) p++;
  strcpy(trimStr, p);
}

void rtrim(char *str, char *trimStr, char *set) {
  char *p = str + strlen(str) - 1;
  while (strchr(set, *p)) p--;
  strncpy(trimStr, str, p-str);
  trimStr[p-str+1] = '\0';
}

void trim(char *str, char *trimStr, char *set) {
  ltrim(str, trimStr, set);
  char tStr[TMAX];
  rtrim(trimStr, tStr, set);
  strcpy(trimStr, tStr);
}

void htob(char* hex, char* binary) {
  for (int i=0; hex[i] != '\0'; i++) {
    char *ptr = strchr(hexDigits, hex[i]);
    assert(ptr != NULL);
    int h = ptr - hexDigits;
    sprintf(&binary[4*i], "%s", h2b[h]);
  }
}

void itob(int i, char* binary) {
  char hex[100];
  sprintf(hex, "%04X", i);
  htob(hex, binary);
}

int btoi(char* binary) {
  int result = 0;
  for (char *p = binary; *p != '\0'; p++) {
    result <<= 1;
    if (*p == '1') result += 1;
  }
  return result;
}

/*
void format(char *buf, char *fmt, char *args[]) {

  int argMax = 0;
  char *fp = fmt, *bp = buf;
  while (*fp != '\0') {
    if (strncmp(fp, "${",2)==0) {
      int ai = 0;
      sscanf(fp, "${%1d}", &ai);
      if (ai > argMax) argMax = ai;
      fp += 4;
    } else {
      fp ++;
    }
  }
  assert(argMax < ARG_MAX);

  char *args[ARG_MAX];
  va_list argp; va_start(argp, fmt);
  for (int i=1; i<=argMax; i++) {
    args[i] = va_arg(argp, char*);
  }
  va_end(argp);
  
  char *fp=fmt, *bp = buf;;
  while (*fp != '\0') {
    if (strncmp(fp, "${", 2)==0) {
      int ai = 0;
      sscanf(fp, "${%1d}", &ai);
      strcpy(bp, args[ai]);
      bp += strlen(args[ai]);
      fp += 4;
    } else {
      *bp++ = *fp++;
    }
  }
  *bp = '\0';
}
*/