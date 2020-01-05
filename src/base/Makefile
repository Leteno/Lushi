
ifdef MAIN_BUILD
include Makefile.common
BASE_PATH=base/
else
include ../Makefile.common
BASE_PATH=
endif

BASE := $(patsubst %.cpp, %.o, $(shell ls $(BASE_PATH)*.cpp | grep -v Test))
BASE_UT := $(patsubst %.cpp, %.o, $(shell ls $(BASE_PATH)*.cpp | grep Test))

ut_base: $(BASE) $(BASE_UT)
	$(CC) $(BASE) $(BASE_UT) -o $(BASE_PATH)ut_base $(CFLAGS)
	./$(BASE_PATH)ut_base

$(BASE): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(BASE_UT): %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

ifdef MAIN_BUILD
clean_base:
else
clean:
endif
	-rm $(BASE_PATH)*.o $(BASE_PATH)ut_base