
include ../Makefile.common

MACHINE_OBJ_DEPS=

OBJS = Machine.o CodeZone.o StackZone.o TestZone.o Utils.o

CardTools: machine codeGen CardToolsGUI

machine: $(OBJS)
	make -C ../machine/
	$(CC) $(OBJS) -o machine $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

$(OBJS) : %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

codeGen:
	@if [ ! -e "../../tools/CodeGenerator/" ]; then echo "CodeGenerator/ path not found"; exit 1; fi

CardToolsGUI:
	@echo Hello Java !

test:

clean:
	-rm machine $(OBJS)