
include ../Makefile.common

EXTERNAL_OBJS = ../unit_test/UT.o

OBJS = Parcel.o Parcellable.o RawData.o
T_OBJS = TestParcellable.o TestRawData.o

test: build_test
	./test

build_test: $(EXTERNAL_OBJS) $(OBJS) $(T_OBJS) Test.cpp
	$(CC) -c Test.cpp -o Test.o $(CFLAGS)
	$(CC) $(EXTERNAL_OBJS) $(OBJS) $(T_OBJS) Test.o -o test $(CFLAGS)

$(EXTERNAL_OBJS):
	make -C ../unit_test/ test

$(OBJS) $(T_OBJS): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm -rf $(EXTERNAL_OBJS) $(OBJS) $(T_OBJS) Test.o test