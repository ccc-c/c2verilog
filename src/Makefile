CC := gcc
CFLAGS = -std=c99 -O0 -Wall 
ALL = cc1 cc2 cc3 ma1 ma2 ma3 as1 as2 as3 vm1 vm2 vm3
NEW = cc3 ma3 as3 vm3
BIN = ../bin
LIB = lib/util.c lib/map.c lib/strTable.c

new: $(NEW)

all: $(ALL)

cc1: cc/1/cc.c cc/1/lexer.c cc/1/compiler.c ir/1/ir.c ir/1/irvm.c ir/1/ir2m.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

cc2: cc/2/cc.c cc/2/lexer.c cc/2/compiler.c ir/2/ir.c ir/2/irvm.c ir/2/ir2m.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

cc3: cc/3/cc.c cc/3/lexer.c cc/3/compiler.c ir/3/ir.c ir/3/irvm.c ir/3/ir2m.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

as1: as/1/asm.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

as2: as/2/asm.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

as3: as/3/asm.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

vm1: vm/1/vm.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

vm2: vm/2/vm.c vm/2/vmExt.c $(LIB)
	$(CC) -D_VM_EXT_ $(CFLAGS) $^ -o $(BIN)/$@

vm3: vm/3/vm.c $(LIB)
	$(CC) -D_VM_EXT_ -g $(CFLAGS) $^ -o $(BIN)/$@

ma1: ma/1/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ma2: ma/2/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ma3: ma/3/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

run:
	$(BIN)/${exe} ../test/$(file) -d -r

c1Run: 
	$(BIN)/cc1 ../test/c/$(file)
	$(BIN)/ma2 ../test/c/$(file).mx -o ../test/c/$(file).sx
	$(BIN)/as3 ../test/c/$(file)
	$(BIN)/vm3 ../test/c/$(file).ox -d

c2Run: 
	$(BIN)/cc2 ../test/c/$(file)
	$(BIN)/ma2 ../test/c/$(file).mx -o ../test/c/$(file).sx
	$(BIN)/as3 ../test/c/$(file)
	$(BIN)/vm3 ../test/c/$(file).ox

c2ir: 
	$(BIN)/cc3 ../test/c/$(file) -d

c3Run: 
	$(BIN)/cc3 ../test/c/$(file) -d
	$(BIN)/ma3 ../test/c/$(file).mx -o ../test/c/$(file).sx

m3Run: 
	$(BIN)/ma3 ../test/m/$(file).mx -o ../test/m/$(file).sx
	$(BIN)/as3 ../test/m/$(file) -d
	$(BIN)/vm3 ../test/m/$(file).ox

cRun: 
	$(BIN)/cc3 ../test/c/$(file)
	$(BIN)/ma2 ../test/c/$(file).mx -o ../test/c/$(file).sx
	$(BIN)/as3 ../test/c/$(file)
	$(BIN)/vm3 ../test/c/$(file).ox

mRun: 
	$(BIN)/ma2 ../test/m/$(file).mx -o ../test/m/$(file).sx
	$(BIN)/as3 ../test/m/$(file)
	$(BIN)/vm3 ../test/m/$(file).ox

s3Run: 
	$(BIN)/as3 ../test/m/$(file)
	$(BIN)/vm3 ../test/m/$(file).ox

sRun: 
	$(BIN)/as3 ../test/m/$(file)
	$(BIN)/vm3 ../test/m/$(file).ox

oRun: 
	$(BIN)/vm3 ../test/m/$(file).ox

oDebug: 
	$(BIN)/vm3 ../test/m/$(file).ox -d

os01: 
	$(BIN)/ma2 os/01/os01.mx -o os/01/os01.sx
	$(BIN)/as3 os/01/os01
	$(BIN)/vm3 os/01/os01.ox

os02: 
	$(BIN)/ma2 os/02/boot.mx os/02/const.mx os/02/time.mx -o os/02/os02.sx
	$(BIN)/as3 os/02/os02
	$(BIN)/vm3 os/02/os02.ox

clean:
	rm -f $(BIN)/*.o $(BIN)/*.exe
