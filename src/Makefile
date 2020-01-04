
GCC=g++ -g
BASE=base/Effect.o base/EffectMachine.o base/GameObject.o
UT=unit_test/TestEffectMachine.o

test: $(BASE) $(UT)
	$(GCC) $(BASE) $(UT) -o ut

$(BASE): %.o : %.cpp %.h
	$(GCC) -c $< -o $@

$(UT): %.o : %.cpp
	$(GCC) -c $< -o $@

clean:
	-rm $(BASE) $(UT)
