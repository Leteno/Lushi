
include ../Makefile.common

BASE := $(patsubst %.cpp, %.o, $(shell ls $(BASE_PATH)*.cpp | grep -v Test))
BASE_TEST := $(patsubst %.cpp, %.o, $(shell ls $(BASE_PATH)*.cpp | grep Test))

OBJS += $(BASE)

DEP_PATHS = ../unit_test
ADDITIONAL_DEPS_OBJS = ../unit_test/UT.o

test: $(BASE) $(BASE_TEST)
	make -C $(DEP_PATHS)
	$(CC) $(BASE) $(BASE_TEST) $(ADDITIONAL_DEPS_OBJS) $(UT) -o test $(CFLAGS)
	./test

$(BASE): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(BASE_TEST): %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	make -C $(DEP_PATHS) clean
	-rm *.o test