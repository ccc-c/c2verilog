#include "ir.h"

IR ir[IR_MAX];
int irTop = 0;
int L[VAR_MAX]; // label => address

void irNew(IR p) {
  ir[irTop++] = p;
}

void irEmitAssignTs(int t, char *s) {
  irNew((IR) {.type=IrAssignTs, .t=t, .str=s});
}

void irEmitAssignSt(char *s, int t) {
  irNew((IR) {.type=IrAssignSt, .t=t, .str=s});
}

void irEmitOp2(int t, int t1, char *op, int t2) {
  irNew((IR) {.type=IrOp2, .str=op, .t=t, .t1=t1, .t2=t2});
}

void irEmitLabel(int label) {
  irNew((IR) {.type=IrLabel, .label=label});
}

void irEmitLabelStr(char *id) {
  irNew((IR) {.type=IrLabelStr, .str=id});
}

void irEmitGoto(int label) {
  irNew((IR) {.type=IrGoto, .label=label});
}

void irEmitGotoStr(char *id) {
  irNew((IR) {.type=IrGotoStr, .str=id});
}

void irEmitIfGoto(int t, int label) {
  irNew((IR) {.type=IrIfGoto, .t=t, .label=label});
}

void irEmitIfNotGoto(int t, int label) {
  irNew((IR) {.type=IrIfNotGoto, .t=t, .label=label});
}

void irEmitAsm(char *asmCode, char *args[]) {
  char *code = stAdd(asmCode);
  irNew((IR) {.type=IrAsm, .str=code });
}

void irEmitArg(int t, int i) {
  irNew((IR) {.type=IrArg, .t=t, .t1=i});
}

void irEmitCall(char *fname, int t, int label) {
  irNew((IR) {.type=IrCall, .str=fname, .t=t, .label=label});
}

void irEmitReturn(int t) {
  irNew((IR) {.type=IrReturn, .t=t});
}

void irEmitParam(char *name) {
  irNew((IR) {.type=IrParam, .str=name });
}

void irEmitFunction(char *name) {
  irNew((IR) {.type=IrFunction, .str=name });
}

void irEmitFend(char *name) {
  irNew((IR) {.type=IrFend, .str=name });
}

void irWrite(FILE *fp, IR *p) {
  // printf("p->str=%s\n", p->str);
  switch (p->type) {
    case IrAssignSt: fprintf(fp, "%s = t%d", p->str, p->t); break;
    case IrAssignTs: fprintf(fp, "t%d = %s", p->t, p->str); break;
    case IrLabel: fprintf(fp, "(L%d)", p->label); break;
    case IrLabelStr: fprintf(fp, "(%s)", p->str); break;
    case IrGoto: fprintf(fp, "goto L%d", p->label); break;
    case IrGotoStr: fprintf(fp, "goto %s", p->str); break;
    case IrIfGoto: fprintf(fp, "if t%d goto L%d", p->t, p->label); break;
    case IrIfNotGoto: fprintf(fp, "ifnot t%d goto L%d", p->t, p->label); break;
    case IrAsm: fprintf(fp, "asm %s", p->str); break;
    case IrOp2: fprintf(fp, "t%d = t%d %s t%d", p->t, p->t1, p->str, p->t2); break;
    case IrCall: fprintf(fp, "call %s t%d L%d", p->str, p->t, p->label); break;
    case IrArg:  fprintf(fp, "arg t%d", p->t); break;
    case IrParam: fprintf(fp, "param %s", p->str); break;
    case IrFunction: fprintf(fp, "function %s", p->str); break;
    case IrFend: fprintf(fp, "fend %s", p->str); break;
    case IrReturn: fprintf(fp, "return t%d", p->t); break;
    default: error("ir.type %d not found!", p->type);
  }
  fprintf(fp, "\n");
}

void irSave(char *fname) {
  FILE *irF = fopen(fname, "w");
  for (int i=0; i<irTop; i++) {
    irWrite(irF, &ir[i]);
  }
  fclose(irF);
}

void irDump() {
  printf("=======irDump()==========\n");
  for (int i=0; i<irTop; i++) {
    printf("%02d: ", i);
    irWrite(stdout, &ir[i]);
  }
}

void irPass2() {
  debug("==========irPass2()============\n");
  for (int i=0; i<irTop; i++) {
    int label = ir[i].label, type = ir[i].type;
    if (type == IrLabel) {
      assert(label != 0);
      L[label] = i;
      debug("L%d=%d\n", label, L[label]);
    }
  }
}
