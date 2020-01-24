
include ../Makefile.common

BASE = Sequence.o
TEST = TestSequence.o

UT_PATHS = ../unit_test
UT_OBJS = ../unit_test/UT.o

all:

test: $(BASE) $(TEST) $(UT_OBJS)
	make -C $(UT_PATHS)
	$(CC) $(BASE) $(UT_OBJS) $(TEST) -o test $(CFLAGS)
	./test

$(BASE): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(TEST): %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(BASE) $(TEST) test