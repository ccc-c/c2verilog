#include <stdio.h>
#include <stdlib.h>
#include "../../lib/map.h"
#include "../../lib/util.h"

Pair macroList[] = {
  // basic
  {"op",   "@${3}\nD=M\n@${5}\nD=D${4}M\n@${1}\nM=D"}, // .op m = x + y
  {"opc",  "@${3}\nD=M\n@${5}\nD=D${4}A\n@${1}\nM=D"}, // .op m = x + 1
  {"set",  "@${3}\nD=M\n@${1}\nM=D"},   // .set  m = t1
  {"setc", "@${3}\nD=A\n@${1}\nM=D"},   // .setc m = 5
  // control
  {"goto", "@${1}\n0;JMP"},             // goto L
  {"if",   "@${1}\nD=M\n@${3}\nD;JNE"}, // if e goto L
  {"ifnot","@${1}\nD=M\n@${3}\nD;JEQ"}, // ifnot e goto L
  {"exit",  "@255\nswi"},
  // pointer
  {"pget",  "@${1}\nA=M\nD=M\n@${2}\nM=D"},   // .pget p v      // v = *p
  {"pset",  "@${2}\nD=M\n@${1}\nA=M\nM=D"},   // .pset p v      // *p = v
  {"psetc", "@${2}\nD=A\n@${1}\nA=M\nM=D"},   // .psetc p 5     // *p = 5
  // stack
  {"pushc", "@${1}\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1"},   // pushc c  *SP=c; SP=SP+1; 
  {"push",  "@${1}\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1"},   // push m   *SP=m; SP=SP+1; 
  {"pop",   "@SP\nM=M-1\n@SP\nA=M\nD=M\n@${1}\nM=D"},   // pop  m   SP=SP-1; m=*SP;
  // function
  {"arg",   "// t=SP-${2}\n@${2}\nD=A\n@SP\nD=M-D\n@t\nM=D\n// *t=${1}\n@${1}\nD=M\n@t\nA=M\nM=D"},  // arg m i     *(SP-i) = m
  {"param", ""}, // param m     ???
  {"function", "(${1})\n.push LR\n.push FP\n.set FP = SP\n.opc SP = SP + 16"}, // function fname  (fname); PUSH FP; FP=SP // push FP\n@FP\nD=M\n@SP\nM=D\nM=M+1\n// FP=SP\n@SP\nD=M\n@FP\nM=D
  {"call",  "@${1}\ncall"}, // call f
  {"fend",   ".set SP = FP\n.pop FP\n.pop LR\nret"},
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

// 使用指標當參數的 DFS 順序，會比較快速與省記憶體！
// 如此 rExpand(text, p) 必須 改用 strchr 取得第一行 head 與剩餘 tail，
// 然後 DFS 展開 rExpand(head, p) + rExpand(tail, p)
void recursiveExpand(char *text, char *p) {
  if (*text == '\0') { *p = '\0'; return; }
  char *head = text;
  char *tail = strchr(text, '\n');
  *tail++ = '\0';
  char code[SMAX];
  int isExpand = expand(head, code);
  if (isExpand) {
    recursiveExpand(code, p);
  } else {
    strcpy(p, code);
  }
  p += strlen(p);
  recursiveExpand(tail, p);
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
    recursiveExpand(line, code);
    debug("%s", code);
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
  fclose(oF);
  mapFree(&macroMap);
}


/*
int recursiveExpand(char *text, char *code) {
  if (strchr(text, '\n') == NULL) return expand(text, code);

  char tText[SMAX], lineCode[SMAX], expCode[SMAX];
  char *line[100];
  int lineTop = 0;

  strcpy(tText, text);
  char *tline = strtok(tText, "\n");
  while( tline != NULL ) {
    line[lineTop++] = tline;
    tline = strtok(NULL, "\n");
  }

  int isExpand = 0;
  int codeIdx = 0;
  code[0] = '\0';
  for (int i=0; i<lineTop; i++) {
    // printf("line[%d]=|%s|\n", i, line[i] );
    strcpy(lineCode, line[i]);
    while (1) {
      if (recursiveExpand(lineCode, expCode)) {
        strcpy(lineCode, expCode);
        isExpand = 1;
      } else {
        break;
      }
    }
    // printf("lineCode=%s\n", lineCode);
    strcpy(&code[codeIdx], lineCode);
    codeIdx += strlen(lineCode);
    code[codeIdx++] = '\n';
    // printf("codeIdx=%d\n", codeIdx);
  }
  code[codeIdx++] = '\0';
  // printf("text=%s code=%s\n", text, code);
  return isExpand;
}
*/