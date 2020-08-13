
include ../Makefile.common

EXTERNAL_OBJS = ../unit_test/UT.o

OBJS = StringSeperator.o Utils.o
TEST_OBJS = TestStringSeperator.o TestUtils.o
MAIN_OBJ = Main.o

test: $(OBJS) $(TEST_OBJS) $(MAIN_OBJ) external
	$(CC) $(OBJS) $(EXTERNAL_OBJS) $(UT) $(TEST_OBJS) $(MAIN_OBJ) -o test $(CFLAGS)
	./test

external:
	make -C ../unit_test/	

$(TEST_OBJS) $(OBJS) : %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(MAIN_OBJ) : Main.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(OBJS) $(TEST_OBJS) $(MAIN_OBJ)