
include ../Makefile.common

UT = UT.o

all: $(UT)

test: $(UT)
	$(CC) $(UT) -o test_ut $(CFLAGS)

$(UT): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

TestUT.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(UT) test_ut