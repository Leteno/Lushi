
include ../Makefile.common

BASE = Sequence.o Machine.o State.o Compiler.o

TEST = TestSequence.o TestMachine.o TestMachine_OBJ.o TestCompiler.o

EXTERNAL_OBJS = \
	../persist/Parcellable.o ../persist/Parcel.o ../persist/RawData.o \
	../base/GameObject.o ../base/Effect.o ../base/EffectMachine.o \
	../unit_test/UT.o ../misc/MessageException.o ../misc/StringSeperator.o ../misc/Utils.o

all:

test: $(BASE) $(TEST) $(UT_OBJS) $(BASE_OBJ) $(EXTERNAL_OBJS)
	$(CC) -c Test.cpp -o Test.o $(CFLAGS)
	$(CC) $(BASE) $(EXTERNAL_OBJS) $(TEST) Test.o -o test $(CFLAGS)
	./test

$(BASE) $(TEST): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(EXTERNAL_OBJS):
	make -C ../base test
	make -C ../misc test
	make -C ../persist test
	make -C ../unit_test test

clean:
	-rm $(BASE) $(TEST) Test.o test