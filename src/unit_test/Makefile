
include ../Makefile.common

UT = UT.o
TEST_UT = TestUT.o

all: $(UT)

test: $(UT) $(TEST_UT)
	$(CC) $(UT) $(TEST_UT) -o test $(CFLAGS)
	./test

$(UT): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

TestUT.o : %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(UT) $(TEST_UT) test