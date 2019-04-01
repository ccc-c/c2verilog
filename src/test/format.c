#include "../lib/util.h"

void main() {
  char buf[SMAX];
  char *args[] = {"", "x", "t1", NULL};
  format(buf, "@${1};D=M;${2};M=D", args);
  printf("buf=|%s|\n", buf);
  format(buf, "abcd", args);
  printf("buf=|%s|\n", buf);
}