#include <stdio.h>

int main() {
  int f1=1, f2=0;
  int f, n=8, i=2, t;
wbegin:
  t = i>n;
  if (t) goto wend;
  f = f1 + f2;
  f2 = f1;
  f1 = f;
  i = i + 1;
  printf("f=%d\n", f);
  goto wbegin; 
wend:
  printf("f=%d\n", f);
}