
include ../Makefile.common

MACHINE_OBJ_DEPS=

OBJS = Machine.o CodeZone.o StackZone.o TestZone.o Utils.o TesterItem.o TesterData.o

EXTERNAL_OBJS = ../machine/Sequence.o ../misc/StringSeperator.o

CardTools: machine codeGen CardToolsGUI

machine: $(OBJS) external
	$(CC) $(OBJS) $(EXTERNAL_OBJS) -o machine $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

external:
	make -C ../misc/ test
	make -C ../machine/ test

$(OBJS) : %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

codeGen:
	@if [ ! -e "../../tools/CodeGenerator/" ]; then echo "CodeGenerator/ path not found"; exit 1; fi

CardToolsGUI:
	@echo Hello Java !

test:

clean:
	-rm machine $(OBJS)