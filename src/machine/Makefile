
include ../Makefile.common

BASE = Sequence.o Machine.o State.o

TEST = TestSequence.o TestMachine.o TestMachine_OBJ.o

BASE_PATH = ../base/
BASE_OBJ = ../base/GameObject.o ../base/Effect.o ../base/EffectMachine.o

UT_PATHS = ../unit_test
UT_OBJS = ../unit_test/UT.o

all:

test: $(BASE) $(TEST) $(UT_OBJS) $(BASE_OBJ)
	make -C $(UT_PATHS)
	make -C $(BASE_PATH)
	$(CC) -c Test.cpp -o Test.o $(CFLAGS)
	$(CC) $(BASE) $(UT_OBJS) $(BASE_OBJ) $(TEST) Test.o -o test $(CFLAGS)
	./test

$(BASE) $(TEST): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(BASE) $(TEST) Test.o test