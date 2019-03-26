CC := gcc
CFLAGS = -std=c99 -O0 -Wall 
TARGET = cc0 ma0 as0 vm0
BIN = ../bin
LIB = lib/util.c lib/map.c lib/strTable.c

all: $(TARGET)

cc0: cc/0/cc0.c cc/0/lexer.c cc/0/compiler.c cc/0/ir.c cc/0/irvm.c cc/0/ir2m.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

as0: as/0/asm.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

vm0: vm/0/vm.c vm/0/vmExt.c $(LIB)
	$(CC) -D_VM_EXT_ $(CFLAGS) $^ -o $(BIN)/$@

ma0: ma/0/macro.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

c0run:
	$(BIN)/cc0 $(file) -r

c0debug:
	$(BIN)/cc0 $(file) -d

m0run: 
	$(BIN)/ma0 $(file)
	$(BIN)/as0 $(file)
	$(BIN)/vm0 $(file).o0

clean:
	rm -f $(BIN)/*.o $(BIN)/*.exe
