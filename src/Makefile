
GCC=g++ -g
BASE=base/Effect.o base/EffectMachine.o base/GameObject.o
UT=unit_test/TestEffectMachine.o

test: $(BASE) $(UT)
	$(GCC) $(BASE) $(UT) -o ut
	./ut

clean:
	rm $(BASE) $(UT)
