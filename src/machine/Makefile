
include ../Makefile.common

BASE = Sequence.o Machine.o State.o

T_SEQ = TestSequence.o
T_MACH = TestMachine.o

UT_PATHS = ../unit_test
UT_OBJS = ../unit_test/UT.o

all:

test: $(BASE) $(T_SEQ) $(T_MACH) $(UT_OBJS)
	make -C $(UT_PATHS)
	$(CC) $(BASE) $(UT_OBJS) $(T_SEQ) -o testSeq $(CFLAGS)
	$(CC) $(BASE) $(UT_OBJS) $(T_MACH) -o testMach $(CFLAGS)
	./testSeq && ./testMach

$(BASE): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(T_SEQ) $(T_MACH): %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(BASE) $(TEST) test