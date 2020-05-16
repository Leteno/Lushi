
include ../Makefile.common

MACHINE_OBJ_DEPS=

MAIN_OBJ = Main.o

TEST_OBJ = unit_test/Test.o

OBJS = CodeZone.o StackZone.o TestZone.o \
	Utils.o TesterItem.o TesterData.o \
	CardEffectListZone.o SaveZone.o \
	CardEffectsModel.o

TEST_OBJS = $(patsubst %.cpp, %.o, $(shell ls unit_test/*.cpp | grep -v Test.cpp))

TEST_EXTERNAL_OBJS = ../unit_test/UT.o

EXTERNAL_OBJS = \
	$(patsubst %.cpp, %.o, $(shell ls ../base/*.cpp | grep -v Test)) \
	$(patsubst %.cpp, %.o, $(shell ls ../machine/*.cpp | grep -v Test)) \
	$(patsubst %.cpp, %.o, $(shell ls ../persist/*.cpp | grep -v Test)) \
	$(patsubst %.cpp, %.o, $(shell ls ../card/*.cpp | grep -v Test)) \
	../misc/StringSeperator.o

CardTools: machine codeGen CardToolsGUI

machine: $(MAIN_OBJ) $(OBJS) external
	$(CC) $(MAIN_OBJ) $(OBJS) $(EXTERNAL_OBJS) -o machine $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

external:
	make -C ../misc/ test
	make -C ../machine/ test
	make -C ../base/ test
	make -C ../persist/ test
	make -C ../card/ test

$(TEST_EXTERNAL_OBJS):
	make -C ../unit_test/ test

$(MAIN_OBJ) $(TEST_OBJ) : %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

$(OBJS) $(TEST_OBJS): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`

codeGen:
	@if [ ! -e "../../tools/CodeGenerator/" ]; then echo "CodeGenerator/ path not found"; exit 1; fi

CardToolsGUI:
	@echo Hello Java !

test: machine testScript $(TEST_OBJS) $(TEST_OBJ) $(TEST_EXTERNAL_OBJS)
	$(CC) $(TEST_OBJ) $(TEST_OBJS) $(OBJS) $(EXTERNAL_OBJS) $(TEST_EXTERNAL_OBJS) -o test $(CFLAGS) `pkg-config --cflags --libs gtk+-2.0`
	./test

testScript:
	python3 ../../tools/CodeGenerator/buildInstructionCode.py test

clean:
	-rm machine $(OBJS) $(TEST_OBJ) $(TEST_OBJS)
	-rm ../../tools/CodeGenerator/*.pyc