#include "compiler.h"

char code[TMAX];

int main(int argc, char * argv[]) {
  argHandle(argc, argv, 2, "c0c <file> -d -r");
  char cFile[SMAX], irFile[SMAX], mFile[SMAX];
  sprintf(cFile, "%s.cx", argv[1]);
  sprintf(irFile, "%s.ix", argv[1]);
  sprintf(mFile, "%s.mx", argv[1]);
  if (readText(cFile, code, TMAX) < 0)
    error("cc0:cFile %s not found !", cFile);
  parse(code);
  irPass2();
  if (isDebug) irDump();
  irSave(irFile);
  ir2m(mFile);
  if (isFlag['r']) irRun();
}