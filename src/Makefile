
CC=g++
CFLAGS=-g
BASE=base/Effect.o base/EffectMachine.o base/GameObject.o
UT=unit_test/TestEffectMachine.o

test: $(BASE) $(UT)
	$(CC) $(BASE) $(UT) -o ut $(CFLAGS)

$(BASE): %.o : %.cpp %.h
	$(CC) -c $< -o $@ $(CFLAGS)

$(UT): %.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	-rm $(BASE) $(UT)
