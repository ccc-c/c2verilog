#include "vm.h"

int16_t  D = 0, A = 0, savedA = 0, savedD = 0;
uint16_t im[32768];
int16_t  m[32768];
uint32_t iCount = 0; // 已執行指令數，時間中斷用
int8_t   inInterrupt = 0;

int putstr(int16_t *str) {
  int16_t *p = str;
  while (*p != 0) {
    printf("%c", *p);
    p++;
  }
  return p-str;
}

// ALU: C 型指令的 cTable 之處理, 也就是T = X op Y 的狀況 
int alu(int16_t c, int16_t A, int16_t D, int16_t AM) {
  int16_t out = 0;
  switch (c) {
    case 0x00: out = D&AM; break; // "D&AM","000000"
    case 0x02: out = D+AM; break; // "D+AM","000010"
    case 0x07: out = AM-D; break; // "AM-D","000111"
    case 0x0C: out = D;  break;   // "D",   "001100"
    case 0x0D: out = D^0xFFFF; break; // "!D",  "001101"
    case 0x0E: out = D-1; break; // "D-1", "001110"
    case 0x0F: out = -D; break;   // "-D",  "001111"
    case 0x13: out = D-AM; break; // "D-AM","010011"
    case 0x15: out = D|AM; break; // "D|AM","010101"
    case 0x1F: out = D+1; break;  // "D+1", "011111"
    case 0x2A: out = 0;  break;   // "0",   "101010"
    case 0x30: out = AM; break;   // "AM",  "110000"
    case 0x31: out = AM^0xFFFF; break; // "!AM", "110001"
    case 0x32: out = AM-1; break; // "AM-1","110010"
    case 0x33: out = -AM; break;  // "-AM", "110011"
    case 0x37: out = AM+1; break; // "AM+1","110111"
    case 0x3A: out = -1; break;   // "-1",  "111010"
    case 0x3F: out = 1;  break;   // "1",   "111111"
    default: out = aluExt(c, A, D, AM); // 擴充指令集
  }
  return out;
}

// C 型指令的擴充指令集 aluExt
int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM) {
  int16_t out = 0;
  switch (c) {
    // 運算延伸指令 : 使用 10xxxx ，避開 {"0",   "101010"}
    case 0x20: out = (D << AM);  break; // 左移
    case 0x21: out = (D >> AM);  break; // 右移
    case 0x22: out = (D * AM);   break; // 乘法
    case 0x23: out = (D / AM);   break; // 除法
    case 0x24: out = (D % AM);   break; // 餘數
    case 0x25: out = (D < AM);   break; // 小於
    case 0x26: out = (D <= AM);  break; // 小於或等於
    case 0x27: out = (D > AM);   break; // 大於
    case 0x28: out = (D >= AM);  break; // 大於或等於
    case 0x29: out = (D == AM);  break; // 等於
    // 0x2A 已被 out = 0 使用
    case 0x2B: out = (D != AM);  break; // 不等於
    case 0x2C: out = (D ^ AM);   break; // xor
    // 中斷與呼叫指令
    case 0x2D: LR = PC; PC=A; break; // {"call", "101101"}, PC 原本就加過 1 了，不用重複加。
    case 0x2E: PC = LR; break;   // {"ret", "101110"}
    case 0x2F: swi(A, D); break;     // 0x30-33 已被使用，以下從 0x34-0x36, 0x38-0x39, 0x3B-0x3E 可用
    case 0x34: // {"iret", "110100"}
      A = savedA;
      D = savedD;
      printf("IRET: PC=%04X iCount=%d", PC, iCount);
      PC = ILR;
      printf("ILR=%04X A=%04X, D=%04X\n", ILR, A, D);
      inInterrupt = 0;
      // exit(0); 
      break;
    default: error("alu+aluExt: c=%02x not found !", c);
  }
  return out;
}

void swi(int16_t A, int16_t D) {
  time_t rawtime;
  struct tm * timeinfo;

  switch (A) {
    case 0x00: // swi 0: print integer
      printf("%d ", D);
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
      printf(" iCount = %d", iCount);
      break;
    case 0x11: // swi 17: fsetm
      F = *(float*) &m[D];
      break;
    case 0x12: // swi 18: fput
      printf("%f ", F);
      break;
    case 0x13: // swi 19: fadd
      F += *(float*) &m[D];
      break;
    case 0x14: // swi 20: fsub
      F -= *(float*) &m[D];
      break;
    case 0x15: // swi 21: fmul
      F *= *(float*) &m[D];
      break;
    case 0x16: // swi 22: fdiv
      F /= *(float*) &m[D];
      break;
    default:
      error("swi A=%04x not found !", A);
  }
}

// 處理 C 型指令
void cInstr(int16_t a, int16_t c, int16_t d, int16_t j) { // int16_t i, 
  int AM = (a == 0) ? A : m[A];

  int16_t aluOut = alu(c, A, D, AM);

  if (BIT(d, 2)) A = aluOut;
  if (BIT(d, 1)) D = aluOut;
  if (BIT(d, 0)) m[A] = aluOut;

  switch (j) {
    case 0x0: break;                          // 不跳躍，執行下一個指令！
    case 0x1: if (aluOut >  0) PC = A; break; // JGT
    case 0x2: if (aluOut == 0) PC = A; break; // JEQ
    case 0x3: if (aluOut >= 0) PC = A; break; // JGE
    case 0x4: if (aluOut <  0) PC = A; break; // JLT
    case 0x5: if (aluOut != 0) PC = A; break; // JNE
    case 0x6: if (aluOut <= 0) PC = A; break; // JLE
    case 0x7: PC = A; break;                  // JMP
    default: error("cInstr() : j=%d not found !", j);
  }

}

// 時間中斷處理
int interruptHandler() {
  iCount ++; // 已執行指令數
  uint32_t tiPeriod = ((uint32_t) CR1) << 8; // 快速的乘以 256
  if (!inInterrupt /* 不允許中斷重入 */ && (tiPeriod > 0) && (iCount % tiPeriod == 0)) {
    savedA = A;
    savedD = D;
    ILR = PC; // 中斷時必須把 PC 存起來，這樣 Scheduler 才能保存該 thread 的 PC 並在下次返回
    printf("interruptHandler(): iCount = %d ILR=%04X A= %04X D=%04X\n", iCount, ILR, A, D);
    PC = 2;
    return 1;
  }
  if (iCount > tiPeriod * 2 + 100) exit(0);
  return 0;
}

void cpu() {
  PC++;

  uint16_t a, c, d, j;
  uint16_t uI = *(uint16_t*) &I;
  if ((uI & 0xE000)==0xE000) { // C 指令前三碼為 111
    a = (uI & 0x1000) >> 12;
    c = (uI & 0x0FC0) >>  6;
    d = (uI & 0x0038) >>  3;
    j = (uI & 0x0007) >>  0;
    cInstr(a, c, d, j);
  } else if ((uI & 0x8000) == 0) { // A 指令
    A = I;
  } else {
    error("cpu(): not A or C command !");
  }
  debug(" A=%04hX D=%04hX=%05d m[A]=%04hX", A, D, D, m[A]);
  if ((I & 0xE000)==0xE000) debug(" a=%X c=%02X d=%X j=%X", a, c, d, j);
  debug("\n");
  // interruptHandler();
}

// 虛擬機主程式
void run(uint16_t *im, int16_t *m, int imTop) {
  while (1) {
    if (PC >= imTop) break; // 超出範圍，虛擬機自動結束。
    I = im[PC];
    debug("PC=%04X I=%04X", PC, I);
    cpu();
  }
}

// run: ./vm <file.bin>
int main(int argc, char *argv[]) {
  argHandle(argc, argv, 2, "./vm <file.ox>\n");

  FILE *oFile = fopen(argv[1], "rb");
  if (oFile == NULL) error("vm: oFile %s not found!", argv[1]);
  int imTop = fread(im, sizeof(im[0]), 32768, oFile);
  if (isDebug) { hexDump16(im, imTop); debug("\n"); }
  fclose(oFile);

  memcpy(m, im, imTop*sizeof(im[0])); // 啟動後將指令記憶體 im 複製到資料記憶體 m，這樣就不需要存取 im 的指令了。

  run(im, m, imTop);
  return 0;
}
