
include ../Makefile.common

BASE = Sequence.o Machine.o State.o

TEST = TestSequence.o TestMachine.o

UT_PATHS = ../unit_test
UT_OBJS = ../unit_test/UT.o

all:

test: $(BASE) $(TEST) $(UT_OBJS)
	make -C $(UT_PATHS)
	$(CC) -c Test.cpp -o Test.o $(CFLAGS)
	$(CC) $(BASE) $(UT_OBJS) $(TEST) Test.o -o test $(CFLAGS)
	./test

$(BASE) $(TEST): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(BASE) $(TEST) Test.o test