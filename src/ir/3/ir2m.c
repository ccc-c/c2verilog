#include "ir2m.h"

void ir2macro(FILE *fp, IR *p) {
  int t=p->t, t1=p->t1, t2=p->t2, label=p->label, slen;
  char *str = p->str, asmText[TMAX], tempText[TMAX], digit;
  if (isDebug) irWrite(stdout, p);
  switch (p->type) {
    case IrCall:
      fprintf(fp, ".call %s t%d", str, t); // t = call fname
      break;
    case IrArg:
      fprintf(fp, ".arg  t%d", t); // arg t
      break;
    case IrAssignSt:
      fprintf(fp, ".set  %s = t%d", str, t); // s=t
      break;
    case IrAssignTs:
      digit = isdigit(*str) ? 'c' : ' ';
      fprintf(fp, ".set%c t%d = %s", digit, t, str); // t=s
      break;
    case IrLabel: // (label)
      fprintf(fp, "(L%d)", label);
      break;
    case IrLabelStr: // (label)
      fprintf(fp, "(%s)", str);
      break;
    case IrGoto: // goto label
      fprintf(fp, ".goto L%d", label);
      break;
    case IrGotoStr: // goto label
      fprintf(fp, ".goto %s", str);
      break;
    case IrIfGoto: // if t goto label
      fprintf(fp, ".if t%d goto L%d", t, label);
      break;
    case IrIfNotGoto: // ifnot t goto label
      fprintf(fp, ".ifnot t%d goto L%d", t, label);
      break;
    case IrAsm: // asm "...."
      slen = strlen(str)-2;
      strncpy(tempText, &str[1], slen);
      tempText[slen] = '\0';
      cstr2text(tempText, asmText);
      fprintf(fp, "%s", asmText);
      break;
    case IrOp2: // t = t1 op t2
      fprintf(fp, ".op   t%d = t%d %s t%d", t, t1, str, t2);
      break;
    default: 
      error("ir.type %d not found!", p->type);
  }
  fprintf(fp, "\n");
}

void ir2m(char *mFile) {
  FILE *mF = fopen(mFile, "w");
  for (int i=0; i<irTop; i++) {
    ir2macro(mF, &ir[i]);
  }
  fclose(mF);
}