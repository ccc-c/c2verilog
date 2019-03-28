CC := gcc
CFLAGS = -std=c99 -O0 -Wall 
TARGET = cc0 ma0 as0 vm0 vm1 ma1
BIN = ../bin
LIB = lib/util.c lib/map.c lib/strTable.c

all: $(TARGET)

cc0: cc/0/cc0.c cc/0/lexer.c cc/0/compiler.c ir/0/ir.c ir/0/irvm.c ir/0/ir2m.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

as0: as/0/asm.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

vm0: vm/0/vm.c vm/0/vmExt.c $(LIB)
	$(CC) -D_VM_EXT_ $(CFLAGS) $^ -o $(BIN)/$@

vm1: vm/1/vm.c vm/1/vmExt.c $(LIB)
	$(CC) -D_VM_EXT_ $(CFLAGS) $^ -o $(BIN)/$@

ma0: ma/0/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

ma1: ma/1/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

c0run:
	$(BIN)/cc0 $(file) -r

c0debug:
	$(BIN)/cc0 $(file) -d

m0run: 
	$(BIN)/ma0 $(file)
	$(BIN)/as0 $(file)
	$(BIN)/vm0 $(file).ox

os0run: 
	$(BIN)/ma1 os/0/os0
	$(BIN)/as0 os/0/os0
	$(BIN)/vm1 os/0/os0.ox

os1run: 
	$(BIN)/ma1 os/1/os1
	$(BIN)/as0 os/1/os1
	$(BIN)/vm1 os/1/os1.ox

os2run: 
	$(BIN)/ma1 os/2/os2
	$(BIN)/as0 os/2/os2
	$(BIN)/vm1 os/2/os2.ox

os3run: 
	$(BIN)/ma1 os/3/os3
	$(BIN)/as0 os/3/os3
	$(BIN)/vm1 os/3/os3.ox

clean:
	rm -f $(BIN)/*.o $(BIN)/*.exe
