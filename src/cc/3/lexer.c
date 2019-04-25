#include "lexer.h"

char *tokenTypeName[6] = {"Id", "Int", "Keyword", "String", "Op", "End"};
char *p;

void lexInit(char *code) {
  stInit();
  p = code;
}

Token lexScan() {
  Token t = { .str=NULL, .type=End };

  while (isspace(*p)) p++;

  char *start = p;
  if (*p == '\0') return t;
  if (*p == '"') {
    p++;
    while (*p != '"') p++;
    p++;
    t.type = String;
  } else if (*p >='0' && *p <='9') { // 數字
    while (*p >='0' && *p <='9') p++;
    t.type = Int;
  } else if (isalpha(*p) || *p == '_') { // 變數名稱或關鍵字
    while (isalpha(*p) || isdigit(*p) || *p == '_') p++;
    t.type = Id;
  } else if (strchr("+-*/%%&|<>!=", *p) >= 0) {
    char c = *p++;
    if (*p == '=') p++; // +=, ==, <=, !=, ....
    else if (strchr("+-&|", c) >= 0 && *p == c) p++; // ++, --, &&, ||
    t.type = Op;
  } else {
    p++;
    t.type = Op;
  }

  int len = p-start;
  t.str = stAddn(start, len);

  return t;
}
