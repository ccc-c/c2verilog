#include "vm.h"
#include <time.h>

float   *F = (float*) &m[R_F];

int putstr(int16_t *str) {
  int16_t *p = str;
  while (*p != 0) {
    printf("%c", *p);
    p++;
  }
  return p-str;
}

// 一開始就載入 im 到 m，所以不需要再有 D=I 之類的指令了。
void swi(int16_t A, int16_t D) {
  time_t rawtime;
  struct tm * timeinfo;

  switch (A) {
    case 0x00: // swi 0: print integer
      printf("%d", D);
      break;
    case 0x01: // swi 1: print char
      printf("%c", (char) D);
      break;
    case 0x03: // swi 3: print string in m
      putstr(&m[D]);
      break;
    case 0x0F: // swi 15: print time
      time ( &rawtime );
      timeinfo = localtime ( &rawtime );
      printf("time: %s", asctime (timeinfo) );
      break;
    case 0x11: // swi 17: fsetm
      *F = *(float*) &m[D];
      break;
    case 0x12: // swi 18: fput
      printf("%f ", *F);
      break;
    case 0x13: // swi 19: fadd
      *F += *(float*) &m[D];
      break;
    case 0x14: // swi 20: fsub
      *F -= *(float*) &m[D];
      break;
    case 0x15: // swi 21: fmul
      *F *= *(float*) &m[D];
      break;
    case 0x16: // swi 22: fdiv
      *F /= *(float*) &m[D];
      break;
  }
}

// C 型指令的擴充指令集 aluExt
int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM) {
  int16_t out = 0;
  switch (c) {
    // 運算延伸指令 : 使用 10xxxx ，避開 {"0",   "101010"}
    case 0x20: out = D << AM;  break; // 左移
    case 0x21: out = D >> AM;  break; // 右移
    case 0x22: out = D * AM;   break; // 乘法
    case 0x23: out = D / AM;   break; // 除法
    case 0x24: out = D % AM;   break; // 餘數
    case 0x25: out = D < AM;   break; // 小於
    case 0x26: out = D <= AM;  break; // 小於或等於
    case 0x27: out = D > AM;   break; // 大於
    case 0x28: out = D >= AM;  break; // 大於或等於
    case 0x29: out = D == AM;  break; // 等於
    case 0x2B: out = D != AM;  break; // 不等於
    case 0x2C: out = D ^ AM;   break; // xor
    case 0x2D: out = 0; LR = PC; PC=A; break; // {"call", "101101"}, PC 原本就加過 1 了，不用重複加。
    case 0x2E: out = 0; PC = LR; break;  // {"ret", "101110"},
    case 0x2F: out=0; swi(A, D); break;
    // case 0x30: out = AM; break;   // "AM",  "110000"
    // case 0x31: out = AM^0xFFFF; break; // "!AM", "110001"
    // case 0x32: out = AM-1; break; // "AM-1","110010"
    // case 0x33: out = -AM; break;  // "-AM", "110011"
    case 0x34: out=0; PC = ILR; break;       // {"iret", "101110"},
    // case 0x37: out = AM+1; break; // "AM+1","110111"
    // case 0x3A: out = -1; break;   // "-1",  "111010"
    // case 0x3F: out = 1;  break;   // "1",   "111111"
    default: break;
  }
  return out;
}
