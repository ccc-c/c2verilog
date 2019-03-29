#ifndef __VM_H__
#define __VM_H__

#include "../../lib/util.h"

#define BIT0 0x0001
#define BIT1 0x0002
#define BIT2 0x0004

extern int16_t m[];

#ifdef _VM_EXT_
int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM);
#endif

#define R_KBD 24576
#define R_SCREEN 16384
#define R_PC  16383
#define R_LR  16382
#define R_SP  16381
#define R_FP  16380
#define R_ILR 16379
#define R_I   16378
#define R_F   16376 // F = m[16176..16377]

#define KBD m[R_KBD]
#define SCREEN m[R_SCREEN]
#define PC m[R_PC]  // PC 原本是 CPU 內部暫存器，現在被映射到 m[15], 這樣讓 PC 可以被存取，才能做出 ret 指令！
#define LR m[R_LR]
#define SP m[R_SP]
#define FP m[R_FP]
#define ILR m[R_ILR]
#define I  m[R_I]
// #define F  m[R_F] // 原本為 float   *F = (float*) &m[24580];
extern float   *F;

#endif
