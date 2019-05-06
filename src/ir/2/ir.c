#include "ir.h"

IR ir[IR_MAX];
int irTop = 0;
int L[VAR_MAX]; // label => address

void irNew(IR p) {
  ir[irTop++] = p;
}

void irEmitCall(char *fname, int t1) {
  irNew((IR) {.type=IrCall, .str=fname, .t1=t1});
}

void irEmitArg(int t1) {
  irNew((IR) {.type=IrArg, .t1=t1});
}

void irEmitAssignTs(int t, char *s) {
  irNew((IR) {.type=IrAssignTs, /*.op="t=s",*/ .t=t, .str=s});
}

void irEmitAssignSt(char *s, int t) {
  irNew((IR) {.type=IrAssignSt, /*.op="s=t",*/ .t=t, .str=s});
}

void irEmitOp2(int t, int t1, char *op, int t2) {
  irNew((IR) {.type=IrOp2, .str=op, .t=t, .t1=t1, .t2=t2});
}

void irEmitLabel(int label) {
  irNew((IR) {.type=IrLabel, /*.op="label",*/ .label=label});
}

void irEmitLabelStr(char *id) {
  irNew((IR) {.type=IrLabelStr, /*.op="goto",*/ .str=id});
}

void irEmitGoto(int label) {
  irNew((IR) {.type=IrGoto, /*.op="goto",*/ .label=label});
}

void irEmitGotoStr(char *id) {
  irNew((IR) {.type=IrGotoStr, /*.op="goto",*/ .str=id});
}

void irEmitIfGoto(int t, int label) {
  irNew((IR) {.type=IrIfGoto, /*.op="if-goto",*/ .t=t, .label=label});
}

void irEmitIfNotGoto(int t, int label) {
  irNew((IR) {.type=IrIfNotGoto, /*.op="ifnot-goto",*/ .t=t, .label=label});
}

void irEmitAsm(char *asmCode, char *args[]) {
  char *code = stAdd(asmCode);
  irNew((IR) {.type=IrAsm, .str=code });
}

void irWrite(FILE *fp, IR *p) {
  switch (p->type) {
    case IrCall: fprintf(fp, "call %s %d", p->str, p->t1); break;
    case IrArg:  fprintf(fp, "arg t%d", p->t1); break;
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
