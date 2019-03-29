CC := gcc
CFLAGS = -std=c99 -O0 -Wall 
TARGET = cc1 ma1 as1 vm1 ma2 as2 vm2 as3 vm3
BIN = ../bin
LIB = lib/util.c lib/map.c lib/strTable.c

all: $(TARGET)

cc1: cc/1/cc.c cc/1/lexer.c cc/1/compiler.c ir/1/ir.c ir/1/irvm.c ir/1/ir2m.c $(LIB)
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

vm3: vm/3/vm.c vm/3/vmExt.c $(LIB)
	$(CC) -D_VM_EXT_ $(CFLAGS) $^ -o $(BIN)/$@

ma1: ma/1/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ma2: ma/2/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

c1run:
	$(BIN)/cc1 ../test/c/$(file) -r

m1run: 
	$(BIN)/ma1 ../test/m/$(file)
	$(BIN)/as1 ../test/m/$(file)
	$(BIN)/vm1 ../test/m/$(file).ox

m2run: 
	$(BIN)/ma2 ../test/m/$(file)
	$(BIN)/as2 ../test/m/$(file)
	$(BIN)/vm2 ../test/m/$(file).ox

m3run: 
	$(BIN)/ma2 ../test/m/$(file)
	$(BIN)/as3 ../test/m/$(file)
	$(BIN)/vm3 ../test/m/$(file).ox

os1run: 
	$(BIN)/ma2 os/0/$(OS)
	$(BIN)/as3 os/0/$(OS)
	$(BIN)/vm3 os/0/$(OS).ox

clean:
	rm -f $(BIN)/*.o $(BIN)/*.exe
