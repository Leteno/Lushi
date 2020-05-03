
include ../Makefile.common

MACHINE_OBJ_DEPS=

MAIN_OBJ = Main.o

OBJS = CodeZone.o StackZone.o TestZone.o Utils.o TesterItem.o TesterData.o

EXTERNAL_OBJS = \
	$(patsubst %.cpp, %.o, $(shell ls ../base/*.cpp | grep -v Test)) \
	$(patsubst %.cpp, %.o, $(shell ls ../machine/*.cpp | grep -v Test)) \
	$(patsubst %.cpp, %.o, $(shell ls ../persist/*.cpp | grep -v Test)) \
	../misc/StringSeperator.o

CardTools: machine codeGen CardToolsGUI

machine: $(MAIN_OBJ) $(OBJS) external
	$(CC) $(MAIN_OBJ) $(OBJS) $(EXTERNAL_OBJS) -o machine $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

external:
	make -C ../misc/ test
	make -C ../machine/ test
	make -C ../base/ test
	make -C ../persist/ test

$(MAIN_OBJ) : %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

$(OBJS) : %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

codeGen:
	@if [ ! -e "../../tools/CodeGenerator/" ]; then echo "CodeGenerator/ path not found"; exit 1; fi

CardToolsGUI:
	@echo Hello Java !

test: machine testScript

testScript:
	python3 ../../tools/CodeGenerator/buildInstructionCode.py test

clean:
	-rm machine $(OBJS)
	-rm ../../tools/CodeGenerator/*.pyc