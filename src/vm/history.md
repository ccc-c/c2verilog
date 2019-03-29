# vm 虛擬機的版本

* 0 -- 有延伸指令集與中斷
* 1 -- 有 Timer Interrupt
    * 並支援 call, ret, iret
    * 還將 PC, LR, SP, .... 等暫存器映射回記憶體，讓程式可以存取到這些值。