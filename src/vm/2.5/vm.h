#ifndef __VM_H__
#define __VM_H__

#include <time.h>
#include "../../lib/util.h"

#define R_SCREEN 16384
#define R_KBD 24576
#define R_PC  24577
#define R_LR  24578
#define R_SP  24579
#define R_FP  24580
#define R_ILR 24581
#define R_I   24582
#define R_F   24583 // F = m[24583..24584]
#define R_CR  24585 // CR[0..4] = m[24585..24589]
#define R_CR0 24585
#define R_CR1 (R_CR+1)
#define R_CR2 (R_CR+2)
#define R_CR3 (R_CR+3)
#define R_CR4 (R_CR+4)

#define KBD m[R_KBD]
#define SCREEN m[R_SCREEN]
#define PC m[R_PC]  // PC 原本是 CPU 內部暫存器，現在被映射到 m[15], 這樣讓 PC 可以被存取，才能做出 ret 指令！
#define LR m[R_LR]
#define SP m[R_SP]
#define FP m[R_FP]
#define ILR m[R_ILR]
#define I  m[R_I]
#define F  (*(float*) &m[R_F])
#define CR0 m[R_CR]   // CR0 : 控制暫存器，位元 0 (是否允許外部中斷) ....
#define CR1 m[R_CR+1] // CR1 : 時間中斷長度， 0 代表不啟動時間中斷
#define CR2 m[R_CR+2]
#define CR3 m[R_CR+3]
#define CR4 m[R_CR+4]

extern void swi(int16_t A, int16_t D);
extern int aluExt(int16_t c, int16_t A, int16_t D, int16_t AM);
extern int alu(int16_t c, int16_t A, int16_t D, int16_t AM);
extern void cInstr(int16_t a, int16_t c, int16_t d, int16_t j);
extern int putstr(int16_t *str);
extern void cpu();

#endif
