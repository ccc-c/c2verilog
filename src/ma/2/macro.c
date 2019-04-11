#include <stdio.h>
#include <stdlib.h>
#include "../../lib/map.h"
#include "../../lib/util.h"

Pair macroList[] = {
  // io
  {"puti", "@${1}\nD=M\n@0\nswi"},
  {"putc", "@${1}\nD=M\n@1\nswi"},
  {"puts", "@${1}\nD=A\n@3\nswi"},
  {"puttime", "@15\nswi"},
  // float
  {"putf", "@18\nswi"},
  {"setf", "@${1}\nD=A\n@17\nswi"},
  {"addf", "@${1}\nD=A\n@19\nswi"},
  {"subf", "@${1}\nD=A\n@20\nswi"},
  {"mulf", "@${1}\nD=A\n@21\nswi"},
  {"divf", "@${1}\nD=A\n@22\nswi"},
  // control
  {"set",  "@${3}\nD=M\n@${1}\nM=D"},   // .set  i = t1
  {"setc", "@${3}\nD=A\n@${1}\nM=D"},   // .setc i = 5
  {"goto", "@${1}\n0;JMP"},             // goto L
  {"if",   "@${1}\nD=M\n@${3}\nD;JNE"}, // if e goto L
  {"ifnot","@${1}\nD=M\n@${3}\nD;JEQ"}, // ifnot e goto L
  {"op",   "@${3}\nD=M\n@${5}\nD=D${4}M\n@${1}\nM=D"}, // .op z = x + y
  {"opc",  "@${3}\nD=M\n@${5}\nD=D${4}A\n@${1}\nM=D"}, // .op z = x + 1
  // function
  {"call",  "@${1}\ncall"},   // .call f
  {"ret",   "ret"},         // .ret
};

Map macroMap;

int expand(char *line, char *code) {
  replace(line, "\r\n", ' ');
  if (line[0] != '.') { sprintf(code, "%s\n", line); return 0; }
  char p[10][SMAX]; memset(p, 0, sizeof(p));
  sscanf(line, ".%s %s %s %s %s %s", p[0], p[1], p[2], p[3], p[4], p[5]);
  char *macro = mapLookup(&macroMap, p[0]);
  if (!macro) error("macro %s not found!\n", p[0]);
  char eMacro[TMAX];
  char *args[] = { p[0], p[1], p[2], p[3], p[4], p[5], NULL };
  format(eMacro, macro, args);
  sprintf(code, "// %s\n%s\n", line, eMacro);
  return 1;
}

void macroExpand(char *iFile, FILE *oF) {
  char line[SMAX];
  debug("====== macroExpand ============\n");
  FILE *iF = fopen(iFile, "r");
  if (iF == NULL) error("macroExpand: file %s not found!\n", iFile);
  char code[TMAX];
  sprintf(code, "// =========== iFile: %s ==============\n", iFile);
  fwrite(code, strlen(code), 1, oF);
  while (fgets(line, sizeof(line), iF)) {
    int isExpand = expand(line, code);
    if (isExpand) { debug("%s", code); } else debug("%s", line);
    fwrite(code, strlen(code), 1, oF);
  }
  fclose(iF);
}

// run: ./ma iFile1, 2, .... -o oFile -d
int main(int argc, char *argv[]) {
  argHandle(argc, argv, 2, "./ma <file>\n");

  mapNew(&macroMap, 59); mapAddAll(&macroMap, macroList, ARRAY_SIZE(macroList));

  FILE *oF = fopen(argOut, "w");
  for (int i=1; i<argc; i++) {
    char *iFile = argv[i];
    if (strcmp(argv[i], "-o") == 0) break;
    macroExpand(iFile, oF);
  }

  mapFree(&macroMap);
}