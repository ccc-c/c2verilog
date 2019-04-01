#include "ir.h"

Pair varList[VAR_MAX];
Map varMap;
int v[VAR_MAX];
int t[VAR_MAX] = { 0 };

int *varLookup(char *name) {
  int h = mapFindIdx(&varMap, name);
  return &v[h];
}

int *varAdd(char *name) {
  return mapAdd(&varMap, name, &t[0])->value;
}

int irOp2(int a, char *op, int b) {
  if (eq(op, "+")) return a + b;
  if (eq(op, "-")) return a - b;
  if (eq(op, "*")) return a * b;
  if (eq(op, "/")) return a / b;
  if (eq(op, "%%")) return a % b;
  if (eq(op, "<")) return a < b;
  if (eq(op, ">")) return a > b;
  if (eq(op, "==")) return a == b;
  if (eq(op, "!=")) return a != b;
  if (eq(op, "<=")) return a <= b;
  if (eq(op, ">=")) return a >= b;
  error("irOp2: op=%s not found!", op);
}

int irExec(int i) {
  IR *p = &ir[i];
  IrType type = p->type;
  int t0 = p->t, t1 = p->t1, t2 = p->t2, label = p->label;
  char *str = p->str;
  int pc = i + 1;
  int *vp, v, cond;
  trace("%02d: ", i);
  switch (type) {
    case IrAssignSt:
      vp = varLookup(str);
      *vp = t[t0];
      trace("%s = t%d = %d\n", str, t0, *vp);
      break;
    case IrAssignTs:
      v = (isdigit(*str)) ? atoi(str) : *varLookup(str);
      t[t0] = v;
      trace("t%d = %s = %d\n", t0, str, v);
      break;
    case IrLabel:
      trace("(L%d) = %d\n", label, L[label]);
      break;
    case IrGoto:
      pc = L[label];
      trace("goto L%d = %d\n", label, pc);
      break;
    case IrIfGoto:
      cond = t[t0];
      trace("if t%d(=%d) ", t0, cond);
      if (cond) {
        pc = L[label];
        trace("goto L%d = %d\n", label, pc);
      } else trace(" -- fail\n");
      break;
    case IrIfNotGoto:
      cond = t[t0];
      trace("ifnot t%d(=%d) ", t0, cond);
      if (!cond) {
        pc = L[label];
        trace("goto L%d = %d\n", label, L[label]);
      } else trace(" -- fail\n");
      break;
    case IrOp2:
      t[t0] = irOp2(t[t1], str, t[t2]);
      trace("t%d = t%d %s t%d = %d\n", t0, t1, str, t2, t[t0]);
      break;
    default: error("irExec: irType=%d not found!", type);
  }
  return pc;
}

void irRun() {
  printf("===================irRun()=======================\n");
  mapNew(&varMap, VAR_MAX);
  for (int pc = 0; pc < irTop;) {
    pc = irExec(pc);
  }
}
