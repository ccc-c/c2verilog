#include <assert.h>
#include "compiler.h"

int  E();
void STMT();
void IF();
void BLOCK();

Token tnow, tnext;

int tempIdx = 1, labelIdx = 1;

#define nextTemp() (tempIdx++)
#define nextLabel() (labelIdx++)

int isNext(char *set) {
  char eset[SMAX], etoken[SMAX+2];
  sprintf(eset, " %s ", set);
  sprintf(etoken, " %s ", tnext.str);
  return (tnext.type != End && strstr(eset, etoken) != NULL);
}

int isNextType(TokenType type) {
  return (tnext.type == type);
}

int isEnd() {
  return tnext.type == End;
}

char *next() {
  tnow = tnext;
  tnext = lexScan();
  debug("token = %-10s type = %-10s\n", tnext.str, tokenTypeName[tnext.type]);
  return tnow.str;
}

char *skip(char *set) {
  if (isNext(set)) {
    return next();
  } else {
    error("skip(%s) got %s fail!\n", set, next());
  }
}

char *skipType(TokenType type) {
  if (isNextType(type)) {
    return next();
  } else {
    error("skipType(%s) got %s fail!\n", tokenTypeName[type], tokenTypeName[tnext.type]);
  }
}

char *skipItem() {
  if (isNextType(Int) || isNextType(String) || isNextType(Id)) {
    return next();
  } else {
    error("skipItem() got %s fail!\n", tokenTypeName[tnext.type]);
  }
}

// F = (E) | Number | Id | CALL
int F() {
  int f;
  if (isNext("(")) { // '(' E ')'
    skip("("); // (
    f = E();
    skip(")"); // )
  } else { // Number | Id | CALL
    f = nextTemp();
    char *item = next();
    irEmitAssignTs(f, item);
  }
  return f;
}

// E = F (op E)*
int E() {
  int i1 = F();
  while (isNext("+ - * / & | < > = <= >= == != && ||")) {
    char *op = skipType(Op);
    int i2 = E();
    int i = nextTemp();
    irEmitOp2(i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// EXP = E
int EXP() {
  tempIdx = 1; // 讓 temp 重新開始，才不會 temp 太多！
  return E();
}

// ASSIGN(id) =  '=' E
void ASSIGN(char *id) {
  skip("=");
  int e = EXP();
  irEmitAssignSt(id, e);
}

// WHILE = while (E) STMT
void WHILE() {
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();
  irEmitLabel(whileBegin);
  skip("while");
  skip("(");
  int e = EXP();
  irEmitIfNotGoto(e, whileEnd);
  skip(")");
  STMT();
  irEmitGoto(whileBegin);
  irEmitLabel(whileEnd);
}

// if (E) STMT (else STMT)?
void IF() {
  int elseBegin = nextLabel();
  int ifEnd = nextLabel();
  skip("if");
  skip("(");
  int e = EXP();
  irEmitIfNotGoto(e, elseBegin);
  skip(")");
  STMT();
  irEmitGoto(ifEnd);
  irEmitLabel(elseBegin);
  if (isNext("else")) {
    skip("else");
    STMT();
  }
  irEmitLabel(ifEnd);
}

// LABEL = id ':'
void LABEL(char *id) {
  skip(":");
  irEmitLabelStr(id);
}

// GOTO = goto id ;
void GOTO() {
  skip("goto");
  char *id = skipType(Id);
  skip(";");
  irEmitGotoStr(id);
}

// ASM = asm( string (, Item)* ) ;
void ASM() {
  skip("asm");
  skip("(");
  char *asmCode = skipType(String);
  char *args[10];
  int  i=0;
  while (isNext(",")) {
    skip(",");
    args[i++] = skipItem();
  }
  skip(")");
  skip(";");
  irEmitAsm(asmCode, args);
}

// STMT = WHILE | IF  | BLOCK | ASM | GOTO | LABEL | ASSIGN ;
void STMT() {
  if (isNext("while"))
    WHILE();
  else if (isNext("if"))
    IF();
  else if (isNext("{"))
    BLOCK();
  else if (isNext("asm"))
    ASM();
  else if (isNext("goto"))
    GOTO();
  else {
    char *id = skipType(Id);
    if (isNext("=")) {
      ASSIGN(id);
      skip(";");
    } else if (isNext(":")) {
      LABEL(id);
    }
  }
}

// STMTS = STMT*
void STMTS() {
  while (!isEnd() && !isNext("}")) {
    STMT();
  }
}

// BLOCK = { STMT* }
void BLOCK() {
  skip("{");
  STMTS();
  skip("}");
}

// PROG = STMT*
void PROG() {
  STMTS();
}

void parse(char *code) {
  debug("============ parse =============\n");
  lexInit(code);
  next();
  PROG();
}
