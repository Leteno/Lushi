
include ../Makefile.common

UT = UT.o TestUT.o

test: $(UT)
	$(CC) $(UT) -o test_ut $(CFLAGS)
	./test_ut

$(UT): %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(UT) test_ut