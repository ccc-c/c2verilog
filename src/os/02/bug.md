PC=0023 I=000A (iCount=7680005, savedA=0008 savedD=7530)  A=000A D=7530=30000 m[A]=000A
PC=0024 I=EC10 (iCount=7680006, savedA=0008 savedD=7530)  (cJump=0 aluOut=10) (cInstr:After A=000A) A=000A D=000A=00010 m[A]=000A a=0 c=30 d=2 j=0
PC=0025 I=0003 (iCount=7680007, savedA=0008 savedD=7530)  A=0003 D=000A=00010 m[A]=EA87
PC=0026 I=EBC0 (iCount=7680008, savedA=0008 savedD=7530)
 (cJump=0 aluOut=0) (cInstr:After A=0003) A=0003 D=000A=00010 m[A]=EA87 a=0 c=2F d=0 j=0
PC=0027 I=ED00 (iCount=7680009, savedA=0008 savedD=7530)
 .... (iCount=7680009, savedA=0008 savedD=7530 ILR=0009)  => (A=0008 D=7530, PC=0009)
 (cJump=1 aluOut=0)  ==> A=8 return(cInstr:After A=0008) A=0008 D=7530=30000 m[A]=0008 a=0 c=34 d=0 j=0  // c=34 是 iret
PC=0009 I=EA87 (iCount=7680010, savedA=0008 savedD=7530)  (cJump=1 aluOut=0)  ==> A=8 return(cInstr:After A=0008) A=0008 D=7530=30000 m[A]=0008 a=0 c=2A d=0 j=7  // c=2A 是 out = 0, EA87 是 0;JMP...
// 上面這行與下面對不起來，為何 => (A=0008 然後又是 EA87 的跳躍指令) 但是卻沒跳到 08 ，而是繼續到 0A 去了 .... 原因是 cJump = 1, 為何沒重設 ???
PC=000A I=000A (iCount=7680011, savedA=0008 savedD=7530)  A=000A D=7530=30000 m[A]=000A
PC=000B I=0000 (iCount=7680012, savedA=0008 savedD=7530)  A=0000 D=7530=30000 m[A]=0004
PC=000C I=0074 (iCount=7680013, savedA=0008 savedD=7530)  A=0074 D=7530=30000 m[A]=0000
PC=000D I=0069 (iCount=7680014, savedA=0008 savedD=7530)  A=0069 D=7530=30000 m[A]=0000
PC=000E I=006D (iCount=7680015, savedA=0008 savedD=7530)  A=006D D=7530=30000 m[A]=0000
PC=000F I=0065 (iCount=7680016, savedA=0008 savedD=7530)  A=0065 D=7530=30000 m[A]=0000
PC=0010 I=0072 (iCount=7680017, savedA=0008 savedD=7530)  A=0072 D=7530=30000 m[A]=0000



// ================ cInstr: iret 時 A 沒修改的問題已解決，但還是沒完全解決問題 ======

PC=0025 I=0003 (iCount=7680007, savedA=0008 savedD=7530)  A=0003 D=000A=00010 m[A]=EA87
PC=0026 I=EBC0 (iCount=7680008, savedA=0008 savedD=7530)
 A=0003 D=000A=00010 m[A]=EA87 a=0 c=2F d=0 j=0
PC=0027 I=ED00 (iCount=7680009, savedA=0008 savedD=7530)
 .... (iCount=7680009, savedA=0008 savedD=7530 ILR=0009)  => (A=0008 D=7530, PC=0009)
 A=0003 D=000A=00010 m[A]=EA87 a=0 c=34 d=0 j=0
// 上面這行不對，為何 => (A=0008 D=7530, PC=0009) 恢復後，接下來 A 又回到 0003 ... ?
PC=0009 I=EA87 (iCount=7680010, savedA=0008 savedD=7530)  A=0003 D=000A=00010 m[A]=EA87 a=0 c=2A d=0 j=7
PC=000A I=000A (iCount=7680011, savedA=0008 savedD=7530)  A=000A D=000A=00010 m[A]=000A
PC=000B I=0000 (iCount=7680012, savedA=0008 savedD=7530)  A=0000 D=000A=00010 m[A]=0004
PC=000C I=0074 (iCount=7680013, savedA=0008 savedD=7530)  A=0074 D=000A=00010 m[A]=0000
PC=000D I=0069 (iCount=7680014, savedA=0008 savedD=7530)  A=0069 D=000A=00010 m[A]=0000
PC=000E I=006D (iCount=7680015, savedA=0008 savedD=7530)  A=006D D=000A=00010 m[A]=0000
PC=000F I=0065 (iCount=7680016, savedA=0008 savedD=7530)  A=0065 D=000A=00010 m[A]=0000


// =========== iFile: os/02/boot.mx ==============
00 @resetHandler  
01 0;JMP  
02 @timerHandler  
03 0;JMP  
  
(resetHandler)  
// .setc CR1 = 30000  
04 @30000
05 D=A
06 @CR1
07 M=D
  
(main)  
  
(forever)  
// .goto forever  
08 @forever
09 0;JMP
// =========== iFile: os/02/const.mx ==============
0A-0B (LF) 10, 0  
0C-20 (timeMsg) "timerHandler: time=", 10, 0  
21    @15
22    swi
// .puts timeMsg  
// .puts LF  
23    @LF
24    D=A
25    @3
26    swi
27    iret  

// =============== 已加入 cJump 解決 =======================

iCount = 7670000
iCount = 7680000
interrupt: iCount = 7680000 A=0008 D=7530 PC=0009 I=EA87
PC=0002 I=0021 (iCount = 7680001)  A=0021 D=7530=30000 m[A]=000F
PC=0003 I=EA87 (iCount = 7680002)  A=0021 D=7530=30000 m[A]=000F a=0 c=2A d=0 j=7
PC=0021 I=000F (iCount = 7680003)  A=000F D=7530=30000 m[A]=0065
PC=0022 I=EBC0 (iCount = 7680004) Sun Mar 31 19:33:10 2019
 A=000F D=7530=30000 m[A]=0065 a=0 c=2F d=0 j=0
PC=0023 I=000A (iCount = 7680005)  A=000A D=7530=30000 m[A]=000A
PC=0024 I=EC10 (iCount = 7680006)  A=000A D=000A=00010 m[A]=000A a=0 c=30 d=2 j=0
PC=0025 I=0003 (iCount = 7680007)  A=0003 D=000A=00010 m[A]=EA87
PC=0026 I=EBC0 (iCount = 7680008)
 A=0003 D=000A=00010 m[A]=EA87 a=0 c=2F d=0 j=0
PC=0027 I=ED00 (iCount = 7680009)  A=0003 D=000A=00010 m[A]=EA87 a=0 c=34 d=0 j=0
PC=0009 I=EA87 (iCount = 7680010)  A=0003 D=000A=00010 m[A]=EA87 a=0 c=2A d=0 j=7
// 指令 0;JMP 這時 A 應該是 08 的 @forever, 但為何卻變成了 A=0003 ，導致最後鎖定在 3 跳不出去呢？
PC=0003 I=EA87 (iCount = 7680011)  A=0003 D=000A=00010 m[A]=EA87 a=0 c=2A d=0 j=7
PC=0003 I=EA87 (iCount = 7680012)  A=0003 D=000A=00010 m[A]=EA87 a=0 c=2A d=0 j=7


(timerHandler)  
// .puts timeMsg  
// .puttime  
0021 @15
0022 swi
// .puts timeMsg  
// .puts LF  
0023 @LF
0024 D=A
0025 @3     這裡的 A=3 延續至後面，導致 iret 返回時得到 A = 3，以致進入無窮迴圈！
0026 swi
0027 iret  問題是 iret 不是會恢復 A = savedA 嗎？ savedA 是時間中斷觸發時的 A 值，




