#include "../lib/util.h"

void main() {
  char buf[SMAX];
  trim("xxabcdefyyy", buf, "xy");
  printf("buf=|%s|\n", buf);
  strcpy(buf, "xxabcdefyyy");
  trim(buf, buf, "xy");
  printf("buf=|%s|\n", buf);
}