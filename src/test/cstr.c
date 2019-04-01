#include "../lib/util.h"

void main() {
  char buf[SMAX];
  cstr2text("abc\\ndef\\nghi\\n", buf);
  printf("buf=|%s|\n", buf);
}