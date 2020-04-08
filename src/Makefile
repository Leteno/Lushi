
PATHS = unit_test/ base/ machine/ misc/ persist

all:
	@echo Hello world

test: $(addsuffix -test, $(PATHS))

clean: $(addsuffix -clean, $(PATHS))

$(addsuffix -test, $(PATHS)):
	make -C $(@:-test=) test

$(addsuffix -clean, $(PATHS)):
	make -C $(@:-clean=) clean