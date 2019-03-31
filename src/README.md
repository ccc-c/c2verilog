# 執行方法

```
user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make
gcc -std=c99 -O0 -Wall  cc/1/cc.c cc/1/lexer.c cc/1/compiler.c ir/1/ir.c ir/1/irvm.c ir/1/ir2m.c lib/util.c lib/map.c lib/strTable.c -o ../bin/cc1
gcc -std=c99 -O0 -Wall  ma/1/macro.c lib/util.c lib/map.c lib/strTable.c -o ../bin/ma1
gcc -std=c99 -O0 -Wall  as/1/asm.c lib/util.c lib/map.c lib/strTable.c -o ../bin/as1
gcc -std=c99 -O0 -Wall  vm/1/vm.c lib/util.c lib/map.c lib/strTable.c -o ../bin/vm1
gcc -std=c99 -O0 -Wall  ma/2/macro.c lib/util.c lib/map.c lib/strTable.c -o ../bin/ma2
gcc -std=c99 -O0 -Wall  as/2/asm.c lib/util.c lib/map.c lib/strTable.c -o ../bin/as2
gcc -D_VM_EXT_ -std=c99 -O0 -Wall  vm/2/vm.c vm/2/vmExt.c lib/util.c lib/map.c lib/strTable.c -o ../bin/vm2
gcc -std=c99 -O0 -Wall  as/3/asm.c lib/util.c lib/map.c lib/strTable.c -o ../bin/as3
gcc -D_VM_EXT_ -std=c99 -O0 -Wall  vm/3/vm.c vm/3/vmExt.c lib/util.c lib/map.c lib/strTable.c -o ../bin/vm3

user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make m3run file=float
../bin/ma2 ../test/m/float
../bin/as3 ../test/m/float
../bin/vm3 ../test/m/float.ox
3.141590 6.283180 25.132721
user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make m3run file=hello
../bin/ma2 ../test/m/hello
../bin/as3 ../test/m/hello
../bin/vm3 ../test/m/hello.ox
hello
world!
world!
world!
user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make m3run file=call
../bin/ma2 ../test/m/call
../bin/as3 ../test/m/call
../bin/vm3 ../test/m/call.ox
hello world!
hello world!

user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make m3run file=sum
../bin/ma2 ../test/m/sum
../bin/as3 ../test/m/sum
../bin/vm3 ../test/m/sum.ox
sum=55

user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make os1run OS=os1.3
../bin/ma2 os/1/os1.3
../bin/as3 os/1/os1.3
../bin/vm3 os/1/os1.3.ox
time: Fri Mar 29 15:50:34 2019
process1
time: Fri Mar 29 15:50:34 2019
process2
time: Fri Mar 29 15:50:34 2019
process0
time: Fri Mar 29 15:50:34 2019
process1
time: Fri Mar 29 15:50:34 2019
process2
time: Fri Mar 29 15:50:34 2019
process0
time: Fri Mar 29 15:50:34 2019
process1
...

user@DESKTOP-96FRN6B MSYS /d/ccc/book/c2verilog/src
$ make c1run file=sum
../bin/cc1 ../test/c/sum -r
token = s          type = Id
token = =          type = Op
token = 0          type = Int
token = ;          type = Op
token = i          type = Id
token = =          type = Op
token = 1          type = Int
token = ;          type = Op
token = while      type = Id
token = (          type = Op
token = i          type = Id
token = <=         type = Op
token = 10         type = Int
token = )          type = Op
token = {          type = Op
token = s          type = Id
token = =          type = Op
token = s          type = Id
token = +          type = Op
token = i          type = Id
token = ;          type = Op
token = i          type = Id
token = =          type = Op
token = i          type = Id
token = +          type = Op
token = 1          type = Int
token = ;          type = Op
token = }          type = Op
token = (null)     type = End
===================irRun()=======================
00: t1 = 0 = 0
01: s = t1 = 0
02: t1 = 1 = 1
03: i = t1 = 1
04: (L1) = 4
05: t2 = i = 1
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 0
10: t2 = i = 1
11: t3 = t1 + t2 = 1
12: s = t3 = 1
13: t1 = i = 1
14: t2 = 1 = 1
15: t3 = t1 + t2 = 2
16: i = t3 = 2
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 2
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 1
10: t2 = i = 2
11: t3 = t1 + t2 = 3
12: s = t3 = 3
13: t1 = i = 2
14: t2 = 1 = 1
15: t3 = t1 + t2 = 3
16: i = t3 = 3
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 3
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 3
10: t2 = i = 3
11: t3 = t1 + t2 = 6
12: s = t3 = 6
13: t1 = i = 3
14: t2 = 1 = 1
15: t3 = t1 + t2 = 4
16: i = t3 = 4
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 4
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 6
10: t2 = i = 4
11: t3 = t1 + t2 = 10
12: s = t3 = 10
13: t1 = i = 4
14: t2 = 1 = 1
15: t3 = t1 + t2 = 5
16: i = t3 = 5
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 5
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 10
10: t2 = i = 5
11: t3 = t1 + t2 = 15
12: s = t3 = 15
13: t1 = i = 5
14: t2 = 1 = 1
15: t3 = t1 + t2 = 6
16: i = t3 = 6
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 6
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 15
10: t2 = i = 6
11: t3 = t1 + t2 = 21
12: s = t3 = 21
13: t1 = i = 6
14: t2 = 1 = 1
15: t3 = t1 + t2 = 7
16: i = t3 = 7
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 7
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 21
10: t2 = i = 7
11: t3 = t1 + t2 = 28
12: s = t3 = 28
13: t1 = i = 7
14: t2 = 1 = 1
15: t3 = t1 + t2 = 8
16: i = t3 = 8
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 8
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 28
10: t2 = i = 8
11: t3 = t1 + t2 = 36
12: s = t3 = 36
13: t1 = i = 8
14: t2 = 1 = 1
15: t3 = t1 + t2 = 9
16: i = t3 = 9
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 9
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 36
10: t2 = i = 9
11: t3 = t1 + t2 = 45
12: s = t3 = 45
13: t1 = i = 9
14: t2 = 1 = 1
15: t3 = t1 + t2 = 10
16: i = t3 = 10
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 10
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 1
08: ifnot t4(=1)  -- fail
09: t1 = s = 45
10: t2 = i = 10
11: t3 = t1 + t2 = 55
12: s = t3 = 55
13: t1 = i = 10
14: t2 = 1 = 1
15: t3 = t1 + t2 = 11
16: i = t3 = 11
17: goto L1 = 4
04: (L1) = 4
05: t2 = i = 11
06: t3 = 10 = 10
07: t4 = t2 <= t3 = 0
08: ifnot t4(=0) goto L2 = 18
18: (L2) = 18


```