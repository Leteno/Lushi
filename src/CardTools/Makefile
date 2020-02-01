
include ../Makefile.common

MACHINE_OBJ_DEPS=

CardTools: machine codeGen CardToolsGUI

machine:
	make -C ../machine/
	$(CC) -c Machine.cpp -o Machine.o $(CFLAGS)
	$(CC) $(MACHINE_OBJ_DEPS) Machine.o -o machine $(CFLAGS)

codeGen:
	@if [ ! -e "../../tools/gen-code/" ]; then echo "gen-code/ path not found"; exit 1; fi

CardToolsGUI:
	@echo Hello Java !

test:

clean:
	-rm machine