#ifndef __IR_H__
#define __IR_H__

#include <stdio.h>
#include "../../lib/strTable.h"
#include "../../lib/map.h"
#include "../../lib/util.h"

// IR Virtual Machine
#define trace printf
#define VAR_MAX 10000
#define IR_MAX  10000

typedef enum { IrAssignSt, IrAssignTs, IrOp2, IrCall1, IrLabel, IrLabelStr, IrGoto, IrGotoStr, IrIfGoto, IrIfNotGoto, IrAsm, IrCall, IrArg, IrReturn, IrParam, IrFunction, IrFend } IrType;

typedef struct {
  IrType type;
  int t, t1, t2, label;
  // char *s, *op, *labelStr;
  char *str;
} IR;


extern IR ir[];
extern int irTop;
extern int L[];

extern void irPass2();
extern int irExec(int i);
extern void irRun();
extern void irPrint(IR *p);
extern void irEmitArg(int t, int i);
extern void irEmitCall(char *fname, int t, int label);
extern void irEmitReturn(int t);
extern void irEmitAssignTs(int t, char *s);
extern void irEmitAssignSt(char *s, int t);
extern void irEmitOp2(int t, int p1, char *op, int p2);
extern void irEmitLabel(int label);
extern void irEmitLabelStr(char *id);
extern void irEmitGoto(int label);
extern void irEmitGotoStr(char *id);
extern void irEmitIfGoto(int t, int label);
extern void irEmitIfNotGoto(int t, int label);
extern void irEmitAsm(char *asmCode, char *args[]);
extern void irEmitParam(char *name);
extern void irEmitFunction(char *name);
extern void irEmitFend(char *name);
extern void irWrite(FILE *fp, IR *p);
extern void irSave(char *fname);
extern void irDump();

#endif
